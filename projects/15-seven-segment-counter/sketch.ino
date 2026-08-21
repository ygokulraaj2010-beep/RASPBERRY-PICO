// ------------------------------------------------------------
// Project 15 - 7-Segment Counter
// Show a number from 0 to 9 on a common-cathode 7-segment
// display. Each button press advances the count by one.
//
// Wiring (direct connections are fine in simulation):
//   Segment A -> GP0   Segment E -> GP4
//   Segment B -> GP1   Segment F -> GP5
//   Segment C -> GP2   Segment G -> GP6
//   Segment D -> GP3   COM -> GND (cathode display)
//   Button: GP16 (Physical Pin 21) -> pin 1.l, pin 2.l -> GND
//
// Physical pins: GP0=1, GP1=2, GP2=4, GP3=5, GP4=6, GP5=7,
//                GP6=9, GP16=21
// ------------------------------------------------------------

// Segment order in our array: A, B, C, D, E, F, G
const int segPins[7] = {0, 1, 2, 3, 4, 5, 6};

const int BUTTON_PIN = 16;    // advance button

// One byte per digit: bit i = segment i (A is bit 0).
// Example for "0": segments A,B,C,D,E,F on -> 0b00111111
const byte digitPatterns[10] = {
  0b00111111,   // 0
  0b00000110,   // 1
  0b01011011,   // 2
  0b01001111,   // 3
  0b01100110,   // 4
  0b01101101,   // 5
  0b01111101,   // 6
  0b00000111,   // 7
  0b01111111,   // 8
  0b01101111    // 9
};

int count = 0;
int lastButtonState = HIGH;

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);
}

void displayDigit(int n) {
  byte pattern = digitPatterns[n];
  for (int i = 0; i < 7; i++) {
    // Bit i of the pattern = state of segment i (HIGH = lit)
    digitalWrite(segPins[i], (pattern >> i) & 1 ? HIGH : LOW);
  }
}

void loop() {
  int current = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && current == LOW) {   // new press
    count++;
    if (count > 9) {
      count = 0;                    // wrap back to zero
    }
    displayDigit(count);
    Serial.print("Count: ");
    Serial.println(count);
  }

  lastButtonState = current;
}
