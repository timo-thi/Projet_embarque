#include "init_utilities.hpp"
#include "ConfigMod.hpp"
#include "sensors.hpp"
#include "fetch_data.hpp"

Collect_params collect_params;

void maintenance_print(int *lumin, float *hygr, float *pressure, float *temp, DateTime dt);
bool check_consistency(int *lumin, float *hygr, float *pressure, float *temp);

void setup() {
  	// put your setup code here, to run once:
	init_rgb_led();
	init_buttons();
	init_RTC();
	check_config();
  	// start_serial();
	init_BME280();
	init_params(rtc.now().secondstime());
	// Serial.println(collect_params.last_collect_time);
	led.setColorRGB(0, 0, 255, 0);
	initialisation_interruption_tim(1000);
}

void loop()
{
	data_fetch();
}
