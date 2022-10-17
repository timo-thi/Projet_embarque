#include <init_utilities.hpp>

void check_config()
{
    //if (! digitalRead(red_button)) return; // Si jamais le bouton rouge n'est pas pressé

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
    
    //Commence à modéliser une interraction avec l'utilisateur
    Serial.println("Entrez ce que vous souhaitez changer");
    Serial.println("------------------------------------");
    Serial.print("3W_Config_Serial ");
    
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
    Serial.println("1 = LOG_INTERVALL = ");
    Serial.print(LOG_INTERVALL);
    Serial.println("2 = FILE_MAX_SIZE = ");
    Serial.print(FILE_MAX_SIZE);
    Serial.println("3 = RESET = ");
    Serial.print(RESET); 
    Serial.println("4 = VERSION = ");
    Serial.print(VERSION);  
    Serial.println("5 = TIMEOUT = ");
    Serial.print(TIMEOUT); 

    int B = 0;
    if (Serial.available() > 0) //Permet de voir ce qui sera écrit
    {
        B = Serial.read();  //pose à C la valeur écrite
        if(B == 1)
        {
            Serial.println("Entrez une nouvelle valeur de LOG_INTERVALL ");
            Serial.read();
            LOG_INTERVALL = Serial.read();
        }
        if(B == 2)
        {
            Serial.println("Entrez une nouvelle valeur de FILE_MAX_SIZE ");
            Serial.read();
            FILE_MAX_SIZE = Serial.read();
        }
        if(B == 3)
        {
            Serial.println("Entrez une nouvelle valeur de RESET ");
            Serial.read();
            RESET = Serial.read();
        }
        if(B == 4)
        {
            Serial.println("Entrez une nouvelle valeur de VERSION ");
            Serial.read();
            VERSION = Serial.read();
        }
        if(B == 5)
        {
            Serial.println("Entrez une nouvelle valeur de TIMEOUT (en ms) ");
            Serial.read();
            TIMEOUT = Serial.read();
        }
    }
}

void test(char A)
{
    Serial.println("entre la valeur de A");
    if (Serial.available() > 0)
    {
        A = Serial.read();
    }
    Serial.print(A);
}
