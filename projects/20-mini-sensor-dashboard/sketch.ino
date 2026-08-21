// ------------------------------------------------------------
// Project 20 - Mini Sensor Dashboard (final project!)
// A real multi-sensor station: temperature + humidity from a
// DHT22, knob position from a potentiometer, and light level
// from an LDR - all shown on an I2C LCD display.
//
// Wiring:
//   LCD1602 (I2C): SDA -> GP4 (Physical Pin 6), SCL -> GP5
//                  (Physical Pin 7), VCC -> 3V3, GND -> GND
//   DHT22:         data -> GP16 (Physical Pin 21)
//   Potentiometer: SIG -> GP26 / A0 (Physical Pin 31)
//   LDR module:    AO  -> GP27 / A1 (Physical Pin 32)
//
// TIP: click the DHT22 during simulation to change its values,
//      drag the pot slider, edit the LDR "lux" attribute!
// ------------------------------------------------------------

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // standard I2C address 0x27
DHT dht(16, DHT22);

unsigned long lastTempRead = 0;
unsigned long lastFastRead = 0;

void setup() {
  // Explicitly route I2C0 to its default pins: SDA = GP4, SCL = GP5
  // (Physical Pins 6 and 7). Doing it manually keeps the wiring obvious.
  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();

  lcd.init();               // initialize the LCD
  lcd.backlight();          // turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Sensor Dashboard");
  lcd.setCursor(0, 1);
  lcd.print("booting...");
  delay(1500);
  dht.begin();

  Serial.begin(115200);
}

void loop() {
  // ---- Fast lane: pot + light sensor update every 300 ms ----
  if (millis() - lastFastRead > 300) {
    lastFastRead = millis();

    int potValue = analogRead(A0);   // GP26
    int ldrValue = analogRead(A1);   // GP27

    // Second line: knob + light readings (max 16 characters!)
    lcd.setCursor(0, 1);
    char line[17];
    snprintf(line, sizeof(line), "P:%4d L:%4d ", potValue, ldrValue);
    lcd.print(line);

    Serial.print("Pot: ");
    Serial.print(potValue);
    Serial.print(" Light: ");
    Serial.println(ldrValue);
  }

  // ---- Slow lane: DHT22 only every 2 seconds (its limit) ----
  if (millis() - lastTempRead > 2000) {
    lastTempRead = millis();

    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (!isnan(t) && !isnan(h)) {
      // First line: climate data (max 16 characters!)
      lcd.setCursor(0, 0);
      char line[17];
      snprintf(line, sizeof(line), "T:%4.1fC H:%3.0f%%", t, h);
      lcd.print(line);
    }
  }
}
