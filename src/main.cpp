#include "init_utilities.hpp"
#include "ConfigMod.hpp"

Collect_params collect_params;

void setup() {
	// put your setup code here, to run once:
	// start_serial();
	init_rgb_led();
	init_buttons();
	check_config();
	led.setColorRGB(0, 0, 255, 0);
	initialisation_interruption_tim(1000);
}

void loop()
{
	// put your main code here, to run repeatedly:
	switch (collect_params.mode)
	{
		case 1:
			collect_params.eco_alternate_gps = !collect_params.eco_alternate_gps; // Something else different compring to std mode ?
			break; // remove if we want to combine std and eco modes ?
		case 0:
			// fetch sensor data
			// check consistency
			// store in sd card
			break;

		case 2:
			// fetch sensor data
			// print data
			break;
		
		default:
			break;
	}
}
