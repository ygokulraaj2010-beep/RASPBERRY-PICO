// ------------------------------------------------------------
// Project 10 - Automatic Night Light
// The LED turns on automatically when it gets DARK.
//
// Wiring:
//   LDR module AO  -> GP26 / A0  (Physical Pin 31)
//   LDR module VCC -> 3V3        (Physical Pin 36)
//   LDR module GND -> GND        (Physical Pin 3)
//   LED: GP15 (Physical Pin 20) -> 220 ohm -> LED -> GND
//
// NOTE: on this module, MORE light = LOWER reading.
//       The circuit starts dark (lux attribute = 5) so the
//       light is ON at boot. Edit the "lux" attribute in
//       diagram.json to simulate daytime and watch it turn off!
// ------------------------------------------------------------

const int LDR_PIN   = A0;    // analog input = GP26, physical pin 31
const int LED_PIN   = 15;    // GP15, physical pin 20

const int DARK_THRESHOLD = 600;   // readings ABOVE this = darkness

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int rawValue = analogRead(LDR_PIN);

  if (rawValue > DARK_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);      // dark -> night light ON
  } else {
    digitalWrite(LED_PIN, LOW);       // bright -> save energy, OFF
  }

  // Print the current value so you can pick your own threshold
  Serial.print("Raw: ");
  Serial.print(rawValue);
  Serial.println(rawValue > DARK_THRESHOLD ? "  (dark: LED on)" : "  (bright: LED off)");

  delay(250);                         // check 4 times per second
}
