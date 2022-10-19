#include "SD_Card.hpp"


// SD Card

const int CS_pin = 4;

File myFile;
String prefix_name = "Données_du_";

void inti_SD_card(){
    while (!SD.begin(SPI_HALF_SPEED, CS_pin)){
        Serial.println("initialization failed");
    }
	pinMode(SS, OUTPUT);
    Serial.print("avant SD.open");
	myFile = SD.open("Données_du_", FILE_WRITE);
    Serial.print("avant SD.open");

   if (myFile) {
      Serial.println("Writing to test.txt");
      myFile.println("testing 1, 2, 3");
      myFile.close();
   }

   else { Serial.println("error opening test.txt"); }

   myFile = SD.open("Données_du_");

   if (myFile) {
      Serial.println("\ntest.txt:");
      while (myFile.available()) {
         Serial.write(myFile.read());
      }
      myFile.close();
   }

   else { Serial.println("error opening test.txt"); }


}