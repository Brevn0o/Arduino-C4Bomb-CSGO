# Arduino C4 Bomb (CS:GO Inspired)
An Arduino prop that recreates the arming and defusing flow of the CS:GO C4 bomb. A 4×4 keypad lets players set a custom code, a 16×2 LCD drives in-game style feedback, and a buzzer/LED combo provides auditory and visual cues
## Features
- Supports custom passcode entry up to 16 characters (digits and A–D).
- LCD shows arming feedback, obfuscated passcode, and live countdown.
- Buzzer and LED pulse each second; wrong guesses shorten the interval to ramp tension.
## Hardware
- Arduino Mega 2560 (or another Arduino with digital pins 3, 4, 7–12, 38–45 available).
- 16×2 LCD display (parallel interface, HD44780-compatible).
- 4×4 matrix keypad.
- Passive buzzer.
- LED with current-limiting resistor.
- Breadboard + jumper wires.
### Pin Mapping
```
LCD
  RS -> 7
  EN -> 8
  D4 -> 9
  D5 -> 10
  D6 -> 11
  D7 -> 12
Keypad
  Row0 -> 38
  Row1 -> 39
  Row2 -> 40
  Row3 -> 41
  Col0 -> 42
  Col1 -> 43
  Col2 -> 44
  Col3 -> 45
Outputs
  Buzzer -> 4
  LED    -> 3
```
## Software Requirements
- Arduino IDE 2.x or Arduino CLI.
- Libraries (available through the Library Manager):
  - `LiquidCrystal` (built-in with the Arduino IDE).
  - `Keypad` by Mark Stanley & Alexander Brevig.
## Getting Started
1. Clone or download this repository.
2. Open `sketch_oct20a/sketch_oct20a.ino` in the Arduino IDE.
3. Install the required libraries if they are not already present.
4. Select your Arduino board/port and upload the sketch.
## Operating the Prop
When the bomb powers on:
1. **Set a passcode:** Use the keypad to enter a code (maximum 16 characters). Use `*` to clear.
2. **Arm the bomb:** Press `#`. The LCD briefly masks the code before switching to the countdown screen.
3. **Countdown:** The display shows seconds remaining. The LED and buzzer tick every second. Each failed attempt lowers the tick interval by 100 ms, intensifying the alarm.
4. **Defuse attempt:** Enter the guessed code and press `#`.
   - Correct code → “DEFUSED” message; countdown stops.
   - Incorrect code → LCD flashes “WRONG PASSWORD”, buzzer chirps, and interval shortens.
   - `*` during countdown clears the current guess but not the timer.
5. **Explosion:** If the timer reaches zero, “BOOM” is displayed and the buzzer + LED stay on for five seconds.
Serial output mirrors password entry and arming state, which helps with debugging or integrating with other control systems.
## Configuration
You can tweak gameplay balance by editing the constants at the top of `sketch_oct20a.ino`:
- `timer` (seconds) – default `180`. Increase for longer rounds.
- `interval` (milliseconds) – default `1000`. Controls tick rate. Lower values speed up the beep/flash cycle.
- `rowPins` / `colPins`, LCD pins, `buzzer`, `led` – adjust if your wiring differs.
