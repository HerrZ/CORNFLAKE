/*

MAGIC BULLET AMSTERDAM 2018 - OPEN SOURCE PROTOTYPES
-------------------------------------------------------------------------
CORNFLAKE RECEIVER V1.2 With Leds
-------------------------------------------------------------------------
Hardware used for this sketch:

- Arduino Nano V3
- HC-12 433MHz Serial Tranciever
- Servos or Motor Controller (2x)
- APA102 Leds (Adafruit Dotstar)
- 10A BEC (input 12V/ Output 5V)
- 5A LiPo battery 12V

------------------------------------------------------------------------    
*/
#include <Adafruit_DotStar.h>
#define NUMPIXELS 21 //15 front - 6 rear
#define DATAPIN    52
#define CLOCKPIN   53
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

#include <Servo.h>

Servo servo1;
Servo servo2;

long time=0; // timer

int pulseLed = 800;
int RGBwarning = 10;
int lightState = 0;

// Common servo setup values
int minPulse = 1000;    // minimum servo position, us (microseconds)
int maxPulse = 2000;    // maximum servo position, us


// HC12 SERIAL INPUT SERVO/VALUE
int userInput[3];    // raw input from serial buffer, 3 bytes
int startbyte;       // start byte, begin reading input
int servo;           // which servo to pulse?
int pos;             // servo angle 0-180
int i;               // iterator

// Serial timeout on lost connection
const long timeout = 1000;
long counter = 0;

// Debug on/off
boolean debug = false;

// COLOR SETS

uint32_t colorwhite = 0xFFFFFF;
uint32_t colorred = 0xFF0000;
uint32_t colorblue = 0x0000FF;
uint32_t coloryellow = 0xFFFF00;
uint32_t colorgreen = 0x00dc1f;
uint32_t coloroff = 0x000000;

void setup() {

    Serial.begin(9600);
    Serial1.begin(9600);
    
    // Attach each Servo object to a digital pin
    servo1.attach(40, minPulse, maxPulse);
    servo2.attach(42, minPulse, maxPulse);

    // Set servos to neutral
    servo1.write(90);  
    servo2.write(90);

    if (debug == true){Serial.println("CORNFLAKE RECEIVER!");}

    strip.begin();
    strip.show();

    // Wait for other stuff to boot

            strip.setPixelColor(0, colorgreen);
            strip.setPixelColor(14, colorgreen);
             strip.show();
            delay(100); 
            strip.setPixelColor(1, colorgreen);
            strip.setPixelColor(13, colorgreen);
             strip.show();
            delay(100); 
            strip.setPixelColor(2, colorgreen);
            strip.setPixelColor(12, colorgreen);
             strip.show();
            delay(100); 
            strip.setPixelColor(3, colorgreen);
            strip.setPixelColor(11, colorgreen);
             strip.show();
            delay(100); 
            strip.setPixelColor(4, colorgreen);
            strip.setPixelColor(10, colorgreen);
             strip.show();
            delay(100); 
            strip.setPixelColor(5, colorgreen);
            strip.setPixelColor(9, colorgreen);
             strip.show();
            delay(100); 
            strip.setPixelColor(6, colorgreen);
            strip.setPixelColor(8, colorgreen);
             strip.show();
            delay(100); 
            strip.setPixelColor(7, colorgreen);
             strip.show();
            
     if (debug == true){Serial.println("READY!");}

} 

void loop() {

// Led pulsing
  time = millis();
  RGBwarning = 128+127*cos(2*PI/pulseLed*time);
  

 // Serial safety - Full stop on lost connection of controller.
     counter = counter + 1;
     
      if (counter >= timeout){
          if (debug == true){Serial.println("No connection!");}
            servo1.write(90);  
            servo2.write(90);

              strip.setPixelColor(0, 0,0,RGBwarning);
              strip.setPixelColor(1, 0,0,RGBwarning);
              strip.setPixelColor(2, 0,0,RGBwarning);
              strip.setPixelColor(3, 0,0,RGBwarning);
              strip.setPixelColor(4, 0,0,RGBwarning);
              strip.setPixelColor(5, 0,0,RGBwarning);
              strip.setPixelColor(6, 0,0,RGBwarning);
              strip.setPixelColor(7, 0,0,RGBwarning);
              strip.setPixelColor(8, 0,0,RGBwarning);
              strip.setPixelColor(9, 0,0,RGBwarning);
              strip.setPixelColor(10, 0,0,RGBwarning);
              strip.setPixelColor(11, 0,0,RGBwarning);
              strip.setPixelColor(12, 0,0,RGBwarning);
              strip.setPixelColor(13, 0,0,RGBwarning);
              strip.setPixelColor(14, 0,0,RGBwarning);
              strip.setPixelColor(15, 0,0,RGBwarning);
                      strip.setPixelColor(16, 0,0,RGBwarning);
                      strip.setPixelColor(17, 0,0,RGBwarning);
                      strip.setPixelColor(18, 0,0,RGBwarning);
                      strip.setPixelColor(19, 0,0,RGBwarning);
                      strip.setPixelColor(20, 0,0,RGBwarning);
                    
          }
        

// Start reading sender
  if (Serial1.available() > 2) {

       startbyte = Serial1.read();
       counter = 0; // Reset connection timeout counter
    
       if (startbyte == 255) {
         for (i=0;i<2;i++){ userInput[i] = Serial1.read();}
         servo = userInput[0];
         pos = userInput[1];
         if (pos == 255){ servo = 255;}

       if (lightState == 0){
            strip.setPixelColor(0, coloroff);
            strip.setPixelColor(1, coloroff);
            strip.setPixelColor(2, coloroff);
            strip.setPixelColor(3, coloroff);
            strip.setPixelColor(4, coloroff);
            strip.setPixelColor(5, coloroff);
            strip.setPixelColor(6, coloroff);
            strip.setPixelColor(7, coloroff);
            strip.setPixelColor(8, coloroff);
            strip.setPixelColor(9, coloroff);
            strip.setPixelColor(10, coloroff);
            strip.setPixelColor(11, coloroff);
            strip.setPixelColor(12, coloroff);
            strip.setPixelColor(13, coloroff);
            strip.setPixelColor(14, coloroff);
            
            } else if (lightState == 1){
            strip.setPixelColor(0, colorwhite);
            strip.setPixelColor(1, colorwhite);
            strip.setPixelColor(2, coloroff);
            strip.setPixelColor(3, coloroff);
            strip.setPixelColor(4, coloroff);
            strip.setPixelColor(5, coloroff);
            strip.setPixelColor(6, coloroff);
            strip.setPixelColor(7, coloroff);
            strip.setPixelColor(8, coloroff);
            strip.setPixelColor(9, coloroff);
            strip.setPixelColor(10, coloroff);
            strip.setPixelColor(11, coloroff);
            strip.setPixelColor(12, coloroff);
            strip.setPixelColor(13, colorwhite);
            strip.setPixelColor(14, colorwhite);
            
            } else if (lightState == 2){
            strip.setPixelColor(0, colorwhite);
            strip.setPixelColor(1, colorwhite);
            strip.setPixelColor(2, colorwhite);
            strip.setPixelColor(3, coloroff);
            strip.setPixelColor(4, coloroff);
            strip.setPixelColor(5, coloroff);
            strip.setPixelColor(6, coloroff);
            strip.setPixelColor(7, coloroff);
            strip.setPixelColor(8, coloroff);
            strip.setPixelColor(9, coloroff);
            strip.setPixelColor(10, coloroff);
            strip.setPixelColor(11, coloroff);
            strip.setPixelColor(12, colorwhite);
            strip.setPixelColor(13, colorwhite);
            strip.setPixelColor(14, colorwhite);
            
            } else if (lightState == 3){
            strip.setPixelColor(0, colorwhite);
            strip.setPixelColor(1, colorwhite);
            strip.setPixelColor(2, colorwhite);
            strip.setPixelColor(3, colorwhite);
            strip.setPixelColor(4, coloroff);
            strip.setPixelColor(5, coloroff);
            strip.setPixelColor(6, coloroff);
            strip.setPixelColor(7, coloroff);
            strip.setPixelColor(8, coloroff);
            strip.setPixelColor(9, coloroff);
            strip.setPixelColor(10, coloroff);
            strip.setPixelColor(11, colorwhite);
            strip.setPixelColor(12, colorwhite);
            strip.setPixelColor(13, colorwhite);
            strip.setPixelColor(14, colorwhite);
            
            } else if (lightState == 4){
            strip.setPixelColor(0, colorwhite);
            strip.setPixelColor(1, colorwhite);
            strip.setPixelColor(2, colorwhite);
            strip.setPixelColor(3, colorwhite);
            strip.setPixelColor(4, colorwhite);
            strip.setPixelColor(5, colorwhite);
            strip.setPixelColor(6, coloroff);
            strip.setPixelColor(7, coloroff);
            strip.setPixelColor(8, coloroff);
            strip.setPixelColor(9, colorwhite);
            strip.setPixelColor(10, colorwhite);
            strip.setPixelColor(11, colorwhite);
            strip.setPixelColor(12, colorwhite);
            strip.setPixelColor(13, colorwhite);
            strip.setPixelColor(14, colorwhite);
            }
         
         switch (servo) {
            case 1: // DRIVE
              if (debug == true){Serial.print("Servo1: ");Serial.println(pos);}
              servo1.write(pos);
                if (pos > 92){ 
                      strip.setPixelColor(15, colorred);
                      strip.setPixelColor(16, coloroff);
                      strip.setPixelColor(17, coloroff);
                      strip.setPixelColor(18, coloroff);
                      strip.setPixelColor(19, coloroff);
                      strip.setPixelColor(20, colorred);
                    } else if (pos < 80){
                      strip.setPixelColor(15, colorred);
                      strip.setPixelColor(16, colorwhite);
                      strip.setPixelColor(17, coloroff);
                      strip.setPixelColor(18, coloroff);
                      strip.setPixelColor(19, colorwhite);
                      strip.setPixelColor(20, colorred);
                    } else {
                      strip.setPixelColor(15, colorred);
                      strip.setPixelColor(16, colorred);
                      strip.setPixelColor(17, coloroff);
                      strip.setPixelColor(18, coloroff);
                      strip.setPixelColor(19, colorred);
                      strip.setPixelColor(20, colorred);
                    }
                  
               break;
            case 2: // STEERING
              if (debug == true){Serial.print("Servo2: ");Serial.println(pos);}
              pos = map(pos, 0, 180, 180, 0);
              servo2.write(pos);
               break;

            case 5: // LIGHTS
                if (pos == 0) {
                   if (lightState != 0) {
                       lightState = 0; 
                    } 
                    
                 } else if (pos == 1) {
                   if (lightState != 1) {
                       lightState = 1; 
                    }
                    
                 } else if (pos == 2){
                  if (lightState != 2) {
                      lightState = 2;
                    }
                 
                 } else if (pos == 3) {
                  if (lightState != 3) {
                      lightState = 3;
                    }
                    
                 } else if (pos == 4) {
                   if (lightState != 4) {
                       lightState = 4;
                    }
                 }
         
                break; 
         
         }
        }            
       }
       strip.show();
} 




