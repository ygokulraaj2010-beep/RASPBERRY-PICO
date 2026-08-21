# Project 07 — RGB LED Controller

## Difficulty

Easy-Medium

## 🎯 Objective

Mix any color from red, green and blue light using one RGB LED and PWM — including secondary colors like yellow, cyan and magenta.

## 🧠 What You Will Learn

- How **RGB color mixing** works (light, not paint!)
- What **PWM** (`analogWrite()`) does and why an LED can be "half on"
- Writing functions with parameters: `setColor(r, g, b)`
- Common-cathode wiring of an RGB LED

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| RGB LED (common cathode) | `wokwi-rgb-led` | 1 |
| 220 Ω resistor | `wokwi-resistor` | 3 |

## 🔌 Wiring

The Wokwi RGB LED's `common` attribute is set to **cathode** in `diagram.json`, so COM goes to **GND** and each color pin is driven HIGH/PWM.

| LED pin | Through | GPIO | Physical Pin |
| ------- | ------- | ---- | ------------ |
| R (red) | 220 Ω | GP13 | 17 |
| G (green) | 220 Ω | GP12 | 16 |
| B (blue) | 220 Ω | GP11 | 15 |
| COM | — | GND.1 | 3 |

## ⚙️ How It Works

`analogWrite(pin, value)` uses hardware PWM: the pin switches on/off very fast, and `value` (0–255) sets the percentage of time it stays HIGH. Your eye averages this into "brightness".

Mixing works like painting with light:

- Yellow = red + green
- Cyan = green + blue
- Magenta = red + blue
- White = all three at full power

## 💻 Code (`sketch.ino`)

```cpp
const int RED_PIN = 13, GREEN_PIN = 12, BLUE_PIN = 11;

void setColor(int r, int g, int b) {
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}

void loop() {
  setColor(255, 0, 0);   delay(1000);  // red
  setColor(0, 255, 0);   delay(1000);  // green
  setColor(0, 0, 255);   delay(1000);  // blue
  setColor(255, 255, 0); delay(1000);  // yellow
  setColor(0, 255, 255); delay(1000);  // cyan
  setColor(255, 0, 255); delay(1000);  // magenta
  setColor(255, 255, 255); delay(1000); // white
}
```

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json` from this folder.

## ▶️ How to Run

- **Wokwi:** press ▶ Play and watch the colors cycle.
- **Hardware:** compile for the Pico; use a common-cathode RGB LED with three 220 Ω resistors.

## ✅ Expected Result

The LED cycles through red → green → blue → yellow → cyan → magenta → white, holding each color ~1.5 s, forever.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Colors look wrong (e.g. yellow shows as blue-ish) | A common-anode LED wired as common-cathode inverts everything — check the `common` attribute is `"cathode"` and COM goes to GND. |
| One channel always off | Trace that channel's resistor wire; check its `analogWrite()` line. |
| Very dim output | Resistors much larger than 220 Ω reduce brightness. |

## 🚀 Challenge

Create your own custom color (try orange ≈ `setColor(255, 100, 0)`), then make a smooth fade from black to white by looping brightness 0→255.

## 💡 Future Improvements

- Fade smoothly between colors instead of jumping.
- Let a potentiometer choose colors (Project 08 shows ADC!).
