#include "init_utilities.hpp"
#ifndef SENSORS
#define SENSORS

#include <RTClib.h>



void init_BME280();

void LightSensor();

void WeatherSensor();

void init_RTC();

void RTC_Clock();

#endif