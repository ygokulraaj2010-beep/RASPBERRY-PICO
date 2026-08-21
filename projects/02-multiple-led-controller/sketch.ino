// ------------------------------------------------------------
// Project 02 - Multiple LED Controller
// Control 3 LEDs with arrays and loops (LED chase pattern).
//
// Wiring (each LED: GPIO -> 220 ohm -> LED anode, cathode -> GND):
//   Red    LED: GP13 (Physical Pin 17)
//   Yellow LED: GP14 (Physical Pin 19)
//   Green  LED: GP15 (Physical Pin 20)
// ------------------------------------------------------------

const int ledPins[3] = {13, 14, 15};   // GP13, GP14, GP15

void setup() {
  // Configure every pin in the array as an OUTPUT
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(115200);
  Serial.println("LED chase started...");
}

void allOff() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  // Chase left -> right
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
  }

  // Chase right -> left (start at index 1, skip the ends)
  for (int i = 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
  }
}
