
#include <SoftwareSerial.h>

SoftwareSerial fromESP(7,8); //Rx, Tx

void setup()
{
  fromESP.begin(9600);
}

void loop()
{
  fromESP.print(analogRead(2));
  fromESP.print('\n');

  delay(2000);

}
