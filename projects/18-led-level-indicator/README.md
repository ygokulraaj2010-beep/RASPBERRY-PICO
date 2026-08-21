# Project 18 — LED Level Indicator

## Difficulty

Medium-Hard

## 🎯 Objective

Turn a knob and watch a 6-LED bar graph fill from empty to full — exactly like a volume meter, battery indicator, or water tank level.

## 🧠 What You Will Learn

- Converting a continuous range into discrete **steps**
- `map()` with an output bigger than the input (1023 → 6 levels)
- The `i < level ? HIGH : LOW` trick for bar graphs
- Optimizing: only update outputs when the value *changes*

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| Potentiometer | `wokwi-potentiometer` | 1 |
| LED (rainbow colors) | `wokwi-led` | 6 |
| 220 Ω resistor | `wokwi-resistor` | 6 |

## 🔌 Wiring

| Bar LED | GPIO | Physical Pin |
| ------- | ---- | ------------ |
| 1 (red) | GP10 | 14 |
| 2 (orange) | GP11 | 15 |
| 3 (yellow) | GP12 | 16 |
| 4 (lime) | GP13 | 17 |
| 5 (cyan) | GP14 | 19 |
| 6 (green) | GP15 | 20 |

Each GPIO → 220 Ω → anode (+); cathodes (−) → GND pins 8…38.
Potentiometer: SIG → GP26 (`A0`, Physical Pin 31), VCC → 3V3 (Pin 36), GND → GND.1 (Pin 3).

## ⚙️ How It Works

The knob gives 0–1023; we want 0–6 "bars":

```cpp
int level = map(rawValue, 0, 1024, 0, 7);   // 0..6
```

Then one loop decides each LED: light it if its index is below the level. LED 4 on means "level ≥ 4".

The `lastLevel` check means the LEDs are only rewritten when the bar actually changes — a tiny optimization that's good practice everywhere.

## 💻 Code (`sketch.ino`)

```cpp
const int ledPins[6] = {10, 11, 12, 13, 14, 15};

void showLevel(int level) {
  for (int i = 0; i < 6; i++)
    digitalWrite(ledPins[i], (i < level) ? HIGH : LOW);
}

void loop() {
  int rawValue = analogRead(A0);
  showLevel(map(rawValue, 0, 1024, 0, 7));
}
```

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`. Drag the pot slider during simulation.

## ▶️ How to Run

- **Wokwi:** press ▶ Play, move the knob.
- **Hardware:** compile for the Pico; wire as above.

## ✅ Expected Result

Knob low → 0–2 LEDs; centered → ~3 LEDs; high → all 6. The Serial Monitor prints the raw value and current level whenever it changes.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| All LEDs always on | Check `map()` output range is `(…, 0, 7)` giving 0–6, not something always > 6. |
| Middle of the bar skips | That's the math working correctly at boundaries — try mapping to 12 and dividing by 2 for finer control. |
| One segment dead | Compare that LED's GPIO wire against the table. |

## 🚀 Challenge

Make the top two segments blink when the level reaches maximum (a "full!" warning). Hint: you'll need the blinking logic from Project 17 inside your highest level case.

## 💡 Future Improvements

- Swap the potentiometer for the LDR module to build a real light meter (Projects 09/10 wiring!).
- Use a real `wokwi-led-bar-graph` part instead of six separate LEDs.
