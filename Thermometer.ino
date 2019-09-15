#include <LiquidCrystal.h>
#include "SR04.h"
#define TRIG_PIN 1
#define ECHO_PIN 2
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);       // Initialize Ultrasonic sensor

int tempPin = 0;

//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);     // Corresponding pins
void setup()
{
  lcd.begin(16, 2);
}

void loop()
{
  int tempReading = analogRead(tempPin);
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  /*  replaced
    float tempVolts = tempReading * 5.0 / 1024.0;
    float tempC = (tempVolts - 0.5) * 10.0;
    float tempF = tempC * 9.0 / 5.0 + 32.0;
  */
  
  double a = sr04.Distance();
  double safeRange = 2.30;      // Range to detect movement
  a = a / 100;                  // Convert to meters
  if (a <= safeRange) {
    lcd.print("INTRUDER ALERT");
    // sound alarm function
  }
  else {
    lcd.print("Distance: ");
    lcd.setCursor(10, 0);
    lcd.print(a);
    lcd.print("m");
  }

  // Thermometer reading in second line of LCD
  lcd.setCursor(0, 1);
  // Display Temperature in C
  lcd.print("Temp         C  ");
  // Display Temperature in F
  //lcd.print("Temp         F  ");
  lcd.setCursor(6, 1);
  // Display Temperature in C
  lcd.print(tempC);
  // Display Temperature in F
  //lcd.print(tempF);
  delay(1000);
}
