# Project 04 — Traffic Light

## Difficulty

Easy

## 🎯 Objective

Build a working traffic light with red, amber and green LEDs that cycles through a realistic signal sequence — now in Arduino C++.

## 🧠 What You Will Learn

- Organizing multiple outputs into clearly named constants
- Writing and reusing your own **function** (`allOff()`)
- Sequencing with multiple `delay()` steps
- Real-world system thinking (state sequences)

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| Red LED | `wokwi-led` | 1 |
| Yellow (amber) LED | `wokwi-led` | 1 |
| Green LED | `wokwi-led` | 1 |
| 220 Ω resistor | `wokwi-resistor` | 3 |

## 🔌 Wiring

Each LED: **GPIO → 220 Ω → anode (+)**; cathode (−) → GND.

| Color | GPIO | Physical Pin |
| ----- | ---- | ------------ |
| Red | GP13 | 17 |
| Amber | GP14 | 19 |
| Green | GP15 | 20 |

Grounds: physical pins 3, 8, 13 (any GND works).

## ⚙️ How It Works

A traffic light is just a repeating list of states:

1. 🔴 RED — stop (3 s)
2. 🔴🟡 RED + AMBER — get ready (1 s)
3. 🟢 GREEN — go (3 s)
4. 🟡 AMBER — slow down (1 s)

The `allOff()` helper keeps each state clean: turn everything off, then switch on only what that state needs. Because `loop()` runs forever, the sequence repeats automatically.

## 💻 Code (`sketch.ino`)

```cpp
const int RED_PIN = 13, AMBER_PIN = 14, GREEN_PIN = 15;

void allOff() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(AMBER_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
}

void loop() {
  allOff(); digitalWrite(RED_PIN, HIGH);   delay(3000); // stop
  digitalWrite(AMBER_PIN, HIGH);           delay(1000); // get ready
  allOff(); digitalWrite(GREEN_PIN, HIGH); delay(3000); // go
  allOff(); digitalWrite(AMBER_PIN, HIGH); delay(1000); // slow down
}
```

(The full commented version is in `sketch.ino`.)

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico) and paste `sketch.ino` + `diagram.json` from this folder.

## ▶️ How to Run

- **Wokwi:** press ▶ Play and watch the sequence.
- **Hardware:** compile in the Arduino IDE (Pico core) or download the UF2 from Wokwi.

## ✅ Expected Result

Red for 3 s → red+amber for 1 s → green for 3 s → amber alone for 1 s → repeat, forever.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Two LEDs on at wrong times | Check `allOff()` is called between states. |
| Wrong color sequence | Swap the GPIO constants so they match your physical wiring. |
| Sequence too fast to see | Increase the `delay()` values (they are milliseconds). |

## 🚀 Challenge

Add a pedestrian "request" button on GP16 (physical pin 21): when held during the green phase, shorten green to 1 second. Hint: replace the green `delay(3000)` with a loop checking `digitalRead(16) == LOW`.

## 💡 Future Improvements

- Add a beeping buzzer for blind pedestrians (see Project 06).
- Replace fixed delays with a non-blocking timer state machine (`millis()`).
