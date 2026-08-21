// ------------------------------------------------------------
// Project 01 - LED Blink
// The "Hello, World!" of embedded systems.
//
// Wiring:
//   GP15 (Physical Pin 20) -> 220 ohm resistor -> LED anode (+, long leg)
//   LED cathode (-, short leg) -> GND (Physical Pin 3)
//
// On the Raspberry Pi Pico, the number you use in code is the
// GPIO number: GPIO 15 = physical pin 20. Never mix them up!
// ------------------------------------------------------------

const int LED_PIN = 15;   // GP15, physical pin 20

void setup() {
  pinMode(LED_PIN, OUTPUT);          // GP15 is an OUTPUT
  Serial.begin(115200);              // start the serial console
  Serial.println("Blinking LED on GP15...");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);       // 3.3V on GP15 -> LED ON
  Serial.println("LED ON");
  delay(500);                        // wait 0.5 seconds

  digitalWrite(LED_PIN, LOW);        // 0V on GP15  -> LED OFF
  Serial.println("LED OFF");
  delay(500);
}
