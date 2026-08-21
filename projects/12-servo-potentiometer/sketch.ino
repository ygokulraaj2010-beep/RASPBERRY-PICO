// ------------------------------------------------------------
// Project 12 - Servo + Potentiometer
// Turn the knob and the servo follows: a classic
// "read sensor -> convert -> act" control loop.
//
// Wiring:
//   Potentiometer SIG -> GP26 / A0 (Physical Pin 31)
//   Potentiometer VCC -> 3V3       (Physical Pin 36)
//   Potentiometer GND -> GND       (Physical Pin 8)
//   Servo PWM (signal) -> GP15     (Physical Pin 20)
//   Servo V+           -> 3V3      (Physical Pin 36)
//   Servo GND          -> GND      (Physical Pin 3)
// ------------------------------------------------------------

#include <Servo.h>

const int POT_PIN = A0;      // analog input = GP26, physical pin 31
const int SERVO_PIN = 15;    // GP15, physical pin 20

Servo myServo;

void setup() {
  myServo.attach(SERVO_PIN);   // connect the library to GP15
  Serial.begin(115200);
  Serial.println("Turn the knob to move the servo!");
}

void loop() {
  // 1. Read the knob (0..1023)
  int rawValue = analogRead(POT_PIN);

  // 2. Convert to an angle (0..180 degrees)
  int angle = map(rawValue, 0, 1023, 0, 180);

  // 3. Command the servo
  myServo.write(angle);

  // 4. Small pause so the servo can keep up with fast turns
  delay(15);
}
