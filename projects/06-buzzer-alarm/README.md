# Project 06 — Buzzer Alarm

## Difficulty

Easy

## 🎯 Objective

Turn the Pico into a police-style siren: a tone that rises and falls continuously using the Arduino `tone()` function.

## 🧠 What You Will Learn

- How sound works: vibrating a piezo disc at audio frequencies
- Generating tones with `tone(pin, frequency)`
- Variables that change direction (`direction = -STEP`)
- Frequency vs pitch intuition

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| Piezo buzzer | `wokwi-buzzer` | 1 |

## 🔌 Wiring

| Buzzer pin | Meaning | Connect to |
| ---------- | ------- | ---------- |
| `2` (+, red) | Positive | GP15 (Physical Pin 20) |
| `1` (−, black) | Negative | GND.1 (Physical Pin 3) |

## ⚙️ How It Works

Sound is air vibrating. If a GPIO switches ON/OFF hundreds of times per second, the buzzer vibrates and you hear a tone:

- Higher frequency → higher pitch.
- The code moves `frequency` up in small steps until `MAX_FREQ`, flips direction, slides down to `MIN_FREQ`, flips again — forever. That's the siren.

Under the hood, `tone()` configures one of the RP2040's hardware PWM slices for you.

## 💻 Code (`sketch.ino`)

```cpp
const int BUZZER_PIN = 15;
const int MIN_FREQ = 400, MAX_FREQ = 1000, STEP = 10;
int frequency = MIN_FREQ;
int direction = STEP;

void setup() {
  Serial.begin(115200);
}

void loop() {
  tone(BUZZER_PIN, frequency);      // play this pitch now
  frequency += direction;
  if (frequency >= MAX_FREQ) direction = -STEP;   // turn around at top
  if (frequency <= MIN_FREQ) direction = STEP;    // turn around at bottom
  delay(5);                         // sweep speed
}
```

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`, and turn your computer sound on!

## ▶️ How to Run

- **Wokwi:** press ▶ Play and listen.
- **Hardware:** compile for the Pico; connect a passive buzzer exactly as wired above.

## ✅ Expected Result

A continuous "wee-oo-wee-oo" siren sweeping between 400 Hz and 1000 Hz.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| No sound | Check + goes to GP15 and − to GND; confirm your speaker volume; make sure you call `tone()` every loop. |
| Constant single tone | Verify both `if` conditions that flip `direction` exist. |
| Compile error "tone was not declared" | Your board selection must be an RP2040/Pico core that includes `tone()` (arduino-pico core does). |

## 🚀 Challenge

Make a two-tone emergency sound instead of a smooth sweep: beep at 600 Hz for 0.2 s, then 900 Hz for 0.2 s, repeating. (Two lines of `tone()` + two `delay(200)`.)

## 💡 Future Improvements

- Play melodies from note-frequency arrays (a mini piano!).
- Combine with Project 17 to build an alarm triggered by an event.
