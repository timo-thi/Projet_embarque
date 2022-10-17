 #include <Arduino.h>

 
void setup()
{
  Serial.begin(9600); //Start serial monitor 
}
 
 
void loop()
{
  int value = analogRead(A0);  //Value get the light sensor values
 
  printf("light: %d",value); // Print light sensor values
  delay(100);
}


void LightSensor(){
  int lux = analogRead(A0); //
  return lux
}
