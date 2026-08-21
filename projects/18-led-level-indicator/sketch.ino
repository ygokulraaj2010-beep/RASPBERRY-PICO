// ------------------------------------------------------------
// Project 18 - LED Level Indicator
// A 6-LED bar graph that fills up as you turn the knob -
// like a volume meter or battery indicator.
//
// Wiring:
//   Potentiometer SIG -> GP26 / A0 (Physical Pin 31)
//   Potentiometer VCC -> 3V3       (Physical Pin 36)
//   Potentiometer GND -> GND       (Physical Pin 3)
//   Bar LEDs: GP10..GP15 (Physical Pins 14,15,16,17,19,20),
//             each GPIO -> 220 ohm -> LED anode, cathodes -> GND
// ------------------------------------------------------------

const int POT_PIN = A0;
const int ledPins[6] = {10, 11, 12, 13, 14, 15};

int lastLevel = -1;   // so the first update always runs

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(115200);
}

void showLevel(int level) {
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], (i < level) ? HIGH : LOW);
  }
}

void loop() {
  int rawValue = analogRead(POT_PIN);          // 0..1023
  int level = map(rawValue, 0, 1024, 0, 7);    // 0..6 bars

  // Only touch the LEDs when the level actually changed
  if (level != lastLevel) {
    showLevel(level);
    Serial.print("Raw: ");
    Serial.print(rawValue);
    Serial.print("  Level: ");
    Serial.println(level);
    lastLevel = level;
  }
}
