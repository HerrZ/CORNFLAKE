/*

MAGIC BULLET AMSTERDAM 2018 - OPEN SOURCE PROTOTYPES
-------------------------------------------------------------------------
CORNFLAKE RECEIVER V1.2
-------------------------------------------------------------------------
Hardware used for this sketch:

- Arduino Nano V3
- HC-12 433MHz Serial Tranciever
- Servos or Motor Controller (2x)

------------------------------------------------------------------------    
*/

#include <Servo.h>

Servo servo1;
Servo servo2;

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
const long timeout = 10000;
long counter = 0;

// Debug on/off
boolean debug = false;


void setup() {

    Serial.begin(9600);
    
    // Attach each Servo object to a digital pin
    servo1.attach(9, minPulse, maxPulse);
    servo2.attach(10, minPulse, maxPulse);

    // Set servos to neutral
    servo1.write(90);  
    servo2.write(90);

    if (debug == true){Serial.println("CORNFLAKE RECEIVER!");}
     
    delay(1000); // Wait for other stuff to boot

} 

void loop() {

 // Serial safety - Full stop on lost connection of controller.
     counter = counter + 1;
      if (counter >= timeout){
          if (debug == true){Serial.println("No connection!");}
            servo1.write(90);  
            servo2.write(90);
          }
        

// Start reading sender
  if (Serial.available() > 2) {

       startbyte = Serial.read();
       counter = 0; // Reset connection timeout counter
    
       if (startbyte == 255) {
         for (i=0;i<2;i++){ userInput[i] = Serial.read();}
         servo = userInput[0];
         pos = userInput[1];
         if (pos == 255){ servo = 255;}
         
         switch (servo) {
            case 1: // DRIVE
              if (debug == true){Serial.print("Servo1: ");Serial.println(pos);}
              servo1.write(pos);
               break;
            case 2: // STEERING
              if (debug == true){Serial.print("Servo2: ");Serial.println(pos);}
              servo2.write(pos);
               break;
         }
       }            
   }


} 

