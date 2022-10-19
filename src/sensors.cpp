#include "sensors.hpp"
#include <Adafruit_BME280.h>

#define adresseI2CduBME280                0x76            // Adresse I2C du BME280 (0x76, dans mon cas, ce qui est souvent la valeur par défaut)
#define pressionAuNiveauDeLaMerEnHpa      1024.90         // https://fr.wikipedia.org/wiki/Pression_atmospherique (1013.25 hPa en moyenne, valeur "par défaut")
#define delaiRafraichissementAffichage    1500            // Délai de rafraîchissement de l'affichage (en millisecondes)


#include <SoftwareSerial.h>
#include <Wire.h>
//#include "DS1307.h"
#include <Arduino.h>
 
 // Instanciation de la librairie BME280
Adafruit_BME280 bme;


// Instanciation de la librairie DS1307
RTC_DS1307 rtc;


 void init_BME280(){
	Serial.print(F("Initialisation du BME280, à l'adresse [0x"));
  	Serial.print(adresseI2CduBME280, HEX);
  	Serial.println(F("]"));
  
  	if(!bme.begin(adresseI2CduBME280)) {
    	Serial.println(F("--> ÉCHEC…"));
  	} else {
    	Serial.println(F("--> RÉUSSIE !"));
  	}
  	Serial.println();
}

void init_RTC(){
  #ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}


void LightSensor(){                         //Light related data
  int lux = analogRead(A0);                 //lux gets the light sensor data : the ambient lumisosity 
  char buf[10];                             
  sprintf(buf, "light: %d lux", lux);           
  led.setColorRGB(0,0,255,0);
  Serial.println(buf);                      //print "light: "lux" value on serial monitor"
}


void WeatherSensor(){

  /**/
  //Fetch the ambient temperature
  float temperature = bme.readTemperature();
  if (Serial){
    Serial.print("temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
  }
  else {
    led.setColorRGB(0, 255, 0, 0);
  }
  //Fetch the ambient humidity
  float humidity = bme.readHumidity();
  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  //Fetch the ambient pressure
  float pressure = (bme.readPressure() / 100.0F);
  Serial.print("pressure: ");
  Serial.print(pressure);
  Serial.println("hPa");
  //Fetch the estimated altitude
  float altitude = bme.readAltitude(pressionAuNiveauDeLaMerEnHpa);
  Serial.print("altitude: ");
  Serial.print(altitude);
  Serial.println("m");

  
}

void RTC_Clock(){
  DateTime now = rtc.now();

  //buffer can be defined using following combinations:
  //hh - the hour with a leading zero (00 to 23)
  //mm - the minute with a leading zero (00 to 59)
  //ss - the whole second with a leading zero where applicable (00 to 59)
  //YYYY - the year as four digit number
  //YY - the year as two digit number (00-99)
  //MM - the month as number with a leading zero (01-12)
  //MMM - the abbreviated English month name ('Jan' to 'Dec')
  //DD - the day as number with a leading zero (01 to 31)
  //DDD - the abbreviated English day name ('Mon' to 'Sun')

   char buf1[] = "hh:mm";
   Serial.println(now.toString(buf1));

   char buf2[] = "YYMMDD-hh:mm:ss";
   Serial.println(now.toString(buf2));

   char buf3[] = "Today is DDD, MMM DD YYYY";
   Serial.println(now.toString(buf3));

   char buf4[] = "MM-DD-YYYY";
   Serial.println(now.toString(buf4));

}




