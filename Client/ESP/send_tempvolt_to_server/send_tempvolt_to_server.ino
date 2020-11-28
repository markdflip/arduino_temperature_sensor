#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266HTTPClient.h>


const char* ssid     = "<ROUTER_NAME>";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "<ROUTER_PASSWORD>";     // The password of the Wi-Fi network

const char* ipaddr = "http://us-central1-arduino-temperature-287404.cloudfunctions.net/post-temperature";     // The ip address of the server




    char s[32];
    static boolean recv = true;
    char endMarker = '\n';
    char rc;
    int ndx = 0;
    boolean newData = true;
    String user_id = "343"; //TODO, dynamically assign user_id after initial call.

void setup() {

  
 Serial.begin(9600);         // Start the Serial communication to send messages to the computer. MUST MATCH BAUD RATE FROM ARDUINO!
 WiFi.begin(ssid, password);             // Connect to the network

 // Wait for the Wi-Fi to connect
 while (WiFi.status() != WL_CONNECTED) { 
   delay(1000);
 }
 
}

void loop() { 



HTTPClient http;

    //The ESP will not enter the loop unless the Arudino sends data over the Serial.
    //This happens on an interval specified within the Arduino code (10 minutes).
    while(Serial.available()>0 &&  newData == true){

 /* Serial gets read in one letter at a time.
  *  Until the endmarker is reached, keep appending to the s character array.
  *  Once the endmarker is reached, newData is set to false to prevent rerun.
  */
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

 /* This block only triggers after new data is read in from Serial.
  *  From there, the GCP function is triggered with the hostname from the top of this ino file.
  *  The GCP function accepts x-www-form-urlencoded format and accepts two values.
  *  
  *  user_id = unique identifier for the arduino.
  *  
  *  user_temp = ADC from the temperature sensor.
  *  
  */
      if(newData ==false){
        http.begin(ipaddr);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
     
        String httpRequestData = "user_id=" + user_id + "&user_temp="  ;
        httpRequestData = httpRequestData + s;
        
        
        int httpResponseCode = http.POST(httpRequestData);
        String payload = http.getString(); 
        
        http.end();
        
        newData = true;
        recv = true;
      }
  }


 }
