#include <init_utilities.hpp>

void check_config()
{
    if (! digitalRead(red_button)) return; // Si jamais le bouton rouge n'est pas pressé

    led.setColorRGB(0, 55, 55, 0); // Set led color (0,R,G,B)
}

void present()
{
    //Pose les paramètres par défaut
    int LOG_INTERVALL = 10;
    int FILE_MAX_SIZE = 4096;
    bool RESET = 0;
    bool VERSION = 0;
    int TIMEOUT = 3000;
    
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

    //Montre à l'utilisateur les options disponibles
    Serial.print("1 = LOG_INTERVALL = ");
    //Définit LOG_INTERVALL sur 1
    Serial.println(LOG_INTERVALL);
    //Donne la valeur actuelle ou par défaut de LOG_INTERVALL
    Serial.print("2 = FILE_MAX_SIZE = ");
    //Définit FILE_MAX_SIZE sur 2
    Serial.println(FILE_MAX_SIZE);
    //Donne la valeur actuelle ou par défaut de FILE_MAX_SIZE
    Serial.print("3 = RESET = ");
    //Définit RESET sur 3
    Serial.println(RESET); 
    //Donne la valeur actuelle ou par défaut de RESET
    Serial.print("4 = VERSION = ");
    //Définit VERSION sur 4
    Serial.println(VERSION);
    //Donne la valeur actuelle ou par défaut de VERSION
    Serial.print("5 = TIMEOUT = ");
    //Définit TIMEOUT sur 5
    Serial.println(TIMEOUT);
    //Donne la valeur actuelle ou par défaut de TIMEOUT

    //Commence à modéliser une interraction avec l'utilisateur
    Serial.println("Entrez ce que vous souhaitez changer");
    Serial.println("------------------------------------");
    Serial.print("3W_Config_Serial ");
    Serial.available();
    Serial.read();

    int B = 0;
    if (Serial.available() > 0) //Permet de voir ce qui sera écrit
    {
        B = Serial.read();  //pose à B la valeur écrite
        if(B == 1)
        //Si la valeur entrée est 1 alors on modifie LOG_INTERVALL
        {
            Serial.println("Entrez une nouvelle valeur de LOG_INTERVALL ");
            Serial.read();
            //Laisse entrer la nouvelle donnée
            LOG_INTERVALL = Serial.read();
            //Donne la nouvelle valeur
        }
        if(B == 2)
        //Si la valeur entrée est 1 alors on modifie FILE_MAX_SIZE
        {
            Serial.println("Entrez une nouvelle valeur de FILE_MAX_SIZE ");
            Serial.read();
            //Laisse entrer la nouvelle donnée
            FILE_MAX_SIZE = Serial.read();
            //Donne la nouvelle valeur
        }
        if(B == 3)
        //Si la valeur entrée est 1 alors on modifie RESET
        {
            Serial.println("Entrez une nouvelle valeur de RESET ");
            Serial.read();
            //Laisse entrer la nouvelle donnée
            RESET = Serial.read();
            //Donne la nouvelle valeur
        }
        if(B == 4)
        //Si la valeur entrée est 1 alors on modifie VERSION
        {
            Serial.println("Entrez une nouvelle valeur de VERSION ");
            Serial.read();
            //Laisse entrer la nouvelle donnée
            VERSION = Serial.read();
            //Donne la nouvelle valeur
        }
        if(B == 5)
        //Si la valeur entrée est 1 alors on modifie TIMEOUT
        {
            Serial.println("Entrez une nouvelle valeur de TIMEOUT (en ms) ");
            Serial.read();
            //Laisse entrer la nouvelle donnée
            TIMEOUT = Serial.read();
            //Donne la nouvelle valeur
        }
    }
}
