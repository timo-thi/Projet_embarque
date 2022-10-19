#include "mode_switch.hpp"

void change_led_color(int mode);

void enable_economic_mode();
void disable_economic_mode();
void enable_maintenance_mode();
void disable_maintenance_mode();

void change_mode(int button){
    /*
    This function will run only if a button has been pressed long enough.
    The following mode is deduced from the current mode and the pressed button.
    The current mode is found from the include path.
    */
    switch (collect_params.mode) {
        case 0: // Current mode is standard
            if (button == green_button){
                enable_economic_mode();
            } else if (button == red_button){
                enable_maintenance_mode();
            }
            break;
        case 1: // Current mode is economic
            if (button == green_button){
                disable_economic_mode();
            } else if (button == red_button){
                enable_maintenance_mode();
            }
            break;
        case 2: // Current mode is maintenance
            if (button == green_button){
                return;
            } else if (button == red_button){
                disable_maintenance_mode();
            }
            break;
    }
}

void enable_economic_mode(){
    /*
    Changing to economic mode.
    */
    collect_params.previous_mode = collect_params.mode; // Store old mode
    collect_params.mode = 1;                           // Switch to new mode
    collect_params.interval *= 2;                     // Double collect interval for economic mode
    collect_params.eco_alternate_gps = false;        // Initialize gps alternater to false (next collect will not use GPS)
    change_led_color(collect_params.mode);          // Set the good led color
}

void disable_economic_mode(){
    /*
    Back to standard mode
    */
    collect_params.mode = 0;                   // Economic can be activated only from standard mode, so new mode is 0 (std)
    collect_params.interval /= 2;             // Divide collect interval by two because the economic mode is exited
    collect_params.eco_alternate_gps = true; // Set gps_alternate to true to let standard mode use it.
    change_led_color(collect_params.mode);  // Set the good led color
}

void enable_maintenance_mode(){
    /*
    Changing to maintenance mode
    */
    collect_params.previous_mode = collect_params.mode; // Store old mode
    collect_params.mode = 2;                           // Switch to new mode
    start_serial();                                   // Start serial for direct sensor feedback
    change_led_color(collect_params.mode);           // Set the good led color
}

void disable_maintenance_mode(){
    /*
    Backto previous mode
    */
    collect_params.mode = collect_params.previous_mode; // Switch back to previous mode
    stop_serial();                                     // End serial because it is not necessary anymore
    change_led_color(collect_params.mode);            // Set the good led color
}

void change_led_color(int mode){
    /*
    Led color switch handler.
    Choose the led color according to the mode passed in parameter.
    */
    switch (mode)
    {
    case 0:
        led.setColorRGB(0, 0, 200, 0);
        break;
    case 1:
        led.setColorRGB(0, 0, 0, 200);
        break;
    case 2:
        led.setColorRGB(0, 255, 128, 0);
        break;
    }
}
