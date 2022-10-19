#include "init_utilities.hpp"
#include "sensors.hpp"





void setup()
{
    init_rgb_led();
    start_serial();
    init_BME280();
    init_RTC();
    led.setColorRGB(0,255,15,255);
    
}

void loop()
{
    LightSensor();
    
    WeatherSensor();
    RTC_Clock();

    delay(2000);
}
