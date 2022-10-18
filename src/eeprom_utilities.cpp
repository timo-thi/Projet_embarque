#include "eeprom_utilities.hpp"

int fetch_eeprom_data(int adr){
    int val;
    EEPROM.get(adr, val); // reading a int directly from eeprom. Possible because we won't store anything else.
    return val;
}

int fetch_eeprom_byte(int adr){
    int val = EEPROM.read(adr); // reading a byte converted in int.
    return val;
}

void send_eeprom_data(int adr, int val){
    EEPROM.put(adr, val); // sending an int directly. Lib takes care of converting in several bytes in eeprom.
}

void send_eeprom_byte(int adr, uint8_t val){
    EEPROM.write(adr, val);
}
