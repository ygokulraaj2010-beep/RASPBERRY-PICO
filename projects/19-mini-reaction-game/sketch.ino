// ------------------------------------------------------------
// Project 19 - Mini Reaction Game (two players!)
// The white LED lights after a random wait. Player 1 (red
// button, GP16) and Player 2 (blue button, GP17) race to
// press first. Pressing BEFORE the light is a false start and
// gives the point to the other player. First to 3 points
// wins the match.
//
// Wiring:
//   LED:     GP15 (Physical Pin 20) -> 220 ohm -> LED -> GND
//   Player1: GP16 (Physical Pin 21) -> btn 1.l, btn 2.l -> GND
//   Player2: GP17 (Physical Pin 22) -> btn 1.l, btn 2.l -> GND
// ------------------------------------------------------------

const int LED_PIN = 15;    // GP15, physical pin 20
const int P1_BUTTON = 16;  // GP16, physical pin 21 - red button
const int P2_BUTTON = 17;  // GP17, physical pin 22 - blue button

const int POINTS_TO_WIN = 3;

int scoreP1 = 0;
int scoreP2 = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(P1_BUTTON, INPUT_PULLUP);
  pinMode(P2_BUTTON, INPUT_PULLUP);
  randomSeed(analogRead(A0));   // noise -> different delays each round
  Serial.begin(115200);
  Serial.println("=== REACTION DUEL: first to 3 points wins! ===");
}

bool pressed(int pin) {
  return digitalRead(pin) == LOW;      // LOW = pressed (pull-up)
}

void waitForBothReleased() {
  while (pressed(P1_BUTTON) || pressed(P2_BUTTON)) {
    delay(10);                         // wait for both to let go
  }
}

void printScore() {
  Serial.print("Score -> Player1: ");
  Serial.print(scoreP1);
  Serial.print(" | Player2: ");
  Serial.println(scoreP2);
}

// The random wait, done WITHOUT delay(): we check the buttons
// every few milliseconds so nobody can cheat with an early press.
// Returns true if someone pressed too early.
bool suspenseWait(unsigned long duration) {
  unsigned long start = millis();
  while (millis() - start < duration) {
    if (pressed(P1_BUTTON)) { scoreP2++; return true; }   // cheat!
    if (pressed(P2_BUTTON)) { scoreP1++; return true; }   // cheat!
  }
  return false;
}

void loop() {
  Serial.println("\nNew round! Wait for the WHITE light...");

  waitForBothReleased();
  digitalWrite(LED_PIN, LOW);

  // Suspense period - early presses are punished
  if (suspenseWait(random(2000, 6000))) {
    digitalWrite(LED_PIN, HIGH);       // flash briefly as penalty
    delay(300);
    digitalWrite(LED_PIN, LOW);
    Serial.println("FALSE START! Point goes to the other player.");
    printScore();
  } else {
    // GO! First press wins the round
    digitalWrite(LED_PIN, HIGH);
    unsigned long goTime = millis();

    int winner = 0;
    while (winner == 0) {
      if (pressed(P1_BUTTON)) winner = 1;
      if (pressed(P2_BUTTON)) winner = 2;
    }

    unsigned long elapsed = millis() - goTime;
    digitalWrite(LED_PIN, LOW);

    Serial.print("Player ");
    Serial.print(winner);
    Serial.print(" reacted in ");
    Serial.print(elapsed);
    Serial.println(" ms!");
    if (winner == 1) scoreP1++; else scoreP2++;
    printScore();
  }

  // Match over? Then reset and play again
  if (scoreP1 >= POINTS_TO_WIN || scoreP2 >= POINTS_TO_WIN) {
    Serial.print("*** PLAYER ");
    Serial.print(scoreP1 > scoreP2 ? 1 : 2);
    Serial.println(" WINS THE MATCH! ***");
    scoreP1 = 0;
    scoreP2 = 0;
    Serial.println("Scores reset - play again!");
  }
}
