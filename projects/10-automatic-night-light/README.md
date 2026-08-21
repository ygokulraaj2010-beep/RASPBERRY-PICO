# Project 10 — Automatic Night Light

## Difficulty

Medium

## 🎯 Objective

Combine a sensor with an actuator to make something useful: a lamp that switches itself on when the room goes dark — like real street lights.

## 🧠 What You Will Learn

- **Sensor → decision → actuator**: the core pattern of all automation
- Comparing sensor values against a **threshold**
- Using `? :` conditional output in a print statement
- Tuning a threshold by observing live data

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| LDR sensor module | `wokwi-photoresistor-sensor` | 1 |
| Warm white LED | `wokwi-led` | 1 |
| 220 Ω resistor | `wokwi-resistor` | 1 |

## 🔌 Wiring

| Connection | From | To |
| ---------- | ---- | -- |
| LDR `AO` | GP26 (`A0`, Physical Pin 31) | sensor analog out |
| LDR `VCC` / `GND` | 3V3 (Pin 36) / GND.1 (Pin 3) | power |
| LED (+ via 220 Ω) | GP15 (Physical Pin 20) | lamp |
| LED (−) | GND.2 (Physical Pin 8) | ground |

## ⚙️ How It Works

Remember from Project 09: more light → lower reading. So "is it dark?" becomes one comparison:

```cpp
if (rawValue > DARK_THRESHOLD) { /* turn lamp on */ }
```

The sketch prints every reading so you can watch the number and adjust `DARK_THRESHOLD` yourself.

**Simulating day/night in Wokwi:** the LDR part's `lux` attribute is set to `"5"` (dark) so the lamp starts ON. Open `diagram.json`, change `lux` to e.g. `"500"`, restart — the lamp turns off. That's your "morning".

## 💻 Code (`sketch.ino`)

```cpp
const int LDR_PIN = A0;
const int LED_PIN = 15;
const int DARK_THRESHOLD = 600;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int rawValue = analogRead(LDR_PIN);
  if (rawValue > DARK_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);   // dark -> on
  } else {
    digitalWrite(LED_PIN, LOW);    // bright -> off
  }
  delay(250);
}
```

(The full version also logs the raw value and its decision.)

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`. Play with the `lux` attribute of the sensor between runs.

## ▶️ How to Run

- **Wokwi:** press ▶ Play; the LED should be ON because it starts "dark".
- **Hardware:** compile for the Pico; cover the LDR with your hand to trigger it.

## ✅ Expected Result

- Dark (lux ≤ ~20, reading > 600): LED ON.
- Bright (reading < 600): LED OFF.
- Console shows which state was chosen and why.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Lamp never turns on | Your room may be "too bright": raise `DARK_THRESHOLD` or lower the lux attribute. |
| Lamp always on | Reading stays high — check AO wiring, then lower `DARK_THRESHOLD`. |
| Rapid flickering around the threshold | Normal hysteresis problem! Fix in the Challenge below. |

## 🚀 Challenge

Add **hysteresis** to kill flicker: turn ON above 700, but only turn OFF below 500. You need two constants and two comparisons.

## 💡 Future Improvements

- Fade the lamp in gradually instead of snapping on.
- Add a button to force the lamp on manually (override mode).
