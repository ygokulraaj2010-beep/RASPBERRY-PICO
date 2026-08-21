// ------------------------------------------------------------
// Project 11 - Servo Controller
// Sweep a servo motor from 0 to 180 degrees and back.
//
// Wiring:
//   Servo PWM (orange/yellow signal) -> GP15 (Physical Pin 20)
//   Servo V+   (red)                 -> 3V3 (Physical Pin 36)
//   Servo GND  (brown/black)         -> GND (Physical Pin 3)
//
// A servo is positioned by short pulses sent ~50 times per
// second. The Servo library handles all of that for you:
// just call servo.write(angle).
// ------------------------------------------------------------

#include <Servo.h>

const int SERVO_PIN = 15;    // GP15, physical pin 20

Servo myServo;

void setup() {
  myServo.attach(SERVO_PIN);      // connect the library to GP15
  Serial.begin(115200);
  Serial.println("Servo sweep starting...");
}

void loop() {
  // Swing from 0 up to 180 degrees, one degree at a time
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    delay(15);                    // give it time to move there
  }

  // And back down from 180 to 0
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(15);
  }
}
