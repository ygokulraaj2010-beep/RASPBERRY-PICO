# Project 13 — Digital Dice

## Difficulty

Medium

## 🎯 Objective

Build an electronic dice: press the button, watch the LEDs flicker like a rolling die, then show your random result (1–6) as that number of lit LEDs.

## 🧠 What You Will Learn

- Generating randomness with `random()` / `randomSeed()`
- Combining **six outputs + one input** in one program
- The `i < number ? HIGH : LOW` conditional expression
- Simple animation loops

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| LED (any colors) | `wokwi-led` | 6 |
| 220 Ω resistor | `wokwi-resistor` | 6 |
| Push button | `wokwi-pushbutton` | 1 |

## 🔌 Wiring

| Dice face | LED | GPIO | Physical Pin |
| --------- | --- | ---- | ------------ |
| 1 | led1 | GP10 | 14 |
| 2 | led2 | GP11 | 15 |
| 3 | led3 | GP12 | 16 |
| 4 | led4 | GP13 | 17 |
| 5 | led5 | GP14 | 19 |
| 6 | led6 | GP15 | 20 |

Each GPIO → 220 Ω → LED anode (+); all cathodes (−) → GND.
Button: GP16 (Physical Pin 21) to pin `1.l`, GND.7 (Physical Pin 38) to pin `2.l`.

## ⚙️ How It Works

- `showNumber(n)` lights exactly the first `n` LEDs — so the count *is* the dice value.
- On each fresh button press, a short loop flashes `random(1, 7)` ten times (the "shake"), then locks in one final `random(1, 7)` result. Note: `random(min, max)` excludes `max`, so `random(1, 7)` gives 1–6.
- `randomSeed(analogRead(A0))` uses floating electrical noise so you don't get the same sequence every reset.

## 💻 Code (`sketch.ino`)

```cpp
const int ledPins[6] = {10, 11, 12, 13, 14, 15};

void showNumber(int n) {
  for (int i = 0; i < 6; i++)
    digitalWrite(ledPins[i], i < n ? HIGH : LOW);
}

void loop() {
  // ...edge detection as in Project 05...
  if (newPress) {
    for (int i = 0; i < 10; i++) {   // rolling animation
      showNumber(random(1, 7));
      delay(100);
    }
    showNumber(random(1, 7));        // final result
  }
}
```

(The full commented version is in `sketch.ino`.)

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`. Click the button to roll.

## ▶️ How to Run

- **Wokwi:** press ▶ Play, click the button.
- **Hardware:** compile for the Pico; wire the six LEDs and button.

## ✅ Expected Result

Press → LEDs flash rapidly for ~1 s ("rolling") → settle showing 1 to 6 lit LEDs. The Serial Monitor prints `You rolled: N`.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Same sequence every restart | You skipped `randomSeed(analogRead(A0))` in `setup()`. |
| Always rolls the same number | Check the seed line again; also confirm you call `random(1, 7)`, not `random(6) + something`. |
| One LED never lights | Trace its resistor/GPIO wire against the table. |

## 🚀 Challenge

Display real dice *patterns* instead of counted dots: e.g. 5 = corners + center. You'll need a pattern table per face and some creative wiring.

## 💡 Future Improvements

- Show the result on a single 7-segment display — Project 15 does exactly that!
