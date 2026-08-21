// ------------------------------------------------------------
// Project 05 - Push Button Counter
// Count how many times the button is PRESSED (not held).
// The count is printed in the Serial Monitor.
//
// Wiring:
//   Button: GP15 (Physical Pin 20) -> button pin 1.l
//           GND  (Physical Pin 3)  -> button pin 2.l
//   Internal pull-up is used, so pressed = LOW.
// ------------------------------------------------------------

const int BUTTON_PIN = 15;   // GP15, physical pin 20

int count = 0;               // our counter variable
int lastState = HIGH;        // HIGH = not pressed (pull-up idle)

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("Press the button to increase the counter.");
}

void loop() {
  int current = digitalRead(BUTTON_PIN);

  // A NEW press = state just changed from HIGH (released) to LOW (pressed)
  if (lastState == HIGH && current == LOW) {
    count++;
    Serial.print("Button pressed! Count = ");
    Serial.println(count);
  }

  lastState = current;       // remember the state for next time
}
