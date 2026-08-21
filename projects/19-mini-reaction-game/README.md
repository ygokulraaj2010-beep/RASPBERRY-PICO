# Project 19 — Mini Reaction Game

## Difficulty

Hard

## 🎯 Objective

A two-player duel: after a random suspense period the white LED flashes, and the first player to slam their button wins the round. False starts are punished. First to 3 points wins.

## 🧠 What You Will Learn

- Reading **two inputs** independently in one program
- Writing functions that return values: `bool suspenseWait(...)`
- Non-blocking waiting (polling buttons *while* time passes)
- Game state: scores, match rules, reset logic
- Everything from Projects 05 + 14 combined into one game

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| White LED | `wokwi-led` | 1 |
| 220 Ω resistor | `wokwi-resistor` | 1 |
| Push button (Player 1) | `wokwi-pushbutton` | 1 |
| Push button (Player 2) | `wokwi-pushbutton` | 1 |

## 🔌 Wiring

| Connection | GPIO | Physical Pin |
| ---------- | ---- | ------------ |
| LED (+ via 220 Ω), − → GND | GP15 | 20 |
| Player 1 button (`1.l`, other side to GND) | GP16 | 21 |
| Player 2 button (`1.l`, other side to GND) | GP17 | 22 |

## ⚙️ How It Works

The clever part is the **suspense wait**: instead of `delay(3000)` — which would make cheating impossible to detect — we loop checking `millis()` and *both* buttons every few milliseconds:

```cpp
bool suspenseWait(unsigned long duration) {
  unsigned long start = millis();
  while (millis() - start < duration) {
    if (pressed(P1_BUTTON)) { scoreP2++; return true; }  // cheat!
    if (pressed(P2_BUTTON)) { scoreP1++; return true; }
  }
  return false;
}
```

If it returns `true`, someone jumped the gun and their opponent gets the point. Otherwise the LED lights, the race loop watches both buttons, and the winner's reaction time is printed.

## 💻 Code (`sketch.ino`)

Main round flow:

```cpp
if (suspenseWait(random(2000, 6000))) {
  // false start: penalty flash + point to opponent
} else {
  digitalWrite(LED_PIN, HIGH);
  unsigned long goTime = millis();
  int winner = 0;
  while (winner == 0) {                 // race!
    if (pressed(P1_BUTTON)) winner = 1;
    if (pressed(P2_BUTTON)) winner = 2;
  }
  unsigned long elapsed = millis() - goTime;
  ...
}
```

Scores persist between rounds; at 3 points the match ends and resets.

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`. Two players click their buttons on screen — or test solo against your own reflexes.

## ▶️ How to Run

- **Wokwi:** press ▶ Play, open the Serial Monitor, play!
- **Hardware:** compile for the Pico; mount two buttons on opposite sides of a breadboard.

## ✅ Expected Result

```text
New round! Wait for the WHITE light...
Player 2 reacted in 341 ms!
Score -> Player1: 0 | Player2: 1
...
*** PLAYER 2 WINS THE MATCH! ***
```

Early presses print "FALSE START!" and award the point to the opponent.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Round never starts | Both buttons must be released first — that's `waitForBothReleased()`. Hold-and-release before playing. |
| Winner always Player 1 | In the race loop both `if`s run; check you didn't put an `else` between them (both can't be checked otherwise). |
| Scores don't reset | The reset block must set **both** `scoreP1 = 0` and `scoreP2 = 0`. |

## 🚀 Challenge

Add a best-of-five mode with a buzzer fanfare on the winning press (GP14 + Project 06 skills).

## 💡 Future Improvements

- Show live scores on LEDs or an LCD.
- Add a third player — how many buttons can the Pico take? (Answer: lots.)
