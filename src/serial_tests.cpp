#include "serial_tests.hpp"

int config_timeout = 5000;


void serial_recup();

void test_init(){
    led.setColorRGB(0, 255,  55, 5);
    start_serial();
    initialisation_interruption_tim(1000);
    while (config_timeout > 0){
        serial_recup();
    }
}

void serial_recup(){
    String command;
    int value;
    Serial.print("WWW_User:~$ ");
    while (Serial.available() <= 0) {};
    command = Serial.readStringUntil('=');
    // Serial.read();
    // if (Serial.available() > 0)
    value = Serial.parseInt();
    while (Serial.available() > 0) Serial.read();
    // Serial.print("Found command : ");Serial.print(command);Serial.print(" | Found value : ");Serial.println(value);
    Serial.print(command);Serial.print("=");Serial.println(value);
}
