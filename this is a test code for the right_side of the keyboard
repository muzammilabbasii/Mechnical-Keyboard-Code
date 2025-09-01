#include <Keyboard.h>

// --------------------
// Matrix pin assignments
const byte rows[6] = {2, 3, 4, 5, 6, 7};
const byte cols[11] = {8, 9, 10, 14, 15, 16, A0, A1, A2, A3, 0};

#define ROWS 6
#define COLS 11

// --------------------
// Right-half keymap (uint8_t allows ASCII + special keys)
uint8_t keymap[ROWS][COLS] = {
  // Row 1: F9–Pause
  {KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINT_SCREEN, KEY_SCROLL_LOCK, KEY_PAUSE, 0, 0, 0, 0},

  // Row 2: 0 – Backspace + Insert/Home/PageUp + NumLock row
  {'0','-','=', KEY_BACKSPACE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP,
   KEY_NUM_LOCK, KEY_KP_SLASH, KEY_KP_ASTERISK, KEY_KP_MINUS},

  // Row 3: Brackets + Delete/End/PageDown + Numpad 7–9
  {0,'[',']','\\', KEY_DELETE, KEY_END, KEY_PAGE_DOWN,
   KEY_KP_7, KEY_KP_8, KEY_KP_9, 0},

  // Row 4: ; ' Enter + Numpad 4–6 +
  {';','\'',0, KEY_RETURN, 0,0,0,
   KEY_KP_4, KEY_KP_5, KEY_KP_6, KEY_KP_PLUS},

  // Row 5: . / Right Shift + Up + Numpad 1–3
  {'.','/',0, KEY_RIGHT_SHIFT, 0, KEY_UP_ARROW, 0,
   KEY_KP_1, KEY_KP_2, KEY_KP_3, 0},

  // Row 6: Alt, Win, Ctrl, Arrows + Numpad 0, DOT, Enter
  {KEY_LEFT_ALT, 0, KEY_LEFT_GUI, KEY_LEFT_CTRL,
   KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW,
   0, KEY_KP_0, KEY_KP_DOT, KEY_KP_ENTER}
};

// --------------------
// State tracking
bool keyState[ROWS][COLS] = {false};

void setup() {
  Keyboard.begin();

  // Set up row pins
  for (byte r = 0; r < ROWS; r++) {
    pinMode(rows[r], OUTPUT);
    digitalWrite(rows[r], HIGH);
  }

  // Set up column pins
  for (byte c = 0; c < COLS; c++) {
    pinMode(cols[c], INPUT_PULLUP);
  }
}

void loop() {
  const int DEBOUNCE_DELAY = 5;

  for (byte r = 0; r < ROWS; r++) {
    digitalWrite(rows[r], LOW); // activate row

    for (byte c = 0; c < COLS; c++) {
      uint8_t k = keymap[r][c];
      if (k == 0) continue; // no key in this position

      bool pressed = (digitalRead(cols[c]) == LOW);

      if (pressed && !keyState[r][c]) {
        Keyboard.press(k);
        keyState[r][c] = true;
      } 
      else if (!pressed && keyState[r][c]) {
        Keyboard.release(k);
        keyState[r][c] = false;
      }
    }

    digitalWrite(rows[r], HIGH); // deactivate row
    delay(DEBOUNCE_DELAY);
  }
}
