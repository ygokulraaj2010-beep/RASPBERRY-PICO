// ------------------------------------------------------------
// Project 03 - Button Controlled LED
// Read a push button and turn an LED on while it is pressed.
//
// Wiring:
//   Button: GP14 (Physical Pin 19) -> button pin 1.l
//           GND  (Physical Pin 3)  -> button pin 2.l
//           (internal pull-up, so pressed = LOW)
//   LED:    GP15 (Physical Pin 20) -> 220 ohm -> LED -> GND
// ------------------------------------------------------------

const int BUTTON_PIN = 14;   // GP14, physical pin 19
const int LED_PIN    = 15;   // GP15, physical pin 20

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);   // internal pull-up resistor ON
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Press the button...");
}

void loop() {
  // With INPUT_PULLUP: LOW = pressed, HIGH = released
  if (digitalRead(BUTTON_PIN) == LOW) {
    digitalWrite(LED_PIN, HIGH);       // button held -> LED on
  } else {
    digitalWrite(LED_PIN, LOW);        // released -> LED off
  }
}
