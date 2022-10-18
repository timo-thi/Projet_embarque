#include "init_utilities.hpp"
#include "sensors.hpp"





void setup()
{
    init_rgb_led();
    start_serial();
    
}
void loop()
{
    LightSensor();
    led.setColorRGB(0,255,255,0);
    WeatherSensor();
}
