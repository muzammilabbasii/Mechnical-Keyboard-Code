# Mechnical-Keyboard-Code
Mechnical-Keyboard-Code

This repository contains the firmware for a custom split mechanical keyboard, built using Arduino Pro Micro controllers. Unlike traditional split keyboards, this design does not use I²C or TRRS communication between halves. Instead, both the left-hand side and right-hand side are completely independent, each with its own microcontroller and USB connection.

That means:

Each half is flashed separately

Each half shows up as its own keyboard device when plugged into a computer

Together, they form a full keyboard when both halves are connected

✨ How It Works

Each side uses a key matrix (rows × columns) to detect key presses.

The Arduino scans each row/column, and when a switch is pressed, the firmware sends the correct keycode to the computer using the Arduino Keyboard library.

Since pins are limited, the left-hand side is built as a 6×10 matrix, while the right-hand side uses a 6×11 matrix (to include the numpad and navigation keys).

Both halves run the Keyboard.h library and independently send key signals over USB.

🛠️ Hardware Used

2 × Arduino Pro Micro (ATmega32U4) (one for each half)

Mechanical switches (Cherry MX or compatible)

Diodes (1N4148) — one per switch for matrix scanning

Keycaps

2 × USB cables (each half connects to PC separately)

Handwired matrix wiring or custom PCB

📂 Firmware Files

keyboard_lefthandside_code.ino → Firmware for the left-hand side (6×10)

keyboard_righthand.code.ino → Firmware for the right-hand side (6×11)

🎹 Keymap & Matrix
Left-Hand Side (6×10)

Rows (pins): {2, 3, 4, 5, 6, 7}

Cols (pins): {8, 9, 10, 14, 15, 16, A0, A1, A2, A3}

Layout (default):
write the letters in small alphabet and i used the [ , ] pin for [ p ] and the [ . ] for [ , ] 
i will show it in the image below 
i have done it because the lefthand side has the capslock and 
only the p would not be uppercased when pressed

[Esc] [F1] [F2] [F3] [F4] [F5] [F6] [F7] [F8]  
[ 1 ] [ 2 ] [ 3 ] [ 4 ] [ 5 ] [ 6 ] [ 7 ] [ 8 ] [ 9 ] [Back]  
[Tab] [ Q ] [ W ] [ E ] [ R ] [ T ] [ Y ] [ U ] [ I ] [ O ]   the [ p ] key is physically here after [ o ] but in matrix it is after [ m ] 
[Caps] [ A ] [ S ] [ D ] [ F ] [ G ] [ H ] [ J ] [ K ] [ L ]  
[Shift] [ Z ] [ X ] [ C ] [ V ] [ B ] [ N ] [ M ] [ P ] [ , ]  
[Ctrl] [GUI] [Alt] [Space] [Fn] [Alt] [Ctrl] [←] [↓] [→]  

Right-Hand Side (6×11)

Rows (pins): {2, 3, 4, 5, 6, 7}

Cols (pins): {8, 9, 10, 14, 15, 16, A0, A1, A2, A3, RX1} here <----
if you are using [ rx1 ] pin 
it will show you an error so instead of writing [ rx1 ] write [ 0 ]

Layout (default):

[F9] [F10] [F11] [F12] [PrtSc] [ScrLk] [Pause]  
[ 0 ] [ - ] [ = ] [Back] [Ins] [Home] [PgUp] [NumLk] [ / ] [ * ] [ - ]  
[ [ ] [ ] ] [ \ ] [Del] [End] [PgDn] [ 7 ] [ 8 ] [ 9 ]  
[ ; ] [ ' ] [Enter] [ 4 ] [ 5 ] [ 6 ] [ + ]  
[ . ] [ / ] [Shift] [ ↑ ] [ 1 ] [ 2 ] [ 3 ]  
[Alt] [Menu] [GUI] [Ctrl] [ ← ] [ ↓ ] [ → ] [ 0 ] [ . ] [Enter]  

🚀 Installation

Clone the repository:

git clone https://github.com/muzammilabbasii/Mechnical-Keyboard-Code.git


Open the .ino files in the Arduino IDE
.

Connect your Arduino Pro Micro.

Flash keyboard_lefthandside_code.ino onto the left-hand side.

Flash keyboard_righthand.code.ino onto the right-hand side.

Connect both halves to your PC via USB.

📸 Example Build

![Mechanical Keyboard](images/IMG20250901223742.jpg)



🤝 Contributing

Contributions are welcome! If you create new layouts, improve the firmware, or adapt it for different hardware, feel free to submit a pull request.

📜 License

This project is licensed under the MIT License.
