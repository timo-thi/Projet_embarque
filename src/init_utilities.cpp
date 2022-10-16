#include "init_utilities.hpp"

void start_serial(){
    Serial.begin(9600);
    Serial.println("Started serial monitor\n");
}

void stop_serial(){
    Serial.println("Ending serial monitor\n");
    Serial.end();
}
