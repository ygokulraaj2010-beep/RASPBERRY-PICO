# Project 08 — Potentiometer LED Dimmer

## Difficulty

Medium

## 🎯 Objective

Turn a knob and smoothly change an LED's brightness from fully off to fully bright — your first **analog input**.

## 🧠 What You Will Learn

- What **ADC** (Analog-to-Digital Conversion) is
- Reading the Pico's ADC with `analogRead()` on pin `A0` (= GP26)
- Scaling values with `map()`
- Outputting variable brightness with `analogWrite()` (PWM)
- Printing status updates *without* blocking using `millis()`

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| Potentiometer | `wokwi-potentiometer` | 1 |
| Red LED | `wokwi-led` | 1 |
| 220 Ω resistor | `wokwi-resistor` | 1 |

## 🔌 Wiring

| Component pin | Connects to Pico | Physical Pin |
| ------------- | ---------------- | ------------ |
| Pot `SIG` | GP26 (`A0`) | 31 |
| Pot `VCC` | 3V3 | 36 |
| Pot `GND` | GND.1 | 3 |
| LED (+ via 220 Ω) | GP15 | 20 |
| LED (−) | GND.2 | 8 |

> Only GP26, GP27 and GP28 can read analog signals — they are connected to the RP2040's internal ADC.

## ⚙️ How It Works

The potentiometer is an adjustable voltage divider: turning the knob changes the voltage on `SIG` between 0 V and 3.3 V. The ADC converts that voltage into a number:

```text
0 V → 0        1.65 V → ~512       3.3 V → 1023
```

`map(rawValue, 0, 1023, 0, 255)` rescales that number to the 0–255 range that `analogWrite()` uses for PWM brightness. Knob position becomes light level!

## 💻 Code (`sketch.ino`)

```cpp
const int POT_PIN = A0;
const int LED_PIN = 15;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int rawValue = analogRead(POT_PIN);              // 0..1023
  int brightness = map(rawValue, 0, 1023, 0, 255); // 0..255
  analogWrite(LED_PIN, brightness);
}
```

(The full version also prints values every 500 ms using `millis()`.)

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`. Click the potentiometer and drag its slider while watching the LED.

## ▶️ How to Run

- **Wokwi:** press ▶ Play, then drag the potentiometer knob.
- **Hardware:** compile for the Pico; use any 10 kΩ rotary potentiometer.

## ✅ Expected Result

- Knob at minimum → LED off.
- Knob in middle → LED half-bright (~512 raw).
- Knob at maximum → LED full brightness.
- The Serial Monitor prints the live numbers.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Value only reads 0 or 1023 | `SIG` wire may be loose or on the wrong pot pin. SIG is the middle wiper. |
| LED always full bright | Check `map()` arguments are `(raw, 0, 1023, 0, 255)`. |
| Compile error: `'A0' was not declared` | Board must be set to a Pi Pico/RP2040 board where `A0` = GP26. |

## 🚀 Challenge

Reverse the direction (max knob = dimmest LED) by swapping two numbers inside `map()`. Then make values below 100 snap to completely off.

## 💡 Future Improvements

- Fade smoothly toward the target instead of jumping instantly.
- Replace the LED with a servo (Project 12) or use the same reading for a bar graph (Project 18).
