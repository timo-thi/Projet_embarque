#include "init_utilities.hpp"

#include "ConfigMod.hpp"
#include "sensors.hpp"

Collect_params collect_params;

void setup() {
  // put your setup code here, to run once:
  // start_serial();
  init_rgb_led();
  start_serial();
  init_BME280();
  init_RTC();
  led.setColorRGB(0,255,15,255);
  init_buttons();
  check_config();
  led.setColorRGB(0, 0, 255, 0);
  initialisation_interruption_tim(1000);

}

void loop()
{

    LightSensor();
    
    WeatherSensor();
    RTC_Clock();

    delay(2000);

  // put your main code here, to run repeatedly:

}
