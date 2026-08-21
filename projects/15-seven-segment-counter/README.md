# Project 15 — 7-Segment Counter

## Difficulty

Medium-Hard

## 🎯 Objective

Show digits 0–9 on a real 7-segment display: every button press advances the counter. This is how digital clocks and counters actually work.

## 🧠 What You Will Learn

- Driving **7 LEDs in one package** and mapping segments to pins
- **Bit patterns** (`0b00111111`) and bit shifting (`pattern >> i & 1`)
- Encoding data in lookup tables (arrays)
- Reusing edge detection from Projects 05/13

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| 7-segment display (common cathode) | `wokwi-7segment` | 1 |
| Push button | `wokwi-pushbutton` | 1 |

## 🔌 Wiring

The display's `common` attribute is set to `"cathode"` → COM goes to GND, segments light on HIGH.

| Segment | Position | GPIO | Physical Pin |
| ------- | -------- | ---- | ------------ |
| A | top | GP0 | 1 |
| B | top-right | GP1 | 2 |
| C | bottom-right | GP2 | 4 |
| D | bottom | GP3 | 5 |
| E | bottom-left | GP4 | 6 |
| F | top-left | GP5 | 7 |
| G | middle | GP6 | 9 |
| COM | common | GND.2 | 8 |

Button: GP16 (Physical Pin 21) → `1.l`; GND.1 (Physical Pin 3) → `2.l`. DP is not used.

> On real hardware add a ~220 Ω resistor per segment. In the simulator direct connections are fine.

## ⚙️ How It Works

Each digit is drawn from up to 7 segments. Instead of seven `if` blocks per digit, we store one **byte** per digit — each bit says whether that segment is on:

```text
digit 0 = A B C D E F on, G off  -> 0b00111111
digit 1 = B C on                 -> 0b00000110
```

`displayDigit(n)` loops over the bits: `(pattern >> i) & 1` extracts bit *i*, which becomes segment *i*'s state. One small loop drives any digit!

## 💻 Code (`sketch.ino`)

```cpp
const int segPins[7] = {0, 1, 2, 3, 4, 5, 6};   // A..G

const byte digitPatterns[10] = {
  0b00111111, 0b00000110, 0b01011011, 0b01001111,
  0b01100110, 0b01101101, 0b01111101, 0b00000111,
  0b01111111, 0b01101111
};

void displayDigit(int n) {
  byte pattern = digitPatterns[n];
  for (int i = 0; i < 7; i++)
    digitalWrite(segPins[i], (pattern >> i) & 1 ? HIGH : LOW);
}
```

Plus the familiar press-detection loop advancing `count` 0→9→0.

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`.

## ▶️ How to Run

- **Wokwi:** press ▶ Play, click the button.
- **Hardware:** compile for the Pico; wire segments through resistors.

## ✅ Expected Result

Display starts at 0. Each press advances it: 1, 2, … 9, then wraps back to 0. The Serial Monitor prints the count too.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Segments light wrong / mirrored numbers | Your segment order differs — check the wiring table against `segPins[]`. |
| Display completely dead | COM must go to GND for a common-cathode display; verify the `common` attribute is `"cathode"`. |
| Digit shows but dim/flickery | On real hardware use resistors; check for loose jumpers. |

## 🚀 Challenge

Make it auto-count once per second when a second "mode" button is held down. Or extend to hexadecimal letters A–F (patterns exist!).

## 💡 Future Improvements

- Drive multiple digits with multiplexing (advanced).
- Combine with Project 13 to show dice results on the display.
