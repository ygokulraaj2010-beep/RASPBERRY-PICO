# Project 14 — Reaction Timer

## Difficulty

Medium

## 🎯 Objective

Measure your reflexes: after a random wait the LED flashes, and the program prints how many milliseconds you took to press the button.

## 🧠 What You Will Learn

- Real time with `millis()` (milliseconds since power-on)
- Subtracting timestamps to measure durations
- `while` loops that wait for events
- Why `delay()` can't do precise timing

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| Red LED | `wokwi-led` | 1 |
| 220 Ω resistor | `wokwi-resistor` | 1 |
| Push button | `wokwi-pushbutton` | 1 |

## 🔌 Wiring

| Connection | From | To |
| ---------- | ---- | -- |
| LED (+ via 220 Ω) | GP15 (Physical Pin 20) | signal light |
| LED (−) | GND.1 (Physical Pin 3) | ground |
| Button pin `1.l` | GP16 (Physical Pin 21) | input |
| Button pin `2.l` | GND.2 (Physical Pin 8) | ground |

## ⚙️ How It Works

A stopwatch needs two timestamps:

```cpp
unsigned long startTime = millis();      // LED goes ON
// ...player presses...
unsigned long reactionTime = millis() - startTime;
```

The flow per round: announce → wait for button release → sleep a *random* 2–6 s (`delay(random(2000, 6000))`) so you can't anticipate → flash LED → start clock → spin in a `while` loop until the press arrives → print the difference.

## 💻 Code (`sketch.ino`)

Core timing part:

```cpp
digitalWrite(LED_PIN, HIGH);            // GO!
unsigned long startTime = millis();
while (digitalRead(BUTTON_PIN) == HIGH) {
  // waiting for the press
}
unsigned long reactionTime = millis() - startTime;
digitalWrite(LED_PIN, LOW);
Serial.print("Your reaction time: ");
Serial.print(reactionTime);
Serial.println(" ms");
```

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`. Click the button when the LED lights.

## ▶️ How to Run

- **Wokwi:** press ▶ Play, watch the Serial Monitor, click when green!
- **Hardware:** compile for the Pico; test yourself and your friends.

## ✅ Expected Result

```text
Get ready... press the button when the LED lights up!
Your reaction time: 287 ms
```

Human average is ~250 ms; anything under 200 ms is excellent!

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Time always ~0–20 ms | You're holding the button during the random delay — release it first (that's what `waitForRelease()` handles). |
| Nothing happens | Check Serial Monitor is open at 115200 baud. |
| Same delay every round | The `randomSeed(analogRead(A0))` line is missing in `setup()`. |

## 🚀 Challenge

Catch cheaters who press *before* the LED lights: if a press happens during the random delay, print "Too soon! 😠" and restart the round without scoring.

## 💡 Future Improvements

- Track best-of-five averages.
- Turn it into a two-player duel — Project 19 does exactly this!
