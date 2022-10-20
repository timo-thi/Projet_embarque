#include "init_utilities.hpp"

#include "ConfigMod.hpp"
#include "sensors.hpp"

Collect_params collect_params;

void maintenance_print(int *lumin, float *hygr, float *pressure, float *temp, float *alt, DateTime *dt);

void setup() {
  	// put your setup code here, to run once:
  	// start_serial();
	init_rgb_led();
	init_buttons();
	check_config();
	init_params();
	init_BME280();
	init_RTC();
	led.setColorRGB(0, 0, 255, 0);
	initialisation_interruption_tim(1000);
}

void loop()
{
	int lumin;
	float hygr;
	float pressure;
	float temp;
	float alt;
	DateTime dt = rtc.now();
	// put your main code here, to run repeatedfloat y:
	if (collect_params.mode == 2){
		// maintenance mode, fetch and print
		LightSensor(&lumin);
		WeatherSensor(&temp, &hygr, &pressure, &alt);
		maintenance_print(&lumin, &hygr, &pressure, &temp, &alt, &dt);
		delay(1000);
	} else {
		// Std or eco
		if (collect_params.last_collect_time - dt.secondstime() < 60 * collect_params.interval) return;
		LightSensor(&lumin);
		WeatherSensor(&temp, &hygr, &pressure, &alt);
		collect_params.eco_alternate_gps = (collect_params.mode == 1) ? !collect_params.eco_alternate_gps : collect_params.eco_alternate_gps;
		collect_params.last_collect_time = dt.secondstime();
		//store in SD card
	}
}

bool check_consistency(int *lumin, float *hygr, float *pressure, float *temp){
	if (*lumin < fetch_eeprom_data(LUMIN_LOW.adr) || *lumin > fetch_eeprom_data(LUMIN_HIGH.adr)) return false;
	if (*hygr < fetch_eeprom_data(HYGR_MINT.adr) || *hygr > fetch_eeprom_data(HYGR_MAXT.adr)) return false;
	if (*pressure < fetch_eeprom_data(PRESSURE_MIN.adr) || *pressure > fetch_eeprom_data(PRESSURE_MAX.adr)) return false;
	if (*temp < fetch_eeprom_data(MIN_TEMP_AIR.adr) || *temp > fetch_eeprom_data(MAX_TEMP_AIR.adr)) return false;
}

void maintenance_print(int *lumin, float *hygr, float *pressure, float *temp, float *alt, DateTime *dt){
	Serial.write(13);
	Serial.print(F("Time : ")); Serial.print("");
}
