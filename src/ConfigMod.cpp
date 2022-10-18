#include <init_utilities.hpp>
#include <ConfigMod.hpp>

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

    String command;
    int value;
    Serial.print("WWW_User:~$ ");
    while ((Serial.available() <= 0) && (timer >= 0)) {}
    if (timer <= 0) 
    {
        return;
    }
    command = Serial.readStringUntil('=');
    Serial.read();
    value = Serial.parseInt();
    while (Serial.available() > 0) Serial.read();
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
    if(command == String("FILE_MAX_SIZE"))
    //Si la valeur entrée est 1 alors on modifie FILE_MAX_SIZE
    {
        FILE_MAX_SIZE = value;
        Serial.println(FILE_MAX_SIZE);
    }
    if(command == String("TIMEOUT"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        TIMEOUT = value;
        Serial.println(TIMEOUT);
    }
    if(command == String("LUMIN"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        LUMIN = value;
        Serial.println(LUMIN);
    }
        if(command == String("LUMIN_LOW"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        LUMIN_LOW = value;
        Serial.println(LUMIN_LOW);
    }
        if(command == String("LUMIN_HIGH"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        LUMIN_HIGH = value;
        Serial.println(LUMIN_HIGH);
    }
        if(command == String("TEMP_AIR"))
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
        if(command == String("MAX_TEMP_AIR"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        MAX_TEMP_AIR = value;
        Serial.println(MAX_TEMP_AIR);
    }
        if(command == String("HYGR"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        HYGR = value;
        Serial.println(HYGR);
    }
    if(command == String("HYGR_MINT"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        HYGR_MINT = value;
        Serial.println(HYGR_MINT);
    }
    if(command == String("HYGR_MAXT"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        HYGR_MAXT = value;
        Serial.println(HYGR_MAXT);
    }
    if(command == String("TIMEOUT"))
    //Si la valeur entrée est 1 alors on modifie TIMEOUT
    {
        TIMEOUT = value;
        Serial.println(TIMEOUT);
    }
}
