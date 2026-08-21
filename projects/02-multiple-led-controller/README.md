# Project 02 — Multiple LED Controller

## Difficulty

Easy

## 🎯 Objective

Control three LEDs (red, yellow, green) and create a "chase" animation that runs left → right, then right → left.

## 🧠 What You Will Learn

- Using **arrays** to manage many GPIO pins with very little code
- `for` loops and array indexing
- Writing a helper function (`allOff()`)
- Reusing Project 01 knowledge at a larger scale

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| Red LED | `wokwi-led` | 1 |
| Yellow LED | `wokwi-led` | 1 |
| Green LED | `wokwi-led` | 1 |
| 220 Ω resistor | `wokwi-resistor` | 3 |

## 🔌 Wiring

Each LED follows the same pattern: **GPIO → 220 Ω resistor → LED anode (+)**, and **LED cathode (−) → GND**.

| LED | GPIO | Physical Pin |
| --- | ---- | ------------ |
| Red | GP13 | 17 |
| Yellow | GP14 | 19 |
| Green | GP15 | 20 |

Grounds can go to any GND pin (this project uses physical pins 3, 8, 13).

## ⚙️ How It Works

Instead of writing three copies of the blink code, we store all pins in an array:

```cpp
const int ledPins[3] = {13, 14, 15};
```

A small loop can then light them in order. The first `for` loop walks the array forward; the second walks it backward. Together they make a back-and-forth "Cylon/Knight Rider" chase.

## 💻 Code (`sketch.ino`)

```cpp
const int ledPins[3] = {13, 14, 15};

void setup() {
  for (int i = 0; i < 3; i++) pinMode(ledPins[i], OUTPUT);
}

void allOff() {
  for (int i = 0; i < 3; i++) digitalWrite(ledPins[i], LOW);
}

void loop() {
  for (int i = 0; i < 3; i++) {           // left -> right
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
  }
  for (int i = 1; i >= 0; i--) {          // right -> left
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
  }
}
```

## 🧪 Wokwi Simulation

Create the project at https://wokwi.com/projects/new/pi-pico (Arduino template!) and paste `sketch.ino` + `diagram.json` from this folder.

## ▶️ How to Run

- **Wokwi:** press ▶ Play.
- **Hardware:** build with the Arduino IDE (Pico/RP2040 core), or use Wokwi's "Download UF2 Binary" (F1) and copy the UF2 to the BOOTSSEL drive.

## ✅ Expected Result

The LEDs light up one after another: red → yellow → green, pause, then green → yellow → red, repeating forever like a moving light.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| One LED never lights | Check its GPIO wire and resistor; confirm the array `{13, 14, 15}` matches your wiring. |
| All LEDs blink together | Two LEDs may share the same breadboard row — separate them. |
| Chase too fast/slow | Adjust `delay(200)` (milliseconds). |
| Compile error about `ledPins` outside scope | Keep the array declared above `setup()` so both functions can see it. |

## 🚀 Challenge

Add a fourth LED on GP12 (physical pin 16): update the array size to `{12, 13, 14, 15}` and change both loop limits. Can you make the pattern bounce without the second loop?

## 💡 Future Improvements

- Store patterns as binary numbers and shift them out bit by bit.
- Use this same idea to build the Traffic Light (Project 04).
