#include "SD_Card.hpp"

// SD Card

#define CS_pin 4
// File myFile;

void Write_SD_Card(int lumin, float hygr, float pressure, float temp)
{ //
    if(!SD.begin(SPI_HALF_SPEED, CS_pin)){
        sd_card_access_error();
    }
    
    Serial.println("sd");
	File myFile = SD.open("0987.log", FILE_WRITE); // SD.open(rtc.now().toString("AAMMDD_0.log"), FILE_WRITE);
    // String donnee = rtc.now().toString("DD AA MM hh mm ss") + String(lumin) + String(hygr) + String(pressure) + String(temp);
    myFile.print(actTime());
    myFile.print(";");
    myFile.print(lumin);
    myFile.print(";");
    myFile.print((char)hygr);
    myFile.print(";");
    myFile.print((char)pressure);
    myFile.print(";");
    myFile.println((char)temp);
    // if(myFile.size() >= fetch_eeprom_data(FILE_MAX_SIZE.adr)){
    // }
    // else{
    // }
    myFile.close();
}