#include "SD_Card.hpp"

// SD Card

#define CS_pin 4
File myFile;

void Write_SD_Card(int *lumin, float *hygr, float *pressure, float *temp)
{ //
    SD.begin(SPI_HALF_SPEED, CS_pin);
    String File_Name = rtc.now().toString("AAMMDD_0.log");
	myFile = SD.open(File_Name, FILE_WRITE);
    myFile.println(rtc.now().toString("DD AA MM hh mm ss") + String(*lumin) + String(*hygr) + String(*pressure) + String(*temp));
    if(myFile.size() >= fetch_eeprom_data(FILE_MAX_SIZE.adr)){
    }
    else{
    }
    myFile.close();



}