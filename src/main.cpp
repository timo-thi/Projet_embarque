#include "init_utilities.hpp"
#include "ConfigMod.hpp"
#include "SD_Card.hpp"
#include "sensors.hpp"

Collect_params collect_params;

void maintenance_print(int *lumin, float *hygr, float *pressure, float *temp, DateTime dt);
bool check_consistency(int *lumin, float *hygr, float *pressure, float *temp);

void setup() {
  	// put your setup code here, to run once:
	init_rgb_led();
	init_buttons();
	init_RTC();
	check_config();
  	start_serial();
	init_BME280();
	init_params(rtc.now().secondstime());
	Serial.println(collect_params.last_collect_time);
	led.setColorRGB(0, 0, 255, 0);
	initialisation_interruption_tim(1000);
}

void loop()
{
	int lumin;
	float hygr;
	float pressure;
	float temp;
	// put your main code here, to run repeatedfloat y:
	if (collect_params.mode == 2){
		// maintenance mode, fetch and print
		LightSensor(&lumin);
		WeatherSensor(&temp, &hygr, &pressure);
		maintenance_print(&lumin, &hygr, &pressure, &temp, rtc.now());
		delay(1000);
	} else {
		// Std or eco
		// Serial.print("last ");Serial.println(collect_params.last_collect_time);
		// Serial.print("last ");Serial.println(dt.secondstime());
		Serial.print("diff ");Serial.println(rtc.now().secondstime() - collect_params.last_collect_time);
		// Serial.print("intr ");Serial.println(collect_params.interval);
		if (((int)rtc.now().secondstime() - (int)collect_params.last_collect_time) < (60 * collect_params.interval)) return;
		LightSensor(&lumin);
		WeatherSensor(&temp, &hygr, &pressure);
		Serial.print("l : ");Serial.println(lumin);
		Serial.print("h : ");Serial.println(hygr);
		Serial.print("p : ");Serial.println(pressure);
		Serial.print("t : ");Serial.println(temp);
		if (!check_consistency(&lumin, &hygr, &pressure, &temp)) {
			consistency_data_error();
		}
		collect_params.eco_alternate_gps = (collect_params.mode == 1) ? !collect_params.eco_alternate_gps : collect_params.eco_alternate_gps;
		collect_params.last_collect_time = (unsigned long)rtc.now().secondstime();
		Write_SD_Card(&lumin, &hygr, &pressure, &temp);
	}
}

bool check_consistency(int *lumin, float *hygr, float *pressure, float *temp){
	// if (*lumin < fetch_eeprom_data(LUMIN_LOW.adr) || *lumin > fetch_eeprom_data(LUMIN_HIGH.adr)) return false;
	if (*hygr < fetch_eeprom_data(HYGR_MINT.adr) || *hygr > fetch_eeprom_data(HYGR_MAXT.adr)) return false;
	if (*pressure < fetch_eeprom_data(PRESSURE_MIN.adr) || *pressure > fetch_eeprom_data(PRESSURE_MAX.adr)) return false;
	if (*temp < fetch_eeprom_data(MIN_TEMP_AIR.adr) || *temp > fetch_eeprom_data(MAX_TEMP_AIR.adr)) return false;
	return true;
}

void maintenance_print(int *lumin, float *hygr, float *pressure, float *temp, DateTime dt){
	Serial.write(13);
	Serial.print(F("Time : ")); Serial.print("");
}
