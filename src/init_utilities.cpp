#include "init_utilities.hpp"

// Global variables
const int green_button = 2;
const int red_button = 3;
unsigned int button_timer = 5000;
unsigned int timer = 5000;

bool ledState = false;
ChainableLED led(8, 7, 1);

bool red_bascule = false;
bool green_bascule = false;

// Serial

void start_serial(){
    Serial.begin(9600);
    Serial.println("Started serial monitor\n");
}

void stop_serial(){
    Serial.println("Ending serial monitor\n");
    Serial.end();
}

// RGB Led

void allumer(){
  led.setColorRGB(0, 255, 255, 255);
  ledState = true;
}

void etteindre(){
  led.setColorRGB(0, 0, 0, 0);
  ledState = false;
}

// Interrupts functions

void green_button_interrupt(){
    green_bascule = !green_bascule;
    if (green_bascule){
        timer = button_timer;
        Serial.println("green");
    }
}

void red_button_interrupt(){
    red_bascule = !red_bascule;
    if (red_bascule){
        timer = button_timer;
        Serial.println("red");
    }
}

// Buttons

void init_buttons(){
    pinMode(red_button, INPUT);
    pinMode(green_button, INPUT);
}

void init_button_interrupts(){
    attachInterrupt(digitalPinToInterrupt(red_button), red_button_interrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(green_button), green_button_interrupt, CHANGE);
}

// Timers

// Timer interruption management
ISR(TIMER1_COMPA_vect){
  if (green_bascule){
    timer -= 1; // Désincrémenter le timer si le bouton est pressé
    Serial.println("Timer -1");
  }
  if (timer == 0) {
    if (ledState){
      etteindre();
      ledState = false;
    } else {
      allumer();
      ledState = true;
    }
  }
}

void initialisation_interruption_tim(long uSecs){
  noInterrupts();
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  OCR1A = ((16e6/256L * uSecs) / (1e6) ) - 1;
  Serial.println(OCR1A);
  
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);
  
  interrupts();
}