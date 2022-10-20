#include "SD_Card.hpp"


// SD Card

#define CS_pin 4
//#define File_Name "data.csv"
File myFile;
String File_Name = "data.csv";

void Write_SD_Card(String donnee)
{ //
    SD.begin(SPI_HALF_SPEED, CS_pin);
	myFile = SD.open(File_Name, FILE_WRITE);
    myFile.println(donnee);
    Serial.println(myFile.size());
    if(myFile.size() >= 4000){
        Serial.print("taille trop grande");
    }
    else{
        Serial.print("taille bien");
    }
    myFile.close();



}