#include <SoftwareSerial.h>

SoftwareSerial toESP(7, 8); //Rx, Tx

unsigned long previousMillis = 0;
unsigned long currentMillis;
long interval = 15000; //Length of time to delay in ms

void setup()
{
  toESP.begin(9600);
}

void loop()
{
  currentMillis = millis();
  if (currentMillis - previousMillis > interval)
  {
    toESP.print(analogRead(2));
    toESP.print('\n');
    previousMillis = currentMillis;
  }
}
