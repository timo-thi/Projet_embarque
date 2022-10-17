 #include <ChainableLED.h>
 
#define NUM_LEDS  5
 
ChainableLED leds(7, 8, NUM_LEDS);
 
void setup()
{
  Serial.begin(9600); //Start serial monitor 
  leds.init(); //initaliser leds
  leds.setColorRGB(0, 0, 0, 55); // Set led color (0,R,G,B)
  
}
 
 
void loop()
{
  int value = analogRead(A0);  //Value get the light sensor values
  value = map(value, 0, 800, 0, 10);
 
  printf("%d",value); // Print light sensor values
  delay(100);
}

