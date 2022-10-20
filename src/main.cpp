#include "init_utilities.hpp"
#include "ConfigMod.hpp"
#include "SD_Card.hpp"

Collect_params collect_params;

void setup() {
  // put your setup code here, to run once:
  start_serial();
  init_rgb_led();
  init_buttons();
  check_config();
  led.setColorRGB(0, 0, 255, 0);
  initialisation_interruption_tim(1000);
  String donnee ;
  donnee = "une data de, merde sdf sdf sdf, sfd ZPH, Zhghjghjghjghjgjh";
  Write_SD_Card(donnee);
}

void loop()
{
  // put your main code here, to run repeatedly:
}
