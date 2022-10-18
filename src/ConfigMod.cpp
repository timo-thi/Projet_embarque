#include <init_utilities.hpp>
#include <ConfigMod.hpp>
#include "eeprom_utilities.hpp"

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
}

bool wait_for_entry(String *command, int *value){
    while ((Serial.available() <= 0) && (timer >= 0)) {} // Wait for something to occur in serial buffer OR timeout
    if (timer <= 0) // if the timout stopped the while, return true to quit config mode
    {
        return true;
    }
    *command = Serial.readString();
    int pos = command->indexOf("=");
    Serial.print("pos : ");Serial.println(pos);
    if (pos != -1){
        *value = command->substring(pos+1).toInt();
        *command = command->substring(0, pos);
    }
    else {
        command->trim(); // Remove every parasite end chracters.
    }
    return false;
}

void wait_for_param()
{
    // Define default values for each parameter
    static int LOG_INTERVALL = 10;
    static int FILE_MAX_SIZE = 4096;
    static int TIMEOUT = 3000;
    static bool LUMIN = 1;
    static int LUMIN_LOW = 255;
    static int LUMIN_HIGH = 768;
    static bool TEMP_AIR = 1;
    static int MIN_TEMP_AIR = -10;
    static int MAX_TEMP_AIR = 60;
    static bool HYGR = 1;
    static int HYGR_MINT = 0;
    static int HYGR_MAXT = 50;
    static bool PRESSURE = 1;
    static int PRESSURE_MIN = 850;
    static int PRESSURE_MAX = 1080;

    // Answer handeling for a command
    bool C = 0;
    if (Serial.available() > 0) //Permet de voir ce qui sera écrit
    {
        C = Serial.read();  //pose à C la valeur écrite
        if(C == 1)
        {
            return ;    //aucun retour nécessaire
        }
        else Serial.println("Erreur "); //arrêt
    }

    // Start serial custom for user entry
    Serial.println("Entrez ce que vous souhaitez changer");
    Serial.println("------------------------------------");
    Serial.print("WWW_User:~$ ");

    String command;
    int value;
    if (wait_for_entry(&command, &value)) return; // If true, return to exit config mode

    Serial.print("Found command : "); // DEBUG
    Serial.print(command);           // or
    Serial.print("=");              // user interface
    Serial.println(value);         // custom

    // Check wich command is concerned, or, tell if not found
    if(command == String("LOG_INTERVALL"))
    {
        LOG_INTERVALL = value;
        Serial.println(LOG_INTERVALL);
    }
    else if(command == String("FILE_MAX_SIZE"))
    {
        FILE_MAX_SIZE = value;
        Serial.println(FILE_MAX_SIZE);
    }
    else if(command == String("TIMEOUT"))
    {
        TIMEOUT = value;
        Serial.println(TIMEOUT);
    }
    else if(command == String("LUMIN"))
    {
        LUMIN = value;
        Serial.println(LUMIN);
    }
    else if(command == String("LUMIN_LOW"))
    {
        LUMIN_LOW = value;
        Serial.println(LUMIN_LOW);
    }
    else if(command == String("LUMIN_HIGH"))
    {
        LUMIN_HIGH = value;
        Serial.println(LUMIN_HIGH);
    }
    else if(command == String("TEMP_AIR"))
    {
        TEMP_AIR = value;
        Serial.println(TEMP_AIR);
    }
    else if(command == String("MIN_TEMP_AIR"))
    {
        MIN_TEMP_AIR = value;
        Serial.println(MIN_TEMP_AIR);
    }
    else if(command == String("MAX_TEMP_AIR"))
    {
        MAX_TEMP_AIR = value;
        Serial.println(MAX_TEMP_AIR);
    }
    else if(command == String("HYGR"))
    {
        HYGR = value;
        Serial.println(HYGR);
    }
    else if(command == String("HYGR_MINT"))
    {
        HYGR_MINT = value;
        Serial.println(HYGR_MINT);
    }
    else if(command == String("HYGR_MAXT"))
    {
        HYGR_MAXT = value;
        Serial.println(HYGR_MAXT);
    }
    else if(command == String("PRESSURE"))
    {
        PRESSURE = value;
        Serial.println(PRESSURE);
    }
    else if(command == String("PRESSURE_MAX"))
    {
        PRESSURE_MAX = value;
        Serial.println(PRESSURE_MAX);
    }
    else if(command == String("PRESSURE_MIN"))
    {
        PRESSURE_MIN = value;
        Serial.println(PRESSURE_MIN);
    }
    else if(command == "RESET")
    {
        Serial.println("Reseting");
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
