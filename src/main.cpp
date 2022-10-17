#include "init_utilities.hpp"
#include "serial_tests.hpp"

void setup() {
  // put your setup code here, to run once:
  start_serial();
  init_rgb_led();
  test_init();
  // init_buttons();
  // init_button_interrupts();
  // initialisation_interruption_tim(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
}
