#include <init_utilities.hpp>
#include <ConfigMod.hpp>
#include "eeprom_utilities.hpp"

void check_config()
{
    if (digitalRead(red_button) == HIGH) return; // Si jamais le bouton rouge n'est pas pressé
    led.setColorRGB(0, 55, 55, 0); // Set led color (0,R,G,B)
    start_serial();
    collect_params.mode = 3;
    initialisation_interruption_tim(10000); //Définit le timer 1 à la valeur indiquée
    timer = configTimeout; //Initialiser le timer
    Serial.println(timer);
    while (timer > 0)
    {
        present();
    }
}

void wait_for_entry(String *command, int *value){
    while ((Serial.available() <= 0) && (timer >= 0)) {}
    if (timer <= 0) 
    {
        return;
    }
    *command = Serial.readStringUntil('=');
    Serial.read();
    *value = Serial.parseInt();
    while (Serial.available() > 0) Serial.read();
}

void present()
{
    //Pose les paramètres par défaut
    int LOG_INTERVALL = 10;
    int FILE_MAX_SIZE = 4096;
    int TIMEOUT = 3000;
    bool LUMIN = 1;
    int LUMIN_LOW = 255;
    int LUMIN_HIGH = 768;
    bool TEMP_AIR = 1;
    int MIN_TEMP_AIR = -10;
    int MAX_TEMP_AIR = 60;
    bool HYGR = 1;
    int HYGR_MINT = 0;
    int HYGR_MAXT = 50;
    bool PRESSURE = 1;
    int PRESSURE_MIN = 850;
    int PRESSURE_MAX = 1080;

    //gestion d'une réponse pour la configuration
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

    //Commence à modéliser une interraction avec l'utilisateur
    Serial.println("Entrez ce que vous souhaitez changer");
    Serial.println("------------------------------------");
    Serial.print("WWW_User:~$ ");

    String command;
    int value;
    wait_for_entry(&command, &value);
    
    Serial.print("Found command : ");
    Serial.print(command);
    Serial.print("=");
    Serial.println(value);

    if(command == String("LOG_INTERVALL"))
    //Si la valeur entrée est 1 alors on modifie LOG_INTERVALL
    {
        LOG_INTERVALL = value;
        Serial.println(LOG_INTERVALL);
    }
    else if(command == String("FILE_MAX_SIZE"))
    //Si la valeur entrée est 1 alors on modifie FILE_MAX_SIZE
    {
        FILE_MAX_SIZE = value;
        Serial.println(FILE_MAX_SIZE);
    }
    else if(command == String("TIMEOUT"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        TIMEOUT = value;
        Serial.println(TIMEOUT);
    }
    else if(command == String("LUMIN"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        LUMIN = value;
        Serial.println(LUMIN);
    }
    else if(command == String("LUMIN_LOW"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        LUMIN_LOW = value;
        Serial.println(LUMIN_LOW);
    }
    else if(command == String("LUMIN_HIGH"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        LUMIN_HIGH = value;
        Serial.println(LUMIN_HIGH);
    }
    else if(command == String("TEMP_AIR"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        TEMP_AIR = value;
        Serial.println(TEMP_AIR);
    }
    if(command == String("MIN_TEMP_AIR"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        MIN_TEMP_AIR = value;
        Serial.println(MIN_TEMP_AIR);
    }
    else if(command == String("MAX_TEMP_AIR"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        MAX_TEMP_AIR = value;
        Serial.println(MAX_TEMP_AIR);
    }
    else if(command == String("HYGR"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        HYGR = value;
        Serial.println(HYGR);
    }
    else if(command == String("HYGR_MINT"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        HYGR_MINT = value;
        Serial.println(HYGR_MINT);
    }
    else if(command == String("HYGR_MAXT"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        HYGR_MAXT = value;
        Serial.println(HYGR_MAXT);
    }
    else if(command == String("PRESSURE"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        PRESSURE = value;
        Serial.println(PRESSURE);
    }
    else if(command == String("PRESSURE_MAX"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        PRESSURE_MAX = value;
        Serial.println(PRESSURE_MAX);
    }
    else if(command == String("PRESSURE_MIN"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        PRESSURE_MIN = value;
        Serial.println(PRESSURE_MIN);
    }
}
