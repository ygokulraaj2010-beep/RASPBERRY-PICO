# 🤖 Raspberry Pi Pico Course — Learn Embedded Programming with 20 Hands-On Projects

An open-source, beginner-friendly course that teaches **Raspberry Pi Pico (RP2040) programming and electronics** through **20 practical projects** — all simulated for free in your browser with [Wokwi](https://wokwi.com).

**Language:** Arduino C++ (arduino-pico core)
**Board:** Raspberry Pi Pico
**Simulator:** Wokwi
**Level:** Absolute beginner → confident maker

---

## 📚 What is the Raspberry Pi Pico?

The Raspberry Pi Pico is a low-cost microcontroller board built on the RP2040 chip:

- Dual-core ARM Cortex-M0+ @ 133 MHz
- 264 KB RAM, 2 MB flash
- **26 usable GPIO pins** (GP0–GP28; GP23–GP25 are internal)
- 3 analog inputs: **GP26/GP27/GP28** = ADC channels 0/1/2
- Hardware PWM, I2C, SPI, UART, and programmable I/O (PIO)

> ⚠️ **Golden rule used throughout this course:** every pin has *two* numbers.
> Example: `GP15` is the GPIO number you use in code; it sits on **physical pin 20** of the board. Every project README lists both.

## ⚙️ Why Arduino C++?

This course uses the Arduino language (C++) with the community [arduino-pico core](https://github.com/earlephilhower/arduino-pico):

- Familiar `pinMode()` / `digitalRead()` / `analogWrite()` APIs
- Huge library ecosystem (Servo, DHT sensors, LCDs…)
- The same skills transfer to Uno, ESP32, and other boards
- Wokwi compiles real C++ — errors teach you real embedded habits

## 💻 What is MicroPython? (and why we didn't use it here)

MicroPython is a lean Python port for microcontrollers. It's great — but this course is written entirely in C++. If you open these `.ino` files in a Wokwi **MicroPython** template you'll get confusing build errors like *"invalid preprocessing directive"*. That error means wrong template, not wrong code: always start projects from the **Arduino Pi Pico template**.

## 🧪 What is Wokwi?

[Wokwi](https://wokwi.com) is a free browser simulator for Arduino, ESP32 and Pi Pico:

- No hardware needed to start learning
- Real compilation of your code + interactive virtual parts (LEDs, buttons, sensors, displays…)
- Every project folder contains a ready-made `diagram.json` circuit you can open instantly

## 📁 How to Use This Repository

Each project lives in its own folder:

```text
projects/
└── 01-led-blink/
    ├── README.md      ← full tutorial (read first!)
    ├── sketch.ino     ← the program
    ├── diagram.json   ← the Wokwi circuit definition
    ├── libraries.txt  ← libraries the build needs
    └── wokwi.toml     ← Wokwi CLI configuration
```

### Run a project in Wokwi (recommended way to start)

1. Open https://wokwi.com/projects/new/pi-pico (**Arduino** template!)
2. Replace the editor's code with the project's `sketch.ino`
3. Open the `diagram.json` tab and replace its content with the project's `diagram.json`
4. Press the green ▶ Play button
5. Follow the README's "Expected Result" section

### Run on real hardware

- Install the Arduino IDE, add the "Raspberry Pi Pico/RP2040" boards package, select your board, upload.
- Or press F1 in Wokwi → **Download UF2 Binary**, hold BOOTSEL while plugging in the Pico, copy the UF2 to the `RPI-RP2` drive.

### Use with the Wokwi CLI (optional)

```bash
npm install -g @wokwi/cli
cd projects/01-led-blink
wokwi-cli .
```

## 🗺️ The 20 Projects

| # | Project | Concept |
| -: | ------- | ------- |
| 01 | LED Blink | Digital output |
| 02 | Multiple LED Controller | Arrays + loops |
| 03 | Button Controlled LED | Digital input, pull-ups |
| 04 | Traffic Light | Sequences & functions |
| 05 | Push Button Counter | Edge detection, Serial |
| 06 | Buzzer Alarm | Sound with `tone()` |
| 07 | RGB LED Controller | PWM color mixing |
| 08 | Potentiometer LED Dimmer | ADC (`analogRead`) |
| 09 | LDR Light Sensor | Analog sensor math |
| 10 | Automatic Night Light | Threshold automation |
| 11 | Servo Controller | Servo library |
| 12 | Servo + Potentiometer | Input → map → output |
| 13 | Digital Dice | Randomness, many LEDs |
| 14 | Reaction Timer | `millis()` timing |
| 15 | 7-Segment Counter | Bit patterns, displays |
| 16 | Temperature Monitor | DHT22 library |
| 17 | Door Alarm | Switch as sensor |
| 18 | LED Level Indicator | Bar graphs |
| 19 | Mini Reaction Game | Two-player game logic |
| 20 | Mini Sensor Dashboard | I2C LCD + multi-sensor |

Full details & status: see **[PROJECT_INDEX.md](PROJECT_INDEX.md)**.

## 📈 Learning Progression

```text
LED basics -> multiple outputs -> buttons -> sequences
-> events/counting -> sound -> PWM -> ADC/sensors
-> servos -> displays -> multi-component systems
```

Every project reuses what came before it — nothing appears out of nowhere.

## 🐙 GitHub Usage

**Clone this repository:**

```bash
git clone <your-fork-url>
cd pico-course
```

**Suggested workflow for learners:**

1. Work through projects 01→20 in order.
2. After each project, commit your own modifications:
   ```bash
   git add projects/01-led-blink/my-version.ino
   git commit -m "Project 01: my faster blink"
   git push
   ```
3. Do the 🚀 Challenge at the end of every README — that's where real learning happens!

**Contributions welcome:** fixes, new challenges, translations. Open an issue or PR.

## 📄 License & Credits

Licensed under the **MIT License** — Copyright © 2026 **Codenix Technology** (see [LICENSE](LICENSE)). Created by Gokul for open education. Component behavior documented per the official [Wokwi docs](https://docs.wokwi.com). All circuits were designed for this course.

**Status:** all 20 projects are STATIC-TESTED (validated JSON, doc-verified part/pin names, sketch↔diagram GPIO match). Wokwi runtime simulations have not been executed during authoring — if a simulation misbehaves, please open an issue!
