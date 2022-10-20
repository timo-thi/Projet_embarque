#include "SD_Card.hpp"


// SD Card

#define CS_pin 4
#define File_Name "data.csv"
File myFile;

//String File_Name = "data.csv";

void Write_SD_Card(String, String GPS){ //
    SD.begin(SPI_HALF_SPEED, CS_pin);
	myFile = SD.open(File_Name, FILE_WRITE);

    Serial.println("Writing to data.csv");
    myFile.println();
    myFile.close();

    myFile = SD.open(File_Name, FILE_READ);

    while (myFile.available()) {
        Serial.write(myFile.read());
    }
    myFile.close();


}