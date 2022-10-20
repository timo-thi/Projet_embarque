#include "init_utilities.hpp"
#ifndef SENSORS
#define SENSORS

#include <RTClib.h>
#include <Adafruit_BME280.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#include <Arduino.h>


void init_BME280();

void LightSensor(int *lux);

void WeatherSensor(float *temperature, float *humidity, float *pressure, float *altitude);

void init_RTC();

void RTC_Clock(DateTime *now);

void Sensors_Tests();


#endif