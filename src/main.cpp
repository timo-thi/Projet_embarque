#include "init_utilities.hpp"

#include "ConfigMod.hpp"
#include "sensors.hpp"

Collect_params collect_params;
int a;
  float b,c,d,e;
  DateTime f;

void setup() {
  // put your setup code here, to run once:
  // start_serial();
  init_rgb_led();
  start_serial();
  init_BME280();
  init_RTC();
  init_buttons();
  check_config();
  initialisation_interruption_tim(1000);
  

}

void loop()
{

    LightSensor(&a);
    WeatherSensor(&b, &c, &d, &e);
    RTC_Clock(&f);
    Sensors_Tests();



  // put your main code here, to run repeatedly:

}
