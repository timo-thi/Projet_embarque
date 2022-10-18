#include <Arduino.h>
#include "ChainableLED.h"
#ifndef INIT_UTILITIES_FUNCTIONS
#define INIT_UTILITIES_FUNCTIONS


struct Collect_params {
  int interval;
  int last_collect_time;
  int current_time;
  bool eco_alternate_gps;
  int mode;
  int previous_mode;

  };

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
void init_button_interrupts();

// RGB LED

void init_rgb_led();

// Timers
ISR(TIMER1_COMPA_vect);
void initialisation_interruption_tim(long uSecs);
extern unsigned int timer;
extern unsigned int configTimeout;

#endif
