#include "recuperation_donnee_capteurs.hpp"
#include "AltSoftSerial.h"


AltSoftSerial GpsSerial(3, 2);

void init_gps(){
    GpsSerial.begin(115200);
    start_serial();
}
void recuperation_donnees_GPS()
{
    char buffer[64];
    int count = 0;
    if (GpsSerial.available())                     // if date is coming from software serial port ==> data is coming from SoftSerial shield
    {
        while(GpsSerial.available())               // reading data into char array
        {
            buffer[count++]=GpsSerial.read();      // writing data into array
            if(count == 64)break;
        }
        Serial.write(buffer,count);                 // if no data transmission ends, write buffer to hardware serial port
        // clearBufferArray();                         // call clearBufferArray function to clear the stored data from the array
        count = 0;                                  // set counter of while loop to zero 
    }
    if (Serial.available())                 // if data is available on hardware serial port ==> data is coming from PC or notebook
    GpsSerial.write(Serial.read());        // write it to the SoftSerial shield
}

// SoftwareSerial SoftSerial(2, 3);
// unsigned char buffer[64];                   // buffer array for data receive over serial port
// int count=0;                                // counter for buffer array

// void init_gps()
// {
//     SoftSerial.begin(115200);                 // the SoftSerial baud rate
// }
 
// void recuperation_donnees_GPS()
// {
//     if (SoftSerial.available())                     // if date is coming from software serial port ==> data is coming from SoftSerial shield
//     {
//         while(SoftSerial.available())               // reading data into char array
//         {
//             buffer[count++]=SoftSerial.read();      // writing data into array
//             if(count == 64)break;
//         }
//         Serial.write(buffer,count);                 // if no data transmission ends, write buffer to hardware serial port
//         clearBufferArray();                         // call clearBufferArray function to clear the stored data from the array
//         count = 0;                                  // set counter of while loop to zero 
//     }
//     if (Serial.available())                 // if data is available on hardware serial port ==> data is coming from PC or notebook
//     SoftSerial.write(Serial.read());        // write it to the SoftSerial shield
// }
 
 
// void clearBufferArray()                     // function to clear buffer array
// {
//     for (int i=0; i<count;i++)
//     {
//         buffer[i]=NULL;
//     }                      // clear all index of array with command NULL
// }


//     SoftwareSerial SoftSerial(2, 3);

// void recuperation_donnees_GPS()
// {    
//     SoftSerial.begin(115200);
//     char *buffer = (char*)malloc(64*sizeof(char));
//     int count=0;
    
//     if (SoftSerial.available())                     // if date is coming from software serial port ==> data is coming from SoftSerial shield
//     {
//         while(SoftSerial.available())               // reading data into char array
//         {
//             buffer[count++]=SoftSerial.read();      // writing data into array
//             if(count == 64)break;
//         }
//         Serial.write(buffer,count);                 // if no data transmission ends, write buffer to hardware serial port
//         free(buffer);                         // call clearBufferArray function to clear the stored data from the array
//         count = 0;                                  // set counter of while loop to zero 
//     }
//     if (Serial.available())                 // if data is available on hardware serial port ==> data is coming from PC or notebook
//     SoftSerial.write(Serial.read());
//     SoftSerial.end();
// }

// void clearBufferArray()                     // function to clear buffer array
// {
//     for (int i=0; i<count;i++)
//     {
//         buffer;
//     }                      // clear all index of array with command NULL
// }