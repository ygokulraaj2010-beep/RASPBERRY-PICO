# Project 05 — Push Button Counter

## Difficulty

Easy

## 🎯 Objective

Count how many times a button is **pressed** and show the running total in the Serial Monitor. This teaches the difference between "holding" (Project 03) and "pressing" (edge detection).

## 🧠 What You Will Learn

- **Edge detection**: reacting to a *change* of state, not just the current level
- C-style counters: `count++`
- Remembering the previous reading in `lastState`
- Printing values with `Serial.print()` / `Serial.println()`

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| Push button | `wokwi-pushbutton` | 1 |

No resistor needed — we use the Pico's internal pull-up!

## 🔌 Wiring

| Connection | From | To |
| ---------- | ---- | -- |
| Button side 1 | GP15 (Physical Pin 20) | button pin `1.l` |
| Button side 2 | GND.1 (Physical Pin 3) | button pin `2.l` |

## ⚙️ How It Works

The loop constantly compares this reading with the last one:

- Was it `HIGH` (released) before, and `LOW` (pressed) now? → a **new press** → `count++`.
- Otherwise nothing happens, so holding the button adds only +1.

This "compare with previous value" pattern is one of the most useful tricks in embedded programming.

## 💻 Code (`sketch.ino`)

```cpp
const int BUTTON_PIN = 15;
int count = 0;
int lastState = HIGH;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  int current = digitalRead(BUTTON_PIN);
  if (lastState == HIGH && current == LOW) {  // new press
    count++;
    Serial.print("Button pressed! Count = ");
    Serial.println(count);
  }
  lastState = current;
}
```

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`. Open the Serial Monitor panel at the bottom to see the counts.

## ▶️ How to Run

- **Wokwi:** press ▶ Play, click the button repeatedly, watch the Serial Monitor.
- **Hardware:** compile in the Arduino IDE (Pico core); open Tools → Serial Monitor.

## ✅ Expected Result

Every fresh press prints:

```text
Button pressed! Count = 1
Button pressed! Count = 2
Button pressed! Count = 3
...
```

Holding the button down adds only +1.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Counter jumps by several per press | Mechanical buttons "bounce". Acceptable for now; debouncing comes later in the course. |
| Nothing prints | Check wiring; make sure you're looking at the **Serial Monitor**, and that `Serial.begin(115200)` is in `setup()`. |
| Counts continuously while held | Your edge condition is wrong — verify both `lastState == HIGH` and `current == LOW` are checked together. |

## 🚀 Challenge

Add a second button on GP14 (physical pin 19) that decreases the count, so you can go up *and* down.

## 💡 Future Improvements

- Reset the counter after reaching 10.
- Show the number on LEDs (Project 13) or on a 7-segment display (Project 15).
