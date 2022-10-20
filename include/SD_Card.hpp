#include "init_utilities.hpp"
#include "eeprom_utilities.hpp"
#include "sensors.hpp"
#include "SPI.h"
#include <SD.h>
#include <RTClib.h>
//SD Card

void Write_SD_Card(int *lumin, float *hygr, float *pressure, float *temp);