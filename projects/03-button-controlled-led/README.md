# Project 03 — Button Controlled LED

## Difficulty

Easy

## 🎯 Objective

Read a push button and light an LED **while** the button is held down — your first digital input, now in Arduino C++.

## 🧠 What You Will Learn

- `pinMode(pin, INPUT_PULLUP)` — enabling the internal pull-up resistor
- Why pressed reads **LOW** with a pull-up
- Reading inputs with `digitalRead()` and deciding with `if / else`
- Wiring a button without any external resistor

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| Push button | `wokwi-pushbutton` | 1 |
| Red LED | `wokwi-led` | 1 |
| 220 Ω resistor | `wokwi-resistor` | 1 |

## 🔌 Wiring

| Connection | From | To |
| ---------- | ---- | -- |
| Button side 1 | GP14 (Physical Pin 19) | button pin `1.l` |
| Button side 2 | GND.1 (Physical Pin 3) | button pin `2.l` |
| LED | GP15 (Physical Pin 20) → 220 Ω → anode (+) | cathode (−) → GND.2 (Physical Pin 8) |

The button uses diagonal pins (`1.l` and `2.l`) because pins on the same side are always connected internally.

## ⚙️ How It Works

`INPUT_PULLUP` switches on an internal resistor that gently holds the input at 3.3 V (= `HIGH`). Pressing the button connects the pin straight to GND, so it reads `LOW`.

That's why **pressed = LOW**. The code turns the LED on whenever it sees `LOW`.

## 💻 Code (`sketch.ino`)

```cpp
const int BUTTON_PIN = 14;
const int LED_PIN    = 15;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {  // LOW = pressed
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}
```

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`, then click the button in the circuit to press it.

## ▶️ How to Run

- **Wokwi:** press ▶ Play, click/hold the push button.
- **Hardware:** compile for "Raspberry Pi Pico" in the Arduino IDE or download the UF2 from Wokwi (F1).

## ✅ Expected Result

- Released → LED off.
- Held → LED on.
- Release → LED instantly off.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| LED works backwards | Your button is wired to 3V3 instead of GND. Keep it simple: button → GND + `INPUT_PULLUP`. |
| Nothing happens when pressing | Both wires may be on the same side of the button (`1.l`/`1.r` are joined). Use one pin from each side, e.g. `1.l` and `2.l`. |
| Random flicker without pull-up | Make sure you wrote `INPUT_PULLUP`, not `INPUT`. |

## 🚀 Challenge

Invert the logic: LED ON by default and OFF while pressed — change only the comparison (`== LOW` ↔ `== HIGH`).

## 💡 Future Improvements

- Detect *presses* instead of *holding* — that's Project 05.
- Add a second button controlling a second LED.
