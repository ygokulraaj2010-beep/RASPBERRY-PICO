# Project 16 — Temperature Monitor

## Difficulty

Medium-Hard

## 🎯 Objective

Read real temperature and humidity data from a DHT22 digital sensor and print it every two seconds — the basis of any weather station.

## 🧠 What You Will Learn

- Working with a **digital protocol** sensor (not just analog voltages)
- Installing/using **libraries** (`DHT.h`)
- Why DHT22 readings must be at least 2 s apart
- Detecting bad data with `isnan()`

## 🧰 Components

| Component | Wokwi Part | Qty |
| --------- | ---------- | --- |
| Raspberry Pi Pico | `wokwi-pi-pico` | 1 |
| DHT22 temperature/humidity sensor | `wokwi-dht22` | 1 |

## 🔌 Wiring

| DHT22 pin | Connects to Pico | Physical Pin |
| --------- | ---------------- | ------------ |
| `SDA` (data) | GP16 | 21 |
| `VCC` | 3V3 | 36 |
| `GND` | GND.1 | 3 |
| `NC` | — leave unconnected — | — |

## ⚙️ How It Works

The DHT22 sends whole numbers as timed pulses on one wire — decoding that by hand would be painful, so we use Adafruit's **DHT sensor library** (already listed in `libraries.txt`, Wokwi installs it automatically):

```cpp
DHT dht(DHT_PIN, DHT22);   // tell the library which pin + sensor type
dht.begin();               // in setup()
float t = dht.readTemperature();
float h = dht.readHumidity();
```

The sensor needs ≥ 2 s between reads, so we use a `millis()` timer (Project 14's technique) instead of `delay()`.

## 💻 Code (`sketch.ino`)

Core reading logic:

```cpp
#include <DHT.h>
DHT dht(16, DHT22);

void loop() {
  if (millis() - lastReading >= 2000) {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (isnan(t) || isnan(h)) {
      Serial.println("Sensor read failed");
      return;
    }
    Serial.print(t, 1);
    Serial.print(" C / ");
    Serial.print(h, 1);
    Serial.println(" %");
  }
}
```

## 🧪 Wokwi Simulation

Use the Arduino "Pi Pico" template (https://wokwi.com/projects/new/pi-pico), paste all files from this folder. **Click the sensor during simulation and drag its sliders** to change temperature/humidity live!

## ▶️ How to Run

- **Wokwi:** press ▶ Play, watch the Serial Monitor.
- **Hardware:** compile for the Pico with the same two libraries installed via Library Manager.

## ✅ Expected Result

Every two seconds:

```text
Temperature: 24.0 C   Humidity: 40.0 %
```

Changing the sliders changes the printed values.

## 🐛 Troubleshooting

| Problem | Fix |
| ------- | --- |
| "Sensor read failed" repeatedly | Check the data wire is on GP16 and VCC/GND are correct; wait — first read can fail right after boot. |
| Compile error: `DHT.h: No such file` | The two libraries from `libraries.txt` aren't installed — add them in Wokwi's Library Manager or Arduino IDE. |
| Values never change | You're reading faster than allowed or forgot to move the sliders. |

## 🚀 Challenge

Add a warning LED on GP15 that lights when temperature exceeds 30 °C — try it by dragging the slider past 30!

## 💡 Future Improvements

- Log data with timestamps.
- Show values on an LCD — Project 20 combines exactly these parts!
