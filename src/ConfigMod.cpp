#include <init_utilities.hpp>
#include <ConfigMod.hpp>
#include "eeprom_utilities.hpp"

static Config_param LOG_INTERVALL = {"LOG_INTERVALL", 0, 10, 1};
static Config_param FILE_MAX_SIZE = {"FILE_MAX_SIZE", 2, 4096, 1};
static Config_param TIMEOUT = {"TIMEOUT", 6, 1, 0, 1};
static Config_param LUMIN = {"LUMIN", 8, 1, 0, 1};
static Config_param LUMIN_LOW = {"LUMIN_LOW", 10, 255, 0, 1023};
static Config_param LUMIN_HIGH = {"LUMIN_HIGH", 12, 768, 0, 1023};
static Config_param TEMP_AIR = {"TEMP_AIR", 14, 1, 0, 1};
static Config_param MIN_TEMP_AIR = {"MIN_TEMP_AIR", 16, -10, -40, 85};
static Config_param MAX_TEMP_AIR = {"MAX_TEMP_AIR", 16, 60, -40, 85};
static Config_param HYGR = {"HYGR", 18, 1, 0, 1};
static Config_param HYGR_MINT = {"HYGR_MINT", 20, 0, -40, 85};
static Config_param HYGR_MAXT = {"HYGR_MAXT", 22, 50, -40, 85};
static Config_param PRESSURE = {"PRESSURE", 24, 0, 0, 1};
static Config_param PRESSURE_MIN = {"PRESSURE_MIN", 26, 850, 300, 1100};
static Config_param PRESSURE_MAX = {"PRESSURE_MAX", 28, 1080, 300, 1100};

void wait_for_param();

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

bool wait_for_entry(String *command, int *value){
    while ((Serial.available() <= 0) && (timer >= 0)) {} // Wait for something to occur in serial buffer OR timeout
    if (timer <= 0) // if the timout stopped the while, return true to quit config mode
    {
        return true;
    }
    *command = Serial.readString(); // Read string and store it directly into command
    int pos = command->indexOf("="); // Check if "=" chracter occurs in command
    Serial.print("pos : ");Serial.println(pos); // DEBUG
    if (pos != -1){ // If "=" found in command
        *value = command->substring(pos+1).toInt(); // Isolate value and convert into integer or long.
        *command = command->substring(0, pos); // Isolate command.available()
    }
    else {
        command->trim(); // Remove every parasite end chracters.
    }
    return false;
}

void wait_for_param()
{
    // Start serial custom for user entry
    Serial.println("Entrez ce que vous souhaitez changer");
    Serial.println("------------------------------------");
    Serial.print("WWW_User:~$ ");

    String command;
    int value;
    if (wait_for_entry(&command, &value)) return; // If true, return to exit config mode
    
    timer = configTimeout;
    Serial.print("Found command : "); // DEBUG
    Serial.print(command);           // or
    Serial.print("=");              // user interface
    Serial.println(value);         // custom

    // Check wich command is concerned, or, tell if not found
    if(command == String("LOG_INTERVALL"))
    {
        LOG_INTERVALL.value = value;
        Serial.println(LOG_INTERVALL.value);
    }
    else if(command == String("FILE_MAX_SIZE"))
    {
        FILE_MAX_SIZE.value = value;
        Serial.println(FILE_MAX_SIZE.value);
    }
    else if(command == String("TIMEOUT"))
    {
        TIMEOUT.value = value;
        Serial.println(TIMEOUT.value);
    }
    else if(command == String("LUMIN"))
    {
        LUMIN.value = value;
        Serial.println(LUMIN.value);
    }
    else if(command == String("LUMIN_LOW"))
    {
        LUMIN_LOW.value = value;
        Serial.println(LUMIN_LOW.value);
    }
    else if(command == String("LUMIN_HIGH"))
    {
        LUMIN_HIGH.value = value;
        Serial.println(LUMIN_HIGH.value);
    }
    else if(command == String("TEMP_AIR"))
    {
        TEMP_AIR.value = value;
        Serial.println(TEMP_AIR.value);
    }
    else if(command == String("MIN_TEMP_AIR"))
    {
        MIN_TEMP_AIR.value = value;
        Serial.println(MIN_TEMP_AIR.value);
    }
    else if(command == String("MAX_TEMP_AIR"))
    {
        MAX_TEMP_AIR.value = value;
        Serial.println(MAX_TEMP_AIR.value);
    }
    else if(command == String("HYGR"))
    {
        HYGR.value = value;
        Serial.println(HYGR.value);
    }
    else if(command == String("HYGR_MINT"))
    {
        HYGR_MINT.value = value;
        Serial.println(HYGR_MINT.value);
    }
    else if(command == String("HYGR_MAXT"))
    {
        HYGR_MAXT.value = value;
        Serial.println(HYGR_MAXT.value);
    }
    else if(command == String("PRESSURE"))
    {
        PRESSURE.value = value;
        Serial.println(PRESSURE.value);
    }
    else if(command == String("PRESSURE_MAX"))
    {
        PRESSURE_MAX.value = value;
        Serial.println(PRESSURE_MAX.value);
    }
    else if(command == String("PRESSURE_MIN"))
    {
        PRESSURE_MIN.value = value;
        Serial.println(PRESSURE_MIN.value);
    }
    else if(command == "RESET")
    {
        Serial.print("Reseting...");
    }
    else if(command == String("VERSION"))
    {
        Serial.println("Version and serial number");
    }
    else
    {
        Serial.println("Command not found X");
    }
}
