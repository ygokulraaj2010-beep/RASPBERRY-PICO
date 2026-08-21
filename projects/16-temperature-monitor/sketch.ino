// ------------------------------------------------------------
// Project 16 - Temperature Monitor
// Read temperature and humidity from a DHT22 sensor and print
// them in the Serial Monitor every two seconds.
//
// Wiring:
//   DHT22 SDA (data) -> GP16 (Physical Pin 21)
//   DHT22 VCC        -> 3V3 (Physical Pin 36)
//   DHT22 GND        -> GND (Physical Pin 3)
//   DHT22 NC         -> not connected
//
// TIP: while the simulation runs, click the DHT22 and use its
// sliders to change temperature/humidity live!
// ------------------------------------------------------------

#include <DHT.h>

const int DHT_PIN = 16;       // GP16, physical pin 21

DHT dht(DHT_PIN, DHT22);      // create the sensor object

unsigned long lastReading = 0;
const unsigned long INTERVAL = 2000;   // DHT22 needs >=2s between reads

void setup() {
  dht.begin();                // start communication with the sensor
  Serial.begin(115200);
  Serial.println("Temperature monitor starting...");
}

void loop() {
  if (millis() - lastReading >= INTERVAL) {
    lastReading = millis();

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();    // Celsius

    // NaN means the reading failed - never print bad data
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Sensor read failed, trying again...");
      return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature, 1);
    Serial.print(" C   Humidity: ");
    Serial.print(humidity, 1);
    Serial.println(" %");
  }
}
