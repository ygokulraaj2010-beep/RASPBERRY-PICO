# Project 20 — Mini Sensor Dashboard

## Difficulty

Hard

## 🎯 Objective

The graduation project: combine **four** components — an I2C LCD, a temperature/humidity sensor, a potentiometer and a light sensor — into one working dashboard that updates live.

## 🧠 What You Will Learn

- **I2C communication**: two wires (SDA/SCL) talking to a display
- Managing **multiple devices at once** without conflicts
- Scheduling different tasks at different rates ("fast lane" vs "slow lane" with `millis()`)
- Formatting text into fixed-width LCD lines with `snprintf()`
- Integrating every concept from Projects 01–19

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| LCD 16×2 (I2C backpack) | `wokwi-lcd1602` | 1 |
| DHT22 sensor | `wokwi-dht22` | 1 |
| Potentiometer | `wokwi-potentiometer` | 1 |
| LDR module | `wokwi-photoresistor-sensor` | 1 |

## 🔌 Wiring

| Component | Pin | GPIO | Physical Pin |
| --------- | --- | ---- | ------------ |
| LCD1602 | SDA | GP4 | 6 |
| LCD1602 | SCL | GP5 | 7 |
| LCD1602 | VCC / GND | 3V3 / GND.1 | 36 / 3 |
| DHT22 | data (`SDA`) | GP16 | 21 |
| DHT22 | VCC / GND | 3V3 / GND.2 | 36 / 8 |
| Potentiometer | SIG | GP26 (`A0`) | 31 |
| LDR | AO | GP27 (`A1`) | 32 |

> The Pico's hardware I2C0 uses GP4 (data) + GP5 (clock) by default — the LCD shares these two wires with the microcontroller only; sensors stay on their own pins.

## ⚙️ How It Works

Three devices, three rhythms:

- The **DHT22** can only be read every ~2 s → "slow lane": its values go on line 1.
- The **potentiometer and LDR** respond instantly → "fast lane" (every 300 ms): their raw values fill line 2.
- Both timers run from `millis()` inside the same `loop()` — no `delay()` blocking anything.

`snprintf(line, sizeof(line), "T:%4.1fC H:%3.0f%%", t, h)` builds exactly 16-character strings so old characters never linger on the display.

## 💻 Code (`sketch.ino`)

Key structure:

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(16, DHT22);

void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();
}

void loop() {
  if (millis() - lastFastRead > 300) { /* pot + LDR -> line 2 */ }
  if (millis() - lastTempRead > 2000) { /* DHT22 -> line 1 */ }
}
```

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste all files from this folder. During simulation: drag the pot slider, edit the LDR's `lux` attribute between runs, click the DHT22 for live sliders.

## ▶️ How to Run

- **Wokwi:** press ▶ Play.
- **Hardware:** compile for the Pico; install the same three libraries in the Arduino IDE. Most I2C LCDs use address `0x27` (try `0x3F` if blank).

## ✅ Expected Result

```text
Line 1: T: 24.0C H: 40%
Line 2: P: 512 L: 300
```

- Dragging the knob changes `P:` instantly.
- Changing light changes `L:`.
- Clicking the DHT22 sliders updates `T:/H:` within 2 seconds.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| LCD backlight on but blank | Wrong I2C address — change `0x27` to `0x3F`. |
| Compile error: `LiquidCrystal_I2C.h not found` | Add the "LiquidCrystal I2C" library (see `libraries.txt`). |
| Garbage characters on screen | Your printed string exceeded 16 chars — keep the `snprintf` widths. |
| Sensors interfere with LCD | They don't share wires — check SDA/SCL really are on GP4/GP5 and sensors on GP16/GP26/GP27. |

## 🚀 Challenge

Add an alarm: if temperature passes 30 °C, blink the LCD backlight or beep a buzzer. Then try swapping line contents every few seconds to fit more info!

## 💡 Future Improvements

- Log readings to Serial as CSV for graphing.
- Send the data over WiFi — that's where the next course level begins!
