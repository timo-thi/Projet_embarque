#include "init_utilities.hpp"
#include <Adafruit_BME280.h>
#ifndef SENSORS
#define SENSORS
#define adresseI2CduBME280                0x76            // Adresse I2C du BME280 (0x76, dans mon cas, ce qui est souvent la valeur par défaut)
#define pressionAuNiveauDeLaMerEnHpa      1024.90         // https://fr.wikipedia.org/wiki/Pression_atmospherique (1013.25 hPa en moyenne, valeur "par défaut")
#define delaiRafraichissementAffichage    1500            // Délai de rafraîchissement de l'affichage (en millisecondes)



void init_BME280();

void LightSensor();

void WeatherSensor();



#endif