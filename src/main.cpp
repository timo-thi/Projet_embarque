#include "init_utilities.hpp"

void setup() {
  // put your setup code here, to run once:
  start_serial();
  init_rgb_led();
  init_buttons();
  init_button_interrupts();
  initialisation_interruption_tim(100);
}

void loop() {
  // put your main code here, to run repeatedly:
}
