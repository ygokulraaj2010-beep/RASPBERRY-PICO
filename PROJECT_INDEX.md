# Project Index — Raspberry Pi Pico Course (Projects 01–20)

Arduino C++ on the Raspberry Pi Pico (RP2040), simulated in Wokwi.

|  # | Project | Difficulty | Main Concept | Components | Status |
| -: | ------- | ---------- | ------------ | ---------- | ------ |
| 01 | [LED Blink](projects/01-led-blink/) | Easy | Digital output (`digitalWrite`) | Pico, LED, resistor | STATIC-TESTED |
| 02 | [Multiple LED Controller](projects/02-multiple-led-controller/) | Easy | Arrays + loops | Pico, 3× LED, 3× resistor | STATIC-TESTED |
| 03 | [Button Controlled LED](projects/03-button-controlled-led/) | Easy | Digital input + pull-ups | Pico, button, LED, resistor | STATIC-TESTED |
| 04 | [Traffic Light](projects/04-traffic-light/) | Easy | State sequences, functions | Pico, 3× LED, 3× resistor | STATIC-TESTED |
| 05 | [Push Button Counter](projects/05-push-button-counter/) | Easy | Edge detection, Serial | Pico, button | STATIC-TESTED |
| 06 | [Buzzer Alarm](projects/06-buzzer-alarm/) | Easy | `tone()` sound generation | Pico, buzzer | STATIC-TESTED |
| 07 | [RGB LED Controller](projects/07-rgb-led-controller/) | Easy-Medium | PWM color mixing (`analogWrite`) | Pico, RGB LED, 3× resistor | STATIC-TESTED |
| 08 | [Potentiometer LED Dimmer](projects/08-potentiometer-led-dimmer/) | Medium | ADC input (`analogRead`/`map`) | Pico, pot, LED, resistor | STATIC-TESTED |
| 09 | [LDR Light Sensor](projects/09-ldr-light-sensor/) | Medium | Analog sensors, lux math | Pico, LDR module | STATIC-TESTED |
| 10 | [Automatic Night Light](projects/10-automatic-night-light/) | Medium | Threshold automation | Pico, LDR module, LED, resistor | STATIC-TESTED |
| 11 | [Servo Controller](projects/11-servo-controller/) | Medium | Servo library, angles | Pico, servo | STATIC-TESTED |
| 12 | [Servo + Potentiometer](projects/12-servo-potentiometer/) | Medium | Input → map → output | Pico, pot, servo | STATIC-TESTED |
| 13 | [Digital Dice](projects/13-digital-dice/) | Medium | `random()`, multi-output logic | Pico, 6× LED, 6× resistor, button | STATIC-TESTED |
| 14 | [Reaction Timer](projects/14-reaction-timer/) | Medium | `millis()` timing | Pico, LED, resistor, button | STATIC-TESTED |
| 15 | [7-Segment Counter](projects/15-seven-segment-counter/) | Medium-Hard | Bit patterns, lookup tables | Pico, 7-segment display, button | STATIC-TESTED |
| 16 | [Temperature Monitor](projects/16-temperature-monitor/) | Medium-Hard | DHT22 sensor library | Pico, DHT22 | STATIC-TESTED |
| 17 | [Door Alarm](projects/17-door-alarm/) | Medium-Hard | Switch as sensor + alarm outputs | Pico, slide switch, LED, resistor, buzzer | STATIC-TESTED |
| 18 | [LED Level Indicator](projects/18-led-level-indicator/) | Medium-Hard | Bar graphs from ranges | Pico, pot, 6× LED, 6× resistor | STATIC-TESTED |
| 19 | [Mini Reaction Game](projects/19-mini-reaction-game/) | Hard | Two-player game logic | Pico, LED, resistor, 2× button | STATIC-TESTED |
| 20 | [Mini Sensor Dashboard](projects/20-mini-sensor-dashboard/) | Hard | I2C LCD + multi-sensor integration | Pico, LCD1602 I2C, DHT22, pot, LDR | STATIC-TESTED |

## Status legend

| Status | Meaning |
| ------ | ------- |
| PLANNED | Designed but no files yet |
| BUILDING | Files being written |
| STATIC-TESTED | All files validated: JSON parses, Wokwi part/pin names verified against official docs, code compiles logically, GPIOs match between sketch and diagram |
| WOKWI-TESTED | Simulation actually executed in Wokwi (never claimed unless truly run) |
| READY | Final reviewed state |

> **Note:** All 20 projects above are **STATIC-TESTED** only. No Wokwi runtime simulation has been executed by the authoring process. Run each project yourself with the green ▶ button and report issues via GitHub.

## Learning progression

```text
Digital output -> Multiple outputs -> Digital input -> Sequences
      -> Events & counting -> Sound -> PWM/analog out
      -> Analog in (ADC) -> Sensors -> Actuators (servo)
      -> Displays -> Multi-device systems
```

Projects 21–50 are planned for future course levels.
