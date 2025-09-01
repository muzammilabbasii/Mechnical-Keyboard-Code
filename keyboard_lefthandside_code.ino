#include <Keyboard.h>

// --------------------
// Right-hand side matrix pin assignments
const byte rows[6] = {2, 3, 4, 5, 6, 7};       // row pins
const byte cols[11] = {8, 9, 10, 14, 15, 16, A0, A1, A2, A3, RX1}; // 11 columns

#define ROWS 6
#define COLS 11

// --------------------
// Keymap for right-hand side (letters, numbers, special keys)
char letters[ROWS][COLS] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Row 1 mostly function keys handled in specials
  {'0','-','=',0,0,0,0,0,0,0,0},     // Row 2 numbers/punctuation
  {'[',']','\\',0,0,0,0,0,0,0,0},    // Row 3 brackets and backslash
  {';','\'',0,0,0,0,0,0,0,0,0},      // Row 4 semicolon/quote
  {'.','/',KEY_RIGHT_SHIFT,0,0,0,0,0,0,0,0}, // Row 5 punctuation + shift
  {KEY_RIGHT_ALT, KEY_COM, KEY_RIGHT_GUI, KEY_RIGHT_CTRL,0,0,0,0,0,0,0} // Row 6 modifiers
};

// --------------------
// Special keys
char specials[ROWS][COLS] = {
  {KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINT_SCREEN, KEY_SCROLL_LOCK, KEY_PAUSE, 0,0,0,0}, // Row1
  {0,0,0,KEY_BACKSPACE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP, KEY_NUM_LOCK, KEY_KP_DIVIDE, KEY_KP_MULTIPLY, KEY_KP_SUBTRACT}, // Row2
  {0,0,0, KEY_DELETE, KEY_END, KEY_PAGE_DOWN, '7','8','9',0,0}, // Row3
  {0,0,KEY_RETURN, '4','5','6',KEY_KP_ADD,0,0,0,0}, // Row4
  {0,0,0, KEY_UP_ARROW, '1','2','3',0,0,0,0}, // Row5
  {0,0,0, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, '0','.',KEY_RETURN,0,0} // Row6
};

// --------------------
// Shifted numbers/punctuation (for number row)
char shiftNumbers[COLS] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_'}; // last column RX1 optional

// --------------------
bool keyState[ROWS][COLS] = {false};
bool shiftPressed = false;
bool capsLockOn = false;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();

  // Initialize row pins as OUTPUT HIGH
  for(byte r=0; r<ROWS; r++){
    pinMode(rows[r], OUTPUT);
    digitalWrite(rows[r], HIGH);
  }

  // Initialize column pins as INPUT_PULLUP
  for(byte c=0; c<COLS; c++){
    pinMode(cols[c], INPUT_PULLUP);
  }
}

void loop() {
  const int DEBOUNCE_DELAY = 5;

  for(byte r=0; r<ROWS; r++){
    digitalWrite(rows[r], LOW); // activate row

    for(byte c=0; c<COLS; c++){
      bool pressed = (digitalRead(cols[c]) == LOW);
      char k = letters[r][c];
      char s = specials[r][c];

      // Track Right Shift
      if(k == KEY_RIGHT_SHIFT){
        shiftPressed = pressed;
        keyState[r][c] = pressed;
        continue; // skip normal press/release
      }

      // Toggle Caps Lock
      if(s == KEY_CAPS_LOCK && pressed && !keyState[r][c]) capsLockOn = !capsLockOn;

      // ----------------
      // Handle letters and numbers
      if(k != 0){
        char out = k;

        // Numbers row with Shift
        if(r == 1 && shiftPressed) out = shiftNumbers[c];

        // Letters with Shift or Caps Lock
        else if(k >= 'a' && k <= 'z'){
          if((shiftPressed && !capsLockOn) || (!shiftPressed && capsLockOn)) out = toupper(k);
        }

        // Press or release
        if(pressed && !keyState[r][c]){
          Keyboard.press(out);
          keyState[r][c] = true;
          Serial.print("Pressed: "); Serial.println(out);
        } else if(!pressed && keyState[r][c]){
          Keyboard.release(out);
          keyState[r][c] = false;
          Serial.print("Released: "); Serial.println(out);
        }
      }

      // ----------------
      // Handle special keys
      if(s != 0){
        if(pressed && !keyState[r][c]){
          Keyboard.press(s);
          keyState[r][c] = true;
          Serial.print("Special Pressed: "); Serial.println(s);
        } else if(!pressed && keyState[r][c]){
          Keyboard.release(s);
          keyState[r][c] = false;
          Serial.print("Special Released: "); Serial.println(s);
        }
      }
    }

    digitalWrite(rows[r], HIGH); // deactivate row
    delay(DEBOUNCE_DELAY);
  }
}
