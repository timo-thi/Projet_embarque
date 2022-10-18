#include <Wire.h>
//#include "DS1307.h"
#include <Arduino.h>
#include <Adafruit_BME280.h>  


void LightSensor(){                         //This function fetches light related data
  int lux = analogRead(A0);                 //lux gets the light sensor data
  char buf[10];                             
  sprintf(buf, "light: %d", lux);           
  Serial.println(buf);                      //print "light: "lux" value on serial monitor"
  return lux;
}


void setup()
{
    Serial.begin(9600);
    
}
void loop()
{
    LightSensor();
}

