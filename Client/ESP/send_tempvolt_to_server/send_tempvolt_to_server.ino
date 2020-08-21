#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <WiFiUdp.h>

const char* ssid     = "<ROUTER_NAME>";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "<ROUTER_PASSWORD>";     // The password of the Wi-Fi network

const char* ipaddr = "<PC IP ADDRESS>";     // The ip address of the server


WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back



    char s[32];
    static boolean recv = true;
    char endMarker = '\n';
    char rc;
    int ndx = 0;
    boolean newData = true;

void setup() {

  
 //Serial.begin(115200);         // Start the Serial communication to send messages to the computer
 Serial.begin(9600);
 
 delay(100);
 Serial.println('\n');
 
 WiFi.begin(ssid, password);             // Connect to the network
 Serial.print("Connecting to ");
 Serial.print(ssid); Serial.println(" ...");

 int i = 0;
 while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
   delay(1000);
   Serial.print(++i); Serial.print(' ');
 }

 Serial.println('\n');
 Serial.println("Connection established!");  
 Serial.print("IP address:\t");
 Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer

 Udp.begin(localUdpPort);
 Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
 delay(100);
 
}

void loop() { 
  
       
    while(Serial.available() && newData == true){
      char rc = Serial.read();
      if(recv == true)
      {
        if(rc!= endMarker)
        {
          s[ndx] = rc;
          ndx++;
        }
        else{
          s[ndx] = '\0'; // get rid of the \r
          recv = false;
          ndx = 0;
          newData = false;
        }
        
      }

      if(newData ==false){
        Udp.beginPacket(ipaddr, 4210);
        Udp.write(s);
        Udp.endPacket();
        newData = true;
        recv = true;
      }
  }


 }
