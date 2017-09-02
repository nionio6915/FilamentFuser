//-------------------------------------------------------------------
//
// Filament Fuser Controller
// Reiner Buehl <reiner@buehl.net>
//
//------------------------------------------------------------------

// Libraries for the Adafruit RGB/LCD Shield
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>  // RGB LCD Shield communications

// ************************************************
// Display Variables and constants
// ************************************************

// The shield uses the I2C SCL and SDA pins. 
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define OFF 0x0
#define ON 0x1

// Version string
#define VERSION "v0.1"

// which analog pin to connect
#define THERMISTORPIN A0         

// resistance at 25 degrees C
#define THERMISTORNOMINAL 100000      

// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   

// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5

// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950

// the value of the 'other' resistor
#define SERIESRESISTOR 100000    
 
int samples[NUMSAMPLES];
 
void setup() {
  // setup serial monitor
  Serial.begin(9600);
  // setup LCD
  lcd.begin(16, 2);  // initialize display colums and rows
  lcd.setBacklight(ON);  // Set to OFF if you do not want backlight on boot
  lcd.setCursor(0,0);
  lcd.print("Filament Fuser");
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  delay(2000);  // wait two seconds
}

void loop(void) {
  uint8_t i;
  float average;
 
  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(THERMISTORPIN);
   delay(10);
  }
 
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;
 
  Serial.print("Average analog reading "); 
  Serial.println(average);
 
  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
  Serial.print("Thermistor resistance "); 
  Serial.println(average);
 
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C
 
  Serial.print("Temperature "); 
  Serial.print(steinhart);
  Serial.println(" *C");

  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(steinhart);
  lcd.print(" *C");

  delay(1000);
}
