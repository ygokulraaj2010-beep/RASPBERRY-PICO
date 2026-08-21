// ------------------------------------------------------------
// Project 09 - LDR Light Sensor
// Read light levels from a photoresistor (LDR) module and
// convert them into approximate lux values.
//
// Wiring:
//   LDR module AO  -> GP26 / A0 (Physical Pin 31)
//   LDR module VCC -> 3V3       (Physical Pin 36)
//   LDR module GND -> GND       (Physical Pin 3)
//   (DO digital output is not used in this project)
// ------------------------------------------------------------

const int LDR_PIN = A0;        // analog input = GP26, physical pin 31

// These must match the module's attributes in diagram.json
const float GAMMA = 0.7;
const float RL10  = 50.0;      // LDR resistance (k-ohms) at 10 lux

unsigned long lastPrint = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Light sensor running...");
}

void loop() {
  if (millis() - lastPrint > 250) {     // update 4x per second
    lastPrint = millis();

    int rawValue = analogRead(LDR_PIN);           // 0..1023
    float voltage = rawValue * 3.3 / 1023.0;      // 0..3.3 V

    // Convert voltage -> LDR resistance -> lux
    // (module: LDR on top, 10k resistor to ground)
    float resistance = 10000.0 * voltage / (3.3 - voltage + 0.0001);

    Serial.print("Raw: ");
    Serial.print(rawValue);
    Serial.print("  Voltage: ");
    Serial.print(voltage, 2);
    Serial.print(" V");
    if (resistance > 1 && isfinite(resistance)) {
      float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance,
                      1.0 / GAMMA);
      Serial.print("  Lux: ");
      Serial.println(lux, 1);
    } else {
      Serial.println("  Lux: very bright!");
    }
  }
}
