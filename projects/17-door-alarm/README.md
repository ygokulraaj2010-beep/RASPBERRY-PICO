# Project 17 — Door Alarm

## Difficulty

Medium-Hard

## 🎯 Objective

Build a security system: when the "door" opens (slide switch), a red LED flashes and the buzzer sounds until the door closes again.

## 🧠 What You Will Learn

- Using a **switch as a sensor** (real door sensors are exactly this — a magnet + reed switch)
- Combining input, two outputs, and sound in one program
- `tone()` / `noTone()` for alarm beeping
- Reading a state continuously instead of counting presses

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| Slide switch (simulated door sensor) | `wokwi-slide-switch` | 1 |
| Red LED | `wokwi-led` | 1 |
| 220 Ω resistor | `wokwi-resistor` | 1 |
| Piezo buzzer | `wokwi-buzzer` | 1 |

## 🔌 Wiring

| Component | Pin | Connects to Pico |
| --------- | --- | ---------------- |
| Switch (common) | `2` | GP16 (Physical Pin 21) |
| Switch | `1` | GND.1 (Physical Pin 3); pin `3` unused |
| LED (+ via 220 Ω) | A | GP14 (Physical Pin 19) |
| LED (−) | C | GND.2 (Physical Pin 8) |
| Buzzer | `+` (`2`) | GP15 (Physical Pin 20) |
| Buzzer | `−` (`1`) | GND.3 (Physical Pin 13) |

## ⚙️ How It Works

The slide switch plays the role of a magnetic reed switch:

- Handle **left** → pins 1+2 connected → GP16 reads **LOW** → door closed → silent.
- Handle **right** → circuit open → pull-up keeps GP16 **HIGH** → door open → alarm!

The alarm alternates: LED on + 1000 Hz beep for 200 ms, then off for 200 ms — the classic flashing siren effect, built from simple delays.

## 💻 Code (`sketch.ino`)

```cpp
bool doorOpen = digitalRead(DOOR_SENSOR_PIN) == HIGH;

if (doorOpen) {
  digitalWrite(ALARM_LED_PIN, HIGH);
  tone(BUZZER_PIN, 1000);
  delay(200);
  digitalWrite(ALARM_LED_PIN, LOW);
  noTone(BUZZER_PIN);
  delay(200);
} else {
  digitalWrite(ALARM_LED_PIN, LOW);
  noTone(BUZZER_PIN);
}
```

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste `sketch.ino` + `diagram.json`. During simulation, click the switch to slide it.

## ▶️ How to Run

- **Wokwi:** press ▶ Play; flip the switch to trigger the alarm.
- **Hardware:** compile for the Pico; replace the switch with a real magnetic reed switch for an actual door!

## ✅ Expected Result

- Switch left (closed): everything quiet.
- Switch right (open): red LED blinks twice per second with beeps between; Serial Monitor spams "ALARM!".
- Back to left: silence returns instantly.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| Alarm never triggers | The switch's pin 2 (middle/common) must go to GP16 — check you didn't use pin 3. |
| Constant alarm at boot | Default handle position is LEFT (closed). If yours starts right, click it back or set attrs `"value": ""`. |
| Buzzer silent but LED works | Buzzer polarity: part pin 2 is "+" and must connect to GP15. |

## 🚀 Challenge

Add a disarm button on GP17: pressing it silences the alarm for 30 seconds even if the door stays open (hint: remember `millis() + 30000`).

## 💡 Future Improvements

- Add multiple doors/windows (more inputs).
- Send a notification over WiFi when triggered (later course level!).
