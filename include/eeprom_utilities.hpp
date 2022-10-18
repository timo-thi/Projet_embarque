#include <EEPROM.h>
#include "init_utilities.hpp"

// Param structures

int fetch_eeprom_data(int adr);
int fetch_eeprom_byte(int adr);
void send_eeprom_data(int adr, int val);
void send_eeprom_byte(int adr, uint8_t val);
