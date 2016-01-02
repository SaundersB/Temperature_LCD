/*

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 * DHT11 Data Sensor pin 8

 This Arduino project reads the temperature and humidity from the DHT11 sensor and prints it to the 16X2 LCD.
 */

// include the library code:
#include <LiquidCrystal.h>
#include "DHT.h"


#define DHTPIN 8     // Data Pin
#define DHTTYPE DHT11   // Model DHT 11 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

void setup() {
   // set up the LCD's number of columns and rows:
   lcd.begin(16, 2);

   Serial.begin(9600); 
   
   Serial.println("DHT11 temperature sensor initalizing");
   dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  lcd.clear();

  lcd.print("Humidity: "); 
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0, 1);

  lcd.print("Temp: "); 
  lcd.print(f);

  lcd.print(char(223));
  lcd.print(" F");

  delay (6000);
  
  float hi = dht.computeHeatIndex(f, h);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: "); 
  lcd.print(t);
  lcd.print(char(223));
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("HI: ");
  lcd.print(hi);
  lcd.print(char(223));
  lcd.print(" F");
  delay (4000);
}