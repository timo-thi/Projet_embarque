#include <EEPROM.h> // Included here to be accessible in eeprom_utilities.cpp AND allow good data type definition in function declarations.

int fetch_eeprom_data(int adr);
int fetch_eeprom_byte(int adr);
void send_eeprom_data(int adr, int val);
void send_eeprom_byte(int adr, uint8_t val);
