// ------------------------------------------------------------
// Project 08 - Potentiometer LED Dimmer
// Turn the knob to smoothly change the LED brightness.
//
// Wiring:
//   Potentiometer SIG -> GP26 / A0 (Physical Pin 31)
//   Potentiometer VCC -> 3V3       (Physical Pin 36)
//   Potentiometer GND -> GND       (Physical Pin 3)
//   LED: GP15 (Physical Pin 20) -> 220 ohm -> LED -> GND
// ------------------------------------------------------------

const int POT_PIN = A0;    // analog input = GP26, physical pin 31
const int LED_PIN = 15;    // GP15, physical pin 20

unsigned long lastPrint = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // 1. Read the knob: 0..1023 (10-bit ADC)
  int rawValue = analogRead(POT_PIN);

  // 2. Rescale to PWM range: 0..255
  int brightness = map(rawValue, 0, 1023, 0, 255);

  // 3. Set LED brightness via hardware PWM
  analogWrite(LED_PIN, brightness);

  // Print status twice per second without blocking the loop
  if (millis() - lastPrint > 500) {
    lastPrint = millis();
    Serial.print("Raw: ");
    Serial.print(rawValue);
    Serial.print("  Brightness: ");
    Serial.println(brightness);
  }
}
