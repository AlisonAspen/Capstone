#include <Adafruit_NeoPixel.h>


#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>
#include "arduino_secrets.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif

//mqtt variables:

#define BROKER "broker.mqttdashboard.com"
#define MQTT_USER "ally-arduino"
#define MQTT_PASS "mkr5422"
//const char[] broker = "broker.m qttdashboard.com";
int port = 1883;

String topic = "/topic1";

//wifi setup variables
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;
WiFiClient wifiClient;

MqttClient mqttClient(wifiClient);

//led strip
const int lightPin = 6;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, lightPin, NEO_GRB + NEO_KHZ800);

void setup(){
  //setting up led strip
  strip.begin();
  strip.setBrightness(0);
  strip.show();
  //wifi connection
  //tutorial from https://www.arduino.cc/en/Guide/MKRWiFi1010/connecting-to-wifi-network
  //"Connecting MKR WiFi 1010 to a Network" by Karl Soderby
  Serial.begin(9600);
  while(!Serial); //ensures that wifi doesn't run unless serial port is open

  while(status != WL_CONNECTED) {
     Serial.print("Attempting to connect to network: ");
     Serial.println(ssid);

     status = WiFi.begin(ssid, pass);
     //wait 10 secs for connection
     delay(10000);
  } //end while

  Serial.println("You're connected to the network: ");
  connectSuccess();
  Serial.println("---------------------------------");
  printData();
  Serial.println("---------------------------------");
  //end of code from wifi tutorial

  Serial.print("Attempting connection to broker: ");
  Serial.println(BROKER);
  mqttClient.setUsernamePassword(MQTT_USER, MQTT_PASS);

  if(!mqttClient.connect(BROKER, port)){
      Serial.print("MQTT connection failed! Error code: ");
      Serial.println(mqttClient.connectError());
        while(1);
    } 
  Serial.println("MQTT Connected!");
  Serial.print("subscribing to topic: ");
  Serial.println(topic);
  mqttClient.subscribe(topic);
  
}

void loop(){
  //wifi setup
  //checks network connection every 10 seconds
  //based on above tutorial
  /*
  delay(10000);
  printData(); //will print data regarding WiFi connection (if established)
  Serial.println("---------------------------------");
  */
  //hardPress();
  int messageSize = mqttClient.parseMessage();
  if(messageSize) {
//    message received
    Serial.print("Message Received with topic:  ");
    Serial.println(mqttClient.messageTopic());
    messageReceived(); 
    //messageReceived();
    while(mqttClient.available()) {
          //byte message = mqttClient.read();
          byte payload = mqttClient.read();
          //String msgString;
          //Serial.print(msgString);
          //messageReceived();
          
          /*
          if(== "hard") {
              hardPress(); 
           }
          if(message == "medium") {
              mediumPress();  
          }
          if(message == "soft") {
              softPress();
          } */
         
      }
      Serial.println();
   }
  
} //end loop

void messageReceived() {
  //blinks light when message is received
  strip.setBrightness(175);
  /*
  for(int i = 0; i < 12; i++){
    strip.setPixelColor(i, 0, 0, 255, 127);
  }
  strip.show();
  delay(2000);
  strip.setBrightness(0);
  strip.show();
  delay(500); */



      for(int i = 0; i < 12; i++) {
            strip.setPixelColor(i, 255, 0, 255);
            strip.show(); 
            delay(100);
       }    
  
  delay(500);
  strip.setBrightness(0);
  strip.show();
}

void hardPress() {
   strip.setBrightness(200);
   for(int i = 0; i < 12; i++){
    strip.setPixelColor(i, 255, 0, 0);
    strip.show();
  }
  delay(5000);
  strip.setBrightness(0);
  strip.show();
}

void mediumPress() {
   strip.setBrightness(200);
   for(int i = 0; i < 12; i++){
    strip.setPixelColor(i, 0, 255, 0);
    strip.show();
  }
  delay(5000);
  strip.setBrightness(0);
  strip.show();
}

void softPress() {
   strip.setBrightness(200);
   for(int i = 0; i < 12; i++){
    strip.setPixelColor(i, 0, 0, 255);
    strip.show();
  }
  delay(5000);
  strip.setBrightness(0);
  strip.show();
}

void connectSuccess() {
    //strip.setBrightness(175);
     for(int i = 0; i < 3; i++) {
          for(int j = 0; j < 12; j++) {
                strip.setBrightness(175);
                strip.setPixelColor(i, 255, 255, 255);
                strip.show();
            }
            delay(500);
            strip.setBrightness(0);
            strip.show();
            delay(500);
           // strip.setBrightness(175);
      } 
}

//prints data about WiFi connection
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
