#include <Arduino.h>
#include "ChainableLED.h"
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
	int value;
	int min_value;
	int max_value;
} Config_param;

static Config_param LOG_INTERVALL = {"LOG_INTERVALL", 0, 10, 1};
static Config_param FILE_MAX_SIZE = {"FILE_MAX_SIZE", 2, 4096, 1};
static Config_param TIMEOUT = {"TIMEOUT", 6, 1, 0, 1};
static Config_param LUMIN = {"LUMIN", 8, 1, 0, 1};
static Config_param LUMIN_LOW = {"LUMIN_LOW", 10, 255, 0, 1023};
static Config_param LUMIN_HIGH = {"LUMIN_HIGH", 12, 768, 0, 1023};
static Config_param TEMP_AIR = {"TEMP_AIR", 14, 1, 0, 1};
static Config_param MIN_TEMP_AIR = {"MIN_TEMP_AIR", 16, -10, -40, 85};
static Config_param MAX_TEMP_AIR = {"MAX_TEMP_AIR", 16, 60, -40, 85};
static Config_param HYGR = {"HYGR", 18, 1, 0, 1};
static Config_param HYGR_MINT = {"HYGR_MINT", 20, 0, -40, 85};
static Config_param HYGR_MAXT = {"HYGR_MAXT", 22, 50, -40, 85};
static Config_param PRESSURE = {"PRESSURE", 24, 0, 0, 1};
static Config_param PRESSURE_MIN = {"PRESSURE_MIN", 26, 850, 300, 1100};
static Config_param PRESSURE_MAX = {"PRESSURE_MAX", 28, 1080, 300, 1100};



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

#endif
