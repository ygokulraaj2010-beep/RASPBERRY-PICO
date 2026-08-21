# Project 11 — Servo Controller

## Difficulty

Medium

## 🎯 Objective

Make a servo motor sweep smoothly from 0° to 180° and back — your first motor, and your first use of a library.

## 🧠 What You Will Learn

- What a **servo motor** is and how hobby servos are positioned
- Including and using a **library** (`#include <Servo.h>`)
- `attach()`, `write()`, and why servos need time between moves
- PWM at 50 Hz: how a pulse *width* becomes an angle

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| Micro servo | `wokwi-servo` | 1 |

## 🔌 Wiring

| Servo wire | Meaning | Connects to Pico |
| ---------- | ------- | ---------------- |
| Orange/Yellow (`PWM`) | Signal | GP15 (Physical Pin 20) |
| Red (`V+`) | Power | 3V3 (Physical Pin 36) |
| Brown/Black (`GND`) | Ground | GND.1 (Physical Pin 3) |

> On real hardware with several servos or heavy loads, power the servo from an external 5 V supply and connect only the grounds together.

## ⚙️ How It Works

Hobby servos expect a control pulse every 20 ms (50 Hz):

- ~1 ms pulse → 0°
- ~1.5 ms pulse → 90°
- ~2 ms pulse → 180°

The `Servo` library generates these pulses automatically on any GPIO. You just call `servo.write(angle)`. The `delay(15)` after each step gives the motor time to actually reach the position — without it the servo would lag behind the numbers.

## 💻 Code (`sketch.ino`)

```cpp
#include <Servo.h>

const int SERVO_PIN = 15;
Servo myServo;

void setup() {
  myServo.attach(SERVO_PIN);
}

void loop() {
  for (int angle = 0; angle <= 180; angle++) {   // up
    myServo.write(angle);
    delay(15);
  }
  for (int angle = 180; angle >= 0; angle--) {   // down
    myServo.write(angle);
    delay(15);
  }
}
```

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`. The simulated servo horn visibly rotates.

## ▶️ How to Run

- **Wokwi:** press ▶ Play and watch the horn sweep.
- **Hardware:** compile for the Pico; any SG90-style micro servo works.

## ✅ Expected Result

The servo arm sweeps slowly to one end (0°), pauses briefly at each end, sweeps to the other end (180°), and repeats forever.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Servo jitters or doesn't move | Check all three wires; signal must be on GP15. |
| Compile error: `Servo.h not found` | Select a Pi Pico/RP2040 board — the core bundles `Servo`. |
| Servo buzzes at the ends | Real servos strain against their hard stops; limit your range (e.g. 5–175). |

## 🚀 Challenge

Add two buttons on GP16/GP17 that nudge the servo ±10° per press instead of auto-sweeping.

## 💡 Future Improvements

- Move to positions entered in the Serial Monitor.
- Control the angle with a potentiometer — that's Project 12!
