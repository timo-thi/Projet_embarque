#include "init_utilities.hpp"

void rtc_clock_access_error(){
    while (1){
        led.setColorRGB(0, 255, 0, 0);
        delay(1000);
        led.setColorRGB(0, 0, 0, 255);
        delay(1000);
    }
}

void gps_access_error(){
    while (1){
        led.setColorRGB(0, 255, 0, 0);
        delay(1000);
        led.setColorRGB(0, 255, 255, 0);
        delay(1000);
    }
}

void sensor_access_error(){
    while (1){
        led.setColorRGB(0, 255, 0, 0);
        delay(1000);
        led.setColorRGB(0, 0, 255, 0);
        delay(1000);
    }
}

void consistency_data_error(){
    while (1){
        led.setColorRGB(0, 255, 0, 0);
        delay(1000);
        led.setColorRGB(0, 0, 255, 0);
        delay(2000);
    }
}

void sd_card_full_error(){
    while (1){
        led.setColorRGB(0, 255, 0, 0);
        delay(1000);
        led.setColorRGB(0, 255, 255, 255);
        delay(1000);
    }
}

void sd_card_access_error(){
    while (1){
        led.setColorRGB(0, 255, 0, 0);
        delay(1000);
        led.setColorRGB(0, 255, 255, 255);
        delay(2000);
    }
}
