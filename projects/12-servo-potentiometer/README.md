# Project 12 — Servo + Potentiometer

## Difficulty

Medium

## 🎯 Objective

Build a classic "knob controls motor" system: turn the potentiometer and the servo follows your hand in real time — like an RC car steering wheel.

## 🧠 What You Will Learn

- Combining **input** (Project 08) with **output** (Project 11)
- `map()` to rescale one range onto another: 0–1023 → 0–180
- Building responsive control loops
- Reading and writing in the same `loop()`

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| Potentiometer | `wokwi-potentiometer` | 1 |
| Micro servo | `wokwi-servo` | 1 |

## 🔌 Wiring

| Component pin | Connects to Pico | Physical Pin |
| ------------- | ---------------- | ------------ |
| Pot `SIG` | GP26 (`A0`) | 31 |
| Pot `VCC` | 3V3 | 36 |
| Pot `GND` | GND.2 | 8 |
| Servo `PWM` (signal) | GP15 | 20 |
| Servo `V+` | 3V3 | 36 |
| Servo `GND` | GND.1 | 3 |

## ⚙️ How It Works

Each cycle of `loop()`:

1. Read the knob: `analogRead()` → 0…1023.
2. Convert units: `map(rawValue, 0, 1023, 0, 180)` → degrees.
3. Command the motor: `servo.write(angle)`.
4. Wait 15 ms so the servo can keep up.

This read→convert→act cycle runs ~66 times per second, so movement feels instant. The same pattern drives joysticks, steering, camera gimbals — anything analog.

## 💻 Code (`sketch.ino`)

```cpp
#include <Servo.h>

Servo myServo;
const int POT_PIN = A0;
const int SERVO_PIN = 15;

void setup() {
  myServo.attach(SERVO_PIN);
  Serial.begin(115200);
}

void loop() {
  int rawValue = analogRead(POT_PIN);            // 0..1023
  int angle = map(rawValue, 0, 1023, 0, 180);    // 0..180 deg
  myServo.write(angle);
  delay(15);
}
```

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`. Click the potentiometer during simulation and drag its slider.

## ▶️ How to Run

- **Wokwi:** press ▶ Play, drag the knob — the horn follows.
- **Hardware:** compile for the Pico; wire as above.

## ✅ Expected Result

- Knob fully left → servo at 0°.
- Knob centered → servo at ~90°.
- Knob fully right → servo at 180°.
- Movement tracks the knob smoothly, both directions.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Servo jumps between only two positions | Pot SIG wire loose → reading is floating. Re-seat it on GP26. |
| Movement backwards from expected | Swap pot VCC/GND wires, or reverse the `map()` output range (`0, 180` → `180, 0`). |
| Servo stutters near ends | Normal for cheap servos at hard stops — use `map(..., 10, 170)` for safety margin. |

## 🚀 Challenge

Make the servo move only when the angle actually changes by 2° or more (store `lastAngle` and compare). Why does this reduce jitter?

## 💡 Future Improvements

- Add smoothing (average of last N readings).
- Replace the pot with the LDR to build a "sun-tracking" dial.
