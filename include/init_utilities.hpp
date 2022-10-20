#include <Arduino.h>
#include "ChainableLED.h"
#include "RTClib.h"
#include "eeprom_utilities.hpp"
#ifndef INIT_UTILITIES_FUNCTIONS
#define INIT_UTILITIES_FUNCTIONS

// Sensor collect params struct
struct Collect_params {
	int interval;
	int last_collect_time;
	int current_time;
	bool eco_alternate_gps;
	int mode;
	int previous_mode;
};

// Config param structure
typedef struct config_param {
	String name;
	int adr;
	int default_value;
	int min_value;
	int max_value;
	// int value;
} Config_param;

extern Config_param LOG_INTERVALL;
extern Config_param FILE_MAX_SIZE;
extern Config_param TIMEOUT;
extern Config_param LUMIN;
extern Config_param LUMIN_LOW;
extern Config_param LUMIN_HIGH;
extern Config_param TEMP_AIR;
extern Config_param MIN_TEMP_AIR;
extern Config_param MAX_TEMP_AIR;
extern Config_param HYGR;
extern Config_param HYGR_MINT;
extern Config_param HYGR_MAXT;
extern Config_param PRESSURE;
extern Config_param PRESSURE_MIN;
extern Config_param PRESSURE_MAX;

// Extern from main
extern Collect_params collect_params;

// Extern from init_utilities
extern ChainableLED led;

extern const int red_button;
extern const int green_button;

// Extern from mode_switch
extern void change_mode(int button);


// Serial monitor
void start_serial();
void stop_serial();

// Buttons
void init_buttons();

// RGB LED

void init_rgb_led();

// Timers
ISR(TIMER1_COMPA_vect);
void initialisation_interruption_tim(long uSecs);
extern int timer;
extern unsigned int configTimeout;

extern int timer;
extern unsigned int configTimeout;

//Led error handling
void sd_card_access_error();
void sd_card_full_error();
void consistency_data_error();
void sensor_access_error();
void gps_access_error();
void rtc_clock_access_error();

// init params
void init_params();

extern int timer;
extern unsigned int configTimeout;

//Led error handling
void sd_card_access_error();
void sd_card_full_error();
void consistency_data_error();
void sensor_access_error();
void gps_access_error();
void rtc_clock_access_error();

// init params
void init_params();

#endif


