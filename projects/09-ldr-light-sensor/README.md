# Project 09 — LDR Light Sensor

## Difficulty

Medium

## 🎯 Objective

Measure light with a photoresistor (LDR) module and print raw readings, voltage and approximate **lux** values in the Serial Monitor.

## 🧠 What You Will Learn

- What a **photoresistor/LDR** is (resistance changes with light)
- Reading an analog sensor on `A0` (= GP26)
- Converting ADC counts → volts → resistance → lux
- Printing formatted sensor data

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| LDR sensor module | `wokwi-photoresistor-sensor` | 1 |

The module contains the LDR plus a fixed 10 kΩ resistor in a divider — no extra parts needed.

## 🔌 Wiring

| Module pin | Connects to Pico | Physical Pin |
| ---------- | ---------------- | ------------ |
| `AO` (analog out) | GP26 (`A0`) | 31 |
| `VCC` | 3V3 | 36 |
| `GND` | GND.1 | 3 |

(`DO`, the digital output, is not used here.)

## ⚙️ How It Works

On this module the LDR sits between VCC and AO, with a 10 kΩ resistor from AO to GND. More light → LDR resistance drops → voltage on AO **drops**. So:

```text
Bright room  → low reading (e.g. ~200)
Dark room    → high reading (e.g. ~850)
```

The code converts each reading into volts, then into LDR resistance using the voltage-divider formula, then into lux using the datasheet model (`GAMMA = 0.7`, `RL10 = 50` — matching the module's attributes).

## 💻 Code (`sketch.ino`)

Key part:

```cpp
int rawValue = analogRead(A0);                // 0..1023
float voltage = rawValue * 3.3 / 1023.0;      // 0..3.3 V
float resistance = 10000.0 * voltage / (3.3 - voltage);
float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance,
                1.0 / GAMMA);
```

(The full version guards against divide-by-zero and prints every 250 ms.)

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`. To simulate different lighting, edit the sensor's `lux` attribute in `diagram.json` (e.g. `"10"` = twilight, `"500"` = office, `"10000"` = daylight) and restart.

## ▶️ How to Run

- **Wokwi:** press ▶ Play and watch the Serial Monitor.
- **Hardware:** compile for the Pico; most 3/4-pin LDR modules work identically (AO/VCC/GND).

## ✅ Expected Result

Serial Monitor lines like:

```text
Raw: 853  Voltage: 2.75 V  Lux: 9.9
```

Lower numbers when "bright" (`lux` attribute large), higher when "dark".

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Always reads 1023 | AO wire loose or connected to DO instead of AO. |
| Always reads 0 | VCC missing — check 3V3 connection. |
| Lux shows nonsense/huge numbers | The `GAMMA`/`RL10` constants must match the module's attributes (defaults 0.7 / 50). |
| Values seem inverted | That's normal for this module: brighter light → lower output. |

## 🚀 Challenge

Add an LED that turns on when lux drops below 50 — you'll build exactly that properly in Project 10!

## 💡 Future Improvements

- Plot readings over time (Serial Plotter).
- Average several readings for smoother data.
