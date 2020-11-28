#include <SoftwareSerial.h>

SoftwareSerial toESP(7, 8); //Rx, Tx pins over software serial (not TX and RX physical pins).

unsigned long previousMillis = 0;
unsigned long currentMillis;
long interval = 600000; //Length of time to delay in ms. Set to 10 minutes.

void setup()
{
  //Serial.begin(19200); //Enable this line to enable debug in serial monitor.
  toESP.begin(9600);
}

void loop()
{

/*
  To avoid using delay(), the time is compared to see if the 
  specified interval has been passed. Once the time passes,
  the Arduino sends the ADC from the temperature sensor
  to the ESP over the soft serial using baud rate initialized
  in setup().
*/
  
  currentMillis = millis();
  if (currentMillis - previousMillis > interval)
  {
    toESP.print(analogRead(2));
    toESP.print('\n');
    //Serial.println(analogRead(2)); //Enable to debug in serial monitor.
    previousMillis = currentMillis;
  }
}
