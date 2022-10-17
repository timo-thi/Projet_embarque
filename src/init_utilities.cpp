#include "init_utilities.hpp"

// Global variables
const int green_button = 2; // Green button pin on D2 shield interface
const int red_button = 3; // Red button pin on D2 shield interface
unsigned int button_timer = 5000; // Time to wait to consider a button press in ms
unsigned int timer = 5000; // Time counter in ms, will be decreased if a button is pressed, or reset at button_timer if new button pressed.

bool ledState = false; // The ledState shows if the led is on or off however the color
ChainableLED led(7, 8, 1); // This object is the RGB LED handler

bool red_bascule = false; // Indicates if the red button is pressed
bool green_bascule = false; // Indicates if the green button is pressed

// Serial

void start_serial(){
  Serial.begin(9600); // Starting serial
  Serial.println("Started serial monitor\n"); // Serial end disclamer
}

void stop_serial(){
    Serial.println("Ending serial monitor\n"); // Serial end disclamer
    Serial.end(); // Stoping serial
}

// RGB Led

void init_rgb_led(){
  /*
  Initialisation de la led.
  Motif rouge - vert - bleu avec 100ms d'écart avant d'éteindre pour la suite du programme.
  */
  led.init();
  led.setColorRGB(0, 255, 0, 0); // Rouge
  delay(100);
  led.setColorRGB(0, 0, 255, 0); // Vert
  delay(100);
  led.setColorRGB(0, 0, 0, 255); // Bleu
  delay(100);
  led.setColorRGB(0, 0, 0, 0); // Etteint
  ledState = false; // Mise à jour de l'état de la led pour la suite du programme.
}

void allumer(){
  /*This function was created for debug*/
  led.setColorRGB(0, 255, 255, 255); // White
  ledState = true; // LED state change
}

void etteindre(){
  /*This function was created for debug*/
  led.setColorRGB(0, 0, 0, 0); // Off
  ledState = false; // LED state change
}

// Interrupts functions

void green_button_interrupt(){
  if (digitalRead(green_button) == LOW) { // Check if the button is pressed
    green_bascule = true;                // If yes, it means that the button was juste pressed
    timer = button_timer;               // the timer can be reset to global button_timer
    // Serial.println("green");           // DEBUG
  } else {
    green_bascule = false;           // else the button isn't pressed anymore
  }
}

void red_button_interrupt(){
  if (digitalRead(red_button) == LOW) { // Check if the button is pressed
    red_bascule = true;                // If yes, it means that the button was juste pressed
    timer = button_timer;             // the timer can be reset to global button_timer
    // Serial.println("red");           // DEBUG
  } else {
    red_bascule = false;           // else the button isn't pressed anymore
  }
}

// Buttons

void init_buttons(){
  /*
  Initialize the two buttons.
  They will be used for mode switching.
  */
  pinMode(red_button, INPUT_PULLUP);
  pinMode(green_button, INPUT_PULLUP);
}

void init_button_interrupts(){
  /*
  We want to detect each button change for both red and green buttons.
  */
  attachInterrupt(digitalPinToInterrupt(red_button), red_button_interrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(green_button), green_button_interrupt, CHANGE);
}

// Timers

// Timer interruption management
ISR(TIMER1_COMPA_vect){
  if (green_bascule || red_bascule){ // If button pressed
    timer -= 1;                     // Decrease timer
    // Serial.println("Timer -1");    // DEBUG
  }
  if (timer == 0) { // If the timer reaches 0, the button press time is over and the code can run further according to the normal button function
    if (ledState){          // This
      etteindre();         // is
      ledState = false;   // only
    } else {             // for
      allumer();        // debug
      ledState = true; // and will be removed once the mode switch is completed.
    }
  }
}

void initialisation_interruption_tim(long uSecs){
  noInterrupts(); // Disable interrupts during configuration of timer
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = ((16e6/256L * uSecs) / (1e6) ) - 1;
  // Serial.println(OCR1A); // DEBUG
  
  TCCR1B |= (1 << WGM12);    // CTC mode
  TCCR1B |= (1 << CS12);    // Choose 256 prescaler
  TIMSK1 |= (1 << OCIE1A); // Enable timer
  
  interrupts(); // Ensable interrupts when configuration is complete
}
