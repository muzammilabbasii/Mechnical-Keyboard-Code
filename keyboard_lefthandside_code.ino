#include <Keyboard.h>

const byte rows[6] = {2, 3, 4, 5, 6, 7};
const byte cols[10] = {8, 9, 10, 14, 15, 16, A0, A1, A2, A3};

#define ROWS 6
#define COLS 10

// Letters and normal keys
char letters[ROWS][COLS] = {
  {0,0,0,0,0,0,0,0,0,0},                                // Row 1: Esc + F1–F8 placeholders
  {'`','1','2','3','4','5','6','7','8','9'},            // Row 2: Numbers
  {KEY_TAB,'q','w','e','r','t','y','u','i','o'},        // Row 3: Q–P + Tab
  {KEY_CAPS_LOCK,'a','s','d','f','g','h','j','k','l'},  // Row 4: A–L + Caps Lock
  {KEY_LEFT_SHIFT,'z','x','c','v','b','n','m','p',','}, // Row 5: Shift row + extra 'p'
  {KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT,' ',' ',' ',' ',' ',' ',' '} // Row 6: Ctrl, Windows, Alt, Space
};

// Special keys
char specials[ROWS][COLS] = {
  {KEY_ESC,0,KEY_F1,KEY_F2,KEY_F3,KEY_F4,KEY_F5,KEY_F6,KEY_F7,KEY_F8}, // Row 1
  {0,0,0,0,0,0,0,0,0,0},   // Row 2
  {KEY_TAB,0,0,0,0,0,0,0,0,0}, // Row 3
  {KEY_CAPS_LOCK,0,0,0,0,0,0,0,0,0}, // Row 4
  {0,0,0,0,0,0,0,0,0,0},   // Row 5
  {0,0,0,0,0,0,0,0,0,0}    // Row 6
};

// Shifted numbers (Row 2)
char shiftNumbers[COLS] = {'~','!','@','#','$','%','^','&','*','('};

bool keyState[ROWS][COLS] = {false};
bool shiftPressed = false;
bool capsLockOn = false;

void setup() {
  Keyboard.begin();
  for(byte r=0;r<ROWS;r++){
    pinMode(rows[r],OUTPUT);
    digitalWrite(rows[r],HIGH);
  }
  for(byte c=0;c<COLS;c++){
    pinMode(cols[c],INPUT_PULLUP);
  }
}

void loop() {
  const int DEBOUNCE_DELAY = 5;

  for(byte r=0;r<ROWS;r++){
    digitalWrite(rows[r],LOW); // activate row

    for(byte c=0;c<COLS;c++){
      bool pressed = (digitalRead(cols[c])==LOW);
      char k = letters[r][c];
      char s = specials[r][c];

      // Track physical Shift key
      if(k == KEY_LEFT_SHIFT) shiftPressed = pressed;

      // Toggle Caps Lock
      if(s == KEY_CAPS_LOCK && pressed && !keyState[r][c]) capsLockOn = !capsLockOn;

      // ----------------
      // Handle letters and numbers using Keyboard.write() once per press
      if(k != 0){
        if(pressed && !keyState[r][c]){  // Only trigger once per press
          char outputChar = k;

          // Row 2 numbers → symbols when Shift
          if(r == 1) outputChar = shiftPressed ? shiftNumbers[c] : letters[r][c];

          // Letters → uppercase if Shift or Caps Lock
          else if(k >= 'a' && k <= 'z'){
            bool upper = (shiftPressed && !capsLockOn) || (!shiftPressed && capsLockOn);
            if(upper) outputChar = toupper(k);
          }

          // Send output
          Keyboard.write(outputChar);
          keyState[r][c] = true;
        }
        else if(!pressed && keyState[r][c]){
          keyState[r][c] = false;
        }
      }

      // ----------------
      // Handle special keys (modifiers)
      if(s != 0){
        if(pressed && !keyState[r][c]){
          Keyboard.press(s);
          keyState[r][c] = true;
        } else if(!pressed && keyState[r][c]){
          Keyboard.release(s);
          keyState[r][c] = false;
        }
      }

    }

    digitalWrite(rows[r],HIGH); // deactivate row
    delay(DEBOUNCE_DELAY);
  }
}

