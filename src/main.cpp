#include "init_utilities.hpp"

struct Collect_params {
  int interval;
  int last_collect_time;
  int current_time;
  bool eco_alternate_gps;
  int mode;
  int previous_mode;

  } collect_params;

void setup() {
  // put your setup code here, to run once:
  start_serial();
  init_rgb_led();
  init_buttons();
  init_button_interrupts();
  initialisation_interruption_tim(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
}
