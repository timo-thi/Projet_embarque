#include "sensors.hpp"

#include <SoftwareSerial.h>
#include <Wire.h>
//#include "DS1307.h"
#include <Arduino.h>
 
 // Instanciation de la librairie BME280
Adafruit_BME280 bme;

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


void LightSensor(){                         //Light related data
  int lux = analogRead(A0);                 //lux gets the light sensor data : the ambient lumisosity 
  char buf[10];                             
  sprintf(buf, "light: %d", lux);           
  led.setColorRGB(0,0,255,0);
  Serial.println(buf);                      //print "light: "lux" value on serial monitor"
}


void WeatherSensor(){
  /**/
  //Fetch the ambient temperature
  float temperature = bme.getTemperature();
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

/*
//
// ======================================
// Boucle principale (boucle perpétuelle)
// ======================================
void loop() {

  // Affichage de la TEMPÉRATURE
  Serial.print(F("Température = "));
  Serial.print(bme.readTemperature());
  Serial.println(F(" °C"));

  // Affichage du TAUX D'HUMIDITÉ
  Serial.print(F("Humidité = "));
  Serial.print(bme.readHumidity());
  Serial.println(F(" %"));
  
  // Affichage de la PRESSION ATMOSPHÉRIQUE
  Serial.print(F("Pression atmosphérique = "));
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(F(" hPa"));

  // Affichage de l'estimation d'ALTITUDE
  Serial.print(F("Altitude estimée = "));
  Serial.print(bme.readAltitude(pressionAuNiveauDeLaMerEnHpa));
  Serial.println(F(" m"));


  // ... et on répète ce cycle à l'infini !
  delay(delaiRafraichissementAffichage);                // Avec x secondes d'attente, avant chaque rebouclage
  Serial.println();                                     // … et un saut de ligne pour faire joli ;)

}

*/
