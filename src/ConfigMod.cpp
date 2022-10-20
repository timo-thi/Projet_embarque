#include <init_utilities.hpp>
#include <ConfigMod.hpp>
#include "eeprom_utilities.hpp"
#include "RTClib.h"

Config_param LOG_INTERVALL = {"LOG_INTERVALL", 0, 10, 1}; //, fetch_eeprom_data(0)};
Config_param FILE_MAX_SIZE = {"FILE_MAX_SIZE", 2, 4096, 1}; //, fetch_eeprom_data(2)};
Config_param TIMEOUT = {"TIMEOUT", 6, 1, 0, 1}; //, fetch_eeprom_data(4)};
Config_param LUMIN = {"LUMIN", 8, 1, 0, 1}; //, fetch_eeprom_data(6)};
Config_param LUMIN_LOW = {"LUMIN_LOW", 10, 255, 0, 1023}; //, fetch_eeprom_data(8)};
Config_param LUMIN_HIGH = {"LUMIN_HIGH", 12, 768, 0, 1023}; //, fetch_eeprom_data(10)};
Config_param TEMP_AIR = {"TEMP_AIR", 14, 1, 0, 1}; //, fetch_eeprom_data(12)};
Config_param MIN_TEMP_AIR = {"MIN_TEMP_AIR", 16, -10, -40, 85}; //, fetch_eeprom_data(14)};
Config_param MAX_TEMP_AIR = {"MAX_TEMP_AIR", 18, 60, -40, 85}; //, fetch_eeprom_data(16)};
Config_param HYGR = {"HYGR", 20, 1, 0, 1}; //, fetch_eeprom_data(18)};
Config_param HYGR_MINT = {"HYGR_MINT", 22, 0, -40, 85}; //, fetch_eeprom_data(20)};
Config_param HYGR_MAXT = {"HYGR_MAXT", 24, 50, -40, 85}; //, fetch_eeprom_data(22)};
Config_param PRESSURE = {"PRESSURE", 26, 0, 0, 1}; //, fetch_eeprom_data(24)};
Config_param PRESSURE_MIN = {"PRESSURE_MIN", 28, 850, 300, 1100}; //, fetch_eeprom_data(26)};
Config_param PRESSURE_MAX = {"PRESSURE_MAX", 30, 1080, 300, 1100}; //, fetch_eeprom_data(28)};

Config_param *params_point[15] = {&LOG_INTERVALL, &FILE_MAX_SIZE, &TIMEOUT, &LUMIN, &LUMIN_LOW, &LUMIN_HIGH, &TEMP_AIR, &MIN_TEMP_AIR, &MAX_TEMP_AIR, &HYGR, &HYGR_MINT, &HYGR_MAXT, &PRESSURE, &PRESSURE_MIN, &PRESSURE_MAX};

void wait_for_param();
void exec_param(String command, int value, bool to_store);

void check_config()
{
    if (digitalRead(red_button) == HIGH) return; // Si jamais le bouton rouge n'est pas pressé
    led.setColorRGB(0, 55, 55, 0); // Set led color (0,R,G,B)
    start_serial();
    collect_params.mode = 3; // Config mode number is 3.
    initialisation_interruption_tim(1000000); // Définit le timer 1 à la valeur indiquée. (1000000 -> une occurence par sec)
    timer = configTimeout; //Initialiser le timer
    while (timer > 0) // While timeout isn't exceeded
    {
        wait_for_param();
    }
    stop_serial();
    collect_params.mode = 0;
}

bool wait_for_entry(String *command, int *value, bool *to_store){
    while ((Serial.available() <= 0) && (timer >= 0)) {} // Wait for something to occur in serial buffer OR timeout
    if (timer <= 0) // if the timout stopped the while, return true to quit config mode
    {
        return true;
    }
    *command = Serial.readString(); // Read string and store it directly into command
    int pos = command->indexOf(F("=")); // Check if "=" chracter occurs in command
    // Serial.print("pos : ");Serial.println(pos); // DEBUG
    if (pos != -1){ // If "=" found in command
        *to_store = true;
        *value = command->substring(pos+1).toInt(); // Isolate value and convert into integer or long.
        *command = command->substring(0, pos); // Isolate command.available()
        return false;
    }
    else {
        *to_store = false;
        command->trim(); // Remove every parasite end chracters.
        return false;
    }
}

void wait_for_param()
{
    // Start serial custom for user entry
    Serial.println(F("Entrez ce que vous souhaitez changer"));
    Serial.println(F("------------------------------------"));
    Serial.print(F("WWW_User:~$ "));

    String command;
    bool to_store; // Store if an equal sign was stored, and deduce if the value variable have to be stored
    int value;
    if (wait_for_entry(&command, &value, &to_store)) return; // If true, return to exit config mode
    
    timer = configTimeout;
    // Serial.print("Found command : "); // DEBUG
    Serial.println(command);           // replace with : Serial.print(command);           // or
    // Serial.print("=");              // user interface
    // Serial.println(value);         // custom

    exec_param(command, value, to_store);
}

bool extract_clock_param(String data, int *hm, int *mj, int *sa, String separator){
    /*String contains the command data without the command name*/
    int pos = data.indexOf(separator);
    if(pos == -1) return true;
    *hm = data.substring(0, pos).toInt();
    data = data.substring(pos+1);
    pos = data.indexOf(separator);
    if(pos == -1) return true;
    *mj = data.substring(0, pos).toInt();
    *sa = data.substring(pos+1).toInt();
    return false;
}

void exec_param(String command, int value, bool to_store)
{
    for (int i = 0; i < 15; i++){
        if (command == params_point[i]->name){
            if (to_store){
                if ((value > params_point[i]->max_value && params_point[i]->max_value) || value < params_point[i]->min_value) {
                    Serial.println(F("Value exceed max or min. Please refer to manual."));
                    return;
                }
                // params_point[i]->value = value;
                send_eeprom_data(params_point[i]->adr, value); // params_point[i]->value);
                Serial.print(F("Updated params_point[i]->, set value : ")); Serial.println(value);
            } else {
                Serial.print(F("Current value : "));Serial.println(fetch_eeprom_data(params_point[i]->adr));
            }
            return;
        }
    }
    int hm, mj, sa; // Heure/mois, Minute/jour, Secondes/annee
    if(command == F("RESET"))
    {
        Serial.print(F("Reseting..."));
        for (int i = 0; i < 15; i++){
            send_eeprom_data(params_point[i]->adr, params_point[i]->default_value);
            // params_point[i]->value = fetch_eeprom_data(params_point[i]->adr);
        }
        Serial.println(F("Done."));
    }
    else if(command == F("VERSION"))
    {
        Serial.println(F("V1.0 S:lMPbPj2T"));
    }
    else if(command.startsWith(F("CLOCK")))
    {
        RTC_DS1307 clock;
        clock.begin();
        if (extract_clock_param(command.substring(6), &hm, &mj, &sa, ":")){
            Serial.println(F("Format error"));
            return;
        }
        clock.adjust(DateTime(clock.now().year(), clock.now().month(), clock.now().day(), hm, mj, sa));
        Serial.println(clock.now().toString("=> YY:MM:DD hh:mm:ss")); // Serial.println(F("Clock adjusted"));
    }
    else if(command.startsWith(F("DATE")))
    {
        RTC_DS1307 clock;
        clock.begin();
        if (extract_clock_param(command.substring(5), &hm, &mj, &sa, ",")){
            Serial.println(F("Format error"));
            return;
        }
        clock.adjust(DateTime(sa, hm, mj, clock.now().hour(), clock.now().minute(), clock.now().second()));
        Serial.println(clock.now().toString("=> YY:MM:DD hh:mm:ss")); // Serial.println(F("Clock adjusted"));
    }
    // else if(command == F("DAY"))
    // {
    //     Serial.println(F("Day..."));
    // }
    else
    {
        Serial.println(F("Command not found X"));
    }
}
