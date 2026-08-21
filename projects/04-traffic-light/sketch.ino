// ------------------------------------------------------------
// Project 04 - Traffic Light
// Simulate a traffic light sequence:
// RED -> RED+AMBER -> GREEN -> AMBER -> repeat
//
// Wiring (each LED: GPIO -> 220 ohm -> anode, cathode -> GND):
//   Red    LED: GP13 (Physical Pin 17)
//   Amber  LED: GP14 (Physical Pin 19)
//   Green  LED: GP15 (Physical Pin 20)
// ------------------------------------------------------------

const int RED_PIN   = 13;   // GP13, physical pin 17
const int AMBER_PIN = 14;   // GP14, physical pin 19
const int GREEN_PIN = 15;   // GP15, physical pin 20

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(AMBER_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void allOff() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(AMBER_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
}

void loop() {
  // Step 1: STOP - red only for 3 seconds
  allOff();
  digitalWrite(RED_PIN, HIGH);
  delay(3000);

  // Step 2: GET READY - red and amber together for 1 second
  digitalWrite(AMBER_PIN, HIGH);
  delay(1000);

  // Step 3: GO - green only for 3 seconds
  allOff();
  digitalWrite(GREEN_PIN, HIGH);
  delay(3000);

  // Step 4: SLOW DOWN - amber only for 1 second
  allOff();
  digitalWrite(AMBER_PIN, HIGH);
  delay(1000);
}
