#include "init_utilities.hpp"
#include "ConfigMod.hpp"
#include "recuperation_donnee_capteurs.hpp"

Collect_params collect_params;

void setup() {
  // put your setup code here, to run once:
  // start_serial();
  init_rgb_led();
  init_buttons();
  check_config();
  led.setColorRGB(0, 0, 255, 0);
  initialisation_interruption_tim(1000);
  initialisation_interruption_tim2();
  void init_gps();
  recuperation_donnees_GPS();
}

void loop()
{
  recuperation_donnees_GPS();
  // put your main code here, to run repeatedly:
}
