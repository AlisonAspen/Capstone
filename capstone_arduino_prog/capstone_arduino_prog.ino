#include <Adafruit_NeoPixel.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif

//wifi setup variables
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;

void setup(){
  //wifi connection
  //tutorial from https://www.arduino.cc/en/Guide/MKRWiFi1010/connecting-to-wifi-network
  //"Connecting MKR WiFi 1010 to a Network" by Karl Soderby
  Serial.begin(9600);
  while(!Serial); //ensures that wifi doesn't run unless serial port is open

  while(status != WL_CONNECTED) {
     Serial.print("Attempting to connect to network");
     Serial.println(ssid);

     status = WiFi.begin(ssid, pass);
     //wait 10 secs for connection
     delay(10000);
  } //end while

  Serial.println("You're connected to the network");
  Serial.println("---------------------------------");
  printData();
  Serial.println("---------------------------------");
  //end of code from wifi tutorial
  
}

void loop(){
  //wifi setup
  //checks network connection every 10 seconds
  //based on above tutorial
  delay(10000);
  printData(); //will print data regarding WiFi connection (if established)
  Serial.println("---------------------------------");
  
} //end loop

void printData() {
  Serial.println("Board Information:");
  //print board IP
  IPAddress ip = WiFi.localIP();
  Serial.println("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.println("Network Information");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  //print signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength: ");
  Serial.println(rssi);
} //end printData
