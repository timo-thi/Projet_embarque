#include "eeprom_utilities.hpp"

int fetch_eeprom_data(int adr){
    int val;
    EEPROM.get(adr, val);
    return val;
}

int fetch_eeprom_byte(int adr){
    int val = EEPROM.read(adr);

    return val;
}

void send_eeprom_data(int adr, int val){
    EEPROM.put(adr, val);
}

void send_eeprom_byte(int adr, uint8_t val){
    EEPROM.write(adr, val);
}
