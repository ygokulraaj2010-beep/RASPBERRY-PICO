// ------------------------------------------------------------
// Project 17 - Door Alarm
// A magnetic door sensor (simulated with a slide switch):
// when the "door" opens, a red LED flashes and the buzzer
// sounds an alarm until the door is closed again.
//
// Wiring:
//   Switch (door sensor): common pin 2 -> GP16 (Physical Pin 21)
//                         pin 1        -> GND (Physical Pin 3)
//   LED: GP14 (Physical Pin 19) -> 220 ohm -> LED -> GND
//   Buzzer: "+" (part pin 2)    -> GP15 (Physical Pin 20)
//           "-" (part pin 1)    -> GND (Physical Pin 8)
//
// Logic: switch LEFT  = pins 1+2 connected = LOW  = door CLOSED
//        switch RIGHT = open circuit      = HIGH = door OPEN
// ------------------------------------------------------------

const int DOOR_SENSOR_PIN = 16;   // GP16, physical pin 21
const int ALARM_LED_PIN   = 14;   // GP14, physical pin 19
const int BUZZER_PIN      = 15;   // GP15, physical pin 20

void setup() {
  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP);
  pinMode(ALARM_LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  bool doorOpen = digitalRead(DOOR_SENSOR_PIN) == HIGH;

  if (doorOpen) {
    // Intruder alert: flash + beep in alternation
    digitalWrite(ALARM_LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);          // alarm pitch
    delay(200);

    digitalWrite(ALARM_LED_PIN, LOW);
    noTone(BUZZER_PIN);              // silence between beeps
    delay(200);

    Serial.println("ALARM! The door is open!");
  } else {
    // All quiet: everything off
    digitalWrite(ALARM_LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }
}
