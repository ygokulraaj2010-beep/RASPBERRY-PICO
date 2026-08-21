// ------------------------------------------------------------
// Project 07 - RGB LED Controller
// Mix any color from Red, Green and Blue using PWM.
//
// Wiring (RGB LED set to COMMON CATHODE, COM -> GND):
//   R pin -> 220 ohm -> GP13 (Physical Pin 17)
//   G pin -> 220 ohm -> GP12 (Physical Pin 16)
//   B pin -> 220 ohm -> GP11 (Physical Pin 15)
//   COM   -----------------> GND  (Physical Pin 3)
// ------------------------------------------------------------

const int RED_PIN   = 13;   // GP13, physical pin 17
const int GREEN_PIN = 12;   // GP12, physical pin 16
const int BLUE_PIN  = 11;   // GP11, physical pin 15

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(115200);
}

// Set a color: each channel is 0 (off) to 255 (full brightness).
void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

void showColor(const char* name, int r, int g, int b) {
  setColor(r, g, b);
  Serial.print("Color: ");
  Serial.println(name);
  delay(1500);                 // hold the color for 1.5 seconds
}

void loop() {
  showColor("Red",       255,   0,   0);
  showColor("Green",       0, 255,   0);
  showColor("Blue",        0,   0, 255);
  showColor("Yellow",    255, 255,   0);   // red + green
  showColor("Cyan",        0, 255, 255);   // green + blue
  showColor("Magenta",   255,   0, 255);   // red + blue
  showColor("White",     255, 255, 255);   // all together
}
