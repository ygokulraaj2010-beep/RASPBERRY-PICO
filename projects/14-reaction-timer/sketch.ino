// ------------------------------------------------------------
// Project 14 - Reaction Timer
// Measure how fast you can press the button after the LED
// lights up. Your time is shown in milliseconds.
//
// Wiring:
//   LED:    GP15 (Physical Pin 20) -> 220 ohm -> LED -> GND
//   Button: GP16 (Physical Pin 21) -> pin 1.l
//           GND (Physical Pin 8)   -> pin 2.l
// ------------------------------------------------------------

const int LED_PIN    = 15;   // GP15, physical pin 20
const int BUTTON_PIN = 16;   // GP16, physical pin 21

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  randomSeed(analogRead(A0));   // noise -> different delays each round
  Serial.begin(115200);
}

void waitForRelease() {
  while (digitalRead(BUTTON_PIN) == LOW) {
    delay(10);                  // wait until button is let go
  }
}

void loop() {
  Serial.println("\nGet ready... press the button when the LED lights up!");

  // Round starts only after you release the button
  waitForRelease();
  delay(random(2000, 6000));    // random wait: 2-6 seconds

  digitalWrite(LED_PIN, HIGH);  // GO!
  unsigned long startTime = millis();

  // Wait for the press
  while (digitalRead(BUTTON_PIN) == HIGH) {
    // just wait...
  }
  unsigned long reactionTime = millis() - startTime;
  digitalWrite(LED_PIN, LOW);

  Serial.print("Your reaction time: ");
  Serial.print(reactionTime);
  Serial.println(" ms");
  delay(1000);
}
