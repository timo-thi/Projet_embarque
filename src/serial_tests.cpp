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
    char buff = -1;
    char command[50];
    int buff_count = 0;
    Serial.print("WWW_User:~$ ");
    while (Serial.available() <= 0) {};
    while (Serial.available() > 0) {
        buff = Serial.read();
        command[buff_count] = buff;
        buff_count++;
    }
    Serial.print("Found command : ");Serial.println(command);
}