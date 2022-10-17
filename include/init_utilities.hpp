#include <Arduino.h>
#include "ChainableLED.h"
#ifndef INIT_UTILITIES_FUNCTIONS
#define INIT_UTILITIES_FUNCTIONS

extern ChainableLED led;

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

#endif
