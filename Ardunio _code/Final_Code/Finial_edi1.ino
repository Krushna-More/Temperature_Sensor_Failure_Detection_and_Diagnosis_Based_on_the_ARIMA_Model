#include "max6675.h"

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;
const int RELAY_PIN = 3;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
//thermister
#include <math.h>

float A = 1.009249522e-03, B = 2.378405444e-04, C = 2.019202697e-07;

float T,logRt,Tf,Tc;

float Thermistor(int Vo) {

 logRt = log(10000.0*((1024.0/Vo-1))); 

 T = (1.0 / (A + B*logRt + C*logRt*logRt*logRt));  // We get the temperature value in Kelvin from this Stein-Hart equation

 Tc = T - 273.15- 30;                     // Convert Kelvin to Celcius

 Tf = (Tc * 1.8) + 32.0 - 30;              // Convert Kelvin to Fahrenheit

 return T;

} //
// lm35
#define ADC_VREF_mV    5000.0 // in millivolt
#define ADC_RESOLUTION 1024.0
#define PIN_LM35       A1
//


void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
 
}

void loop() {
  //lm35
  // get the ADC value from the temperature sensor
  int adcVal = analogRead(PIN_LM35);
  // convert the ADC value to voltage in millivolt
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  // convert the voltage to the temperature in Celsius
  float tempC = milliVolt / 10;
  // convert the Celsius to Fahrenheit
  float tempF = tempC * 9 / 5 + 32;

  // print the temperature in the Serial Monitor:
//  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(",");// print the temperature in Celsius
//  Serial.print("°C");
 
//  delay(1000);
  //

  // thermister
  
Thermistor(analogRead(A0));
//Serial.println(A0);

//delay(1000);
 Serial.print(Tc);
 Serial.print(",");
 //
// Serial.print("C = "); 
  Serial.println(thermocouple.readCelsius());
  digitalWrite(RELAY_PIN, HIGH);
 
  delay(1000);
  digitalWrite(RELAY_PIN, LOW);
  
  delay(500);
  
  
  
}
