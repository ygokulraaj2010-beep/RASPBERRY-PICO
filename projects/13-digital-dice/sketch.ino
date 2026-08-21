// ------------------------------------------------------------
// Project 13 - Digital Dice
// Press the button to "roll": LEDs flicker, then show your
// result (1-6) as that number of lit LEDs.
//
// Wiring:
//   Dice LED i: GP10..GP15 (Physical Pins 14,15,16,17,19,20)
//               each via 220 ohm -> anode, cathodes -> GND
//   Button:     GP16 (Physical Pin 21) -> pin 1.l
//               GND (Physical Pin 38)  -> pin 2.l
// ------------------------------------------------------------

const int ledPins[6] = {10, 11, 12, 13, 14, 15};  // dice face LEDs
const int BUTTON_PIN = 16;                        // roll button

int lastButtonState = HIGH;

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Seed the random generator with electrical noise from A0,
  // otherwise you get the same sequence after every reset!
  randomSeed(analogRead(A0));

  Serial.begin(115200);
  Serial.println("Press the button to roll the dice!");
}

// Light exactly the first 'n' LEDs -> shows the number n
void showNumber(int n) {
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], (i < n) ? HIGH : LOW);
  }
}

void allOff() {
  showNumber(0);
}

void loop() {
  int current = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && current == LOW) {   // new press!
    Serial.println("Rolling...");

    // Rolling animation: flash random numbers ten times
    for (int i = 0; i < 10; i++) {
      showNumber(random(1, 7));      // random(1,7) gives 1..6
      delay(100);
    }

    int result = random(1, 7);       // the final throw
    showNumber(result);
    Serial.print("You rolled: ");
    Serial.println(result);
  }

  lastButtonState = current;
}
