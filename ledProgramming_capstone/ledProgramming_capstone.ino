/* How to use a flex sensor/resistro - Arduino Tutorial
   Fade an LED with a flex sensor
   More info: http://www.ardumotive.com/how-to-use-a-flex-sensor-en.html
   Dev: Michalis Vasilakis // Date: 9/7/2015 // www.ardumotive.com  */
#include <Adafruit_NeoPixel.h>


#ifdef __AVR__
  #include <avr/power.h>
#endif

//Constants:
const int lightPin = 6;

//Variables:
int value; //save analog value
int brightVal = 10;



Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, lightPin, NEO_GRB + NEO_KHZ800);

void setup(){
       

  //neopixel setup
  
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
  


  
}

void loop(){
  
  //kiwiSetup();
  
 
  
} //end loop



//led programming


void blinkingBlue() {
  //blue light
  strip.setBrightness(175);
  for(int i = 0; i < 12; i++){
    strip.setPixelColor(i, 0, 0, 255, 127);
  }
  strip.show();
  delay(2000);
  strip.setBrightness(0);
  strip.show();
  delay(500);
  
  
}


void flexLight(int flexVal) {
    for(int i = 0; i < 12; i++){
        //make cases based on how hard item is being squeezed
        
    }
}

void gainBrightness() {
    
     for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 255; j+=5){
              strip.setBrightness(j);
              strip.setPixelColor(i, 100, 10, 20);
              strip.show();
              delay(500);
          }
      }
    
      
      for(int j = 0; j < 100; j+=5){
              strip.setBrightness(j);
              for(int i =  0; i < 12; i++){
                  strip.setPixelColor(i, 255, 10, 50);
                  strip.show();
               }
             delay(200);
       }
}

void kiwiSetup() {
    //circle around LEDs
    strip.setBrightness(12);
    for(int i = 0; i < 12; i++) {
        strip.setPixelColor(i, 255, 255, 255); //white??
        strip.show();
        delay(200);
      } 
      
 }

 void wifiConnected() {
  strip.show();
  delay(200);
  strip.setBrightness(0);
  strip.show();
  delay(500);
  
  strip.setBrightness(12);
  for(int i = 0; i < 13; i++){
    strip.setPixelColor(i, 255, 255, 255);
    
  }
  
 }

//adafruit examples
//rainbow on neopixel
void rainbow(uint8_t wait) {
  strip.setBrightness(20);
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
 
  strip.setBrightness(0);
  strip.show(); // Initialize all pixels to 'off'
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
} 
