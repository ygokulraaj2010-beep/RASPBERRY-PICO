# Project 01 — LED Blink

## Difficulty

Easy

## 🎯 Objective

Make a single LED turn ON and OFF (blink) once per second — the "Hello, World!" of embedded programming, now in Arduino C++.

## 🧠 What You Will Learn

- What a **GPIO** pin is and how `pinMode()` / `digitalWrite()` control it
- The Arduino program structure: `setup()` runs once, `loop()` repeats forever
- Why LEDs need a **resistor** and which leg is + and −
- The difference between **Physical Pin numbers** and **GPIO numbers**

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| Red LED | `wokwi-led` | 1 |
| 220 Ω resistor | `wokwi-resistor` | 1 |

## 🔌 Wiring

| From (Pico) | Physical Pin | To |
| ----------- | ------------ | -- |
| GP15 | 20 | Resistor (220 Ω) → LED anode (+, long leg) |
| GND | 3 (`GND.1`) | LED cathode (−, short leg) |

> ⚠️ **Never confuse physical pin number with GPIO number!**
> Here we use **GPIO: GP15**, which lives on **Physical Pin: 20**.
> In Arduino code you always write the GPIO number: `pinMode(15, OUTPUT)`.

## ⚙️ How It Works

A GPIO output pin works like a tiny software-controlled switch:

- `digitalWrite(LED_PIN, HIGH)` → 3.3 V → current flows through the resistor into the LED → light!
- `digitalWrite(LED_PIN, LOW)` → 0 V → no current → dark.

The resistor limits current (~10 mA) so the LED is safe. `delay(500)` pauses half a second, giving a visible blink.

## 💻 Code (`sketch.ino`)

```cpp
const int LED_PIN = 15;   // GP15 = physical pin 20

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);   // LED ON
  delay(500);                    // wait 0.5 s
  digitalWrite(LED_PIN, LOW);    // LED OFF
  delay(500);
}
```

## 🧪 Wokwi Simulation

Use the **Arduino "Pi Pico" template** (https://wokwi.com/projects/new/pi-pico) — *not* the MicroPython one — then paste:

- `sketch.ino` from this folder into the code editor
- `diagram.json` from this folder over the default one

> Using the MicroPython template with this `.ino` file causes exactly the
> "invalid preprocessing directive" build error — that error means the wrong
> language template was selected.

## ▶️ How to Run

- **Wokwi:** press the green ▶ Play button.
- **Real hardware:** press F1 in Wokwi → "Download UF2 Binary", hold BOOTSEL while plugging the Pico into USB, copy the UF2 onto the `RPI-RP2` drive. Or compile in the Arduino IDE with the "Raspberry Pi Pico/RP2040" core installed.

## ✅ Expected Result

The red LED blinks **ON 0.5 s → OFF 0.5 s**, forever. The Serial Monitor prints "LED ON"/"LED OFF" as it happens.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Build error mentions `.ino` or preprocessing directives | You are using the MicroPython template — recreate the project with the Arduino Pi Pico template. |
| LED never lights | Long leg (+/anode) goes to GP15 through the resistor; short leg (−/cathode) to GND. |
| Nothing happens at all | Check the console for compile errors and confirm the simulation actually started. |
| Wrong pin blinks on real hardware | You may have counted physical pins instead of GPIOs — GP15 = physical pin 20. |

## 🚀 Challenge

The Pico also has a **built-in LED** on GPIO 25 (Wokwi simulates it). Blink it instead by changing one line: `const int LED_PIN = 25;` — no wiring needed! Then blink both alternately.

## 💡 Future Improvements

- Make the speed adjustable with a variable.
- Move on to Project 02 to control several LEDs with an array.
