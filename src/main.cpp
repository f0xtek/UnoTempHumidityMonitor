#include <Arduino.h>
#include <LiquidCrystal.h> // Ardunio LiquidCrystal library
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11

/*
 * Initialize ther LCD object, passing in the reset & enable pins,
 * as well as the data pins in use
 * lcd(resetPin, enablePin, data1, data2, data3, data4)
 */
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/*
 * Initialize the DHT sensor object
 */
DHT dht(DHTPIN, DHTTYPE);

// cppcheck-suppress unusedFunction
void setup()
{
  dht.begin();
  lcd.begin(16, 2); // columns, rows
  lcd.print("Hello, Luke!");
}

// cppcheck-suppress unusedFunction
void loop()
{
  // wait between measurements
  delay(5000);

  float h = dht.readHumidity();
  float tc = dht.readTemperature(); // default celsius

  /*
   * check for valid readings from DHT sensor
   */
  if (isnan(h) || isnan(tc))
  {
    lcd.setCursor(0, 0);
    lcd.print("DHT read failed!");
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(tc) + " C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: " + String(h) + "%");
}