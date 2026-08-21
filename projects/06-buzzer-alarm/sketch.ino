// ------------------------------------------------------------
// Project 06 - Buzzer Alarm
// Play a rising-and-falling siren on a buzzer with tone().
//
// Wiring:
//   Buzzer pin "+" (part pin 2) -> GP15 (Physical Pin 20)
//   Buzzer pin "-" (part pin 1) -> GND (Physical Pin 3)
// ------------------------------------------------------------

const int BUZZER_PIN = 15;    // GP15, physical pin 20

const int MIN_FREQ = 400;     // lowest siren pitch (Hz)
const int MAX_FREQ = 1000;    // highest siren pitch (Hz)
const int STEP     = 10;      // pitch change per step

int frequency = MIN_FREQ;
int direction = STEP;         // +1 step = rising pitch

void setup() {
  Serial.begin(115200);
  Serial.println("Siren running...");
}

void loop() {
  tone(BUZZER_PIN, frequency);   // play this frequency now

  frequency += direction;        // move the pitch up or down
  if (frequency >= MAX_FREQ) {
    direction = -STEP;           // reached the top -> fall back down
  }
  if (frequency <= MIN_FREQ) {
    direction = STEP;            // reached the bottom -> rise again
  }

  delay(5);                      // controls how fast the siren sweeps
}
