#include "init_utilities.hpp"
#include "ConfigMod.hpp"

Collect_params collect_params;

void setup() {
  // put your setup code here, to run once:
  // start_serial();
  init_rgb_led();
  init_buttons();
  check_config();
  present();
  init_button_interrupts();
  initialisation_interruption_tim(1000);
}

void loop()
{
  // put your main code here, to run repeatedly:
}
