// VWR DUAL JOYSTICK MULTI CHANNEL SERIAL TRANSMITTER (HC-12)
// HC-12 SET CHANNEL: AT+C044

#include <SoftwareSerial.h>

SoftwareSerial SSerial(3, 2); // RX, TX

// ANALOG INPUTS
const int joypin1 = A1; //Joystick X1
const int joypin2 = A0; //Joystick Y1

const int joypin3 = A3; //Joystick X2
const int joypin4 = A2; //Joystick Y2

// BUTTON PRESS LIGHT CONTROL
int count = 0;
int buttonState = 0; 
int lastButtonState = 0;       

// MODE SWITCH
int modecount = 0;
int modeState = 0; 
int lastModeState = 0;  

int servo;
int angle;

void setup() {
  
Serial.begin(9600);
SSerial.begin(9600);

pinMode(4, INPUT);
digitalWrite(4, 1);

pinMode(5, INPUT);
digitalWrite(5, 1);
}

void loop(){

  //READ ANALOG INPUTS TO INT
  int val1 = analogRead(joypin1);
  int val2 = analogRead(joypin2);
  int val3 = analogRead(joypin3);
  int val4 = analogRead(joypin4);

  //MAP ANALOG JOYSTICK VALS TO SERVO VALS (0-90-180)
  val1 = map(val1, 0, 1023, 0, 180);
  val2 = map(val2, 0, 1023, 0, 180);
  val3 = map(val3, 0, 1023, 0, 180);
  val4 = map(val4, 0, 1023, 0, 180);

  // BUTTON PRESS COUNTER FOR LIGHTS  
  int buttonState = digitalRead(4);

  if (buttonState != lastButtonState) {
       if (buttonState != 1) {    
          count++;  
          if (count >= 5) {
            count = 0;
          }
        } else {
          // nothing
        }
  }
  lastButtonState = buttonState;

      if (count == 0) {
               move(5, 0);
               Serial.println("lights off");
          } else if (count == 1) {
               move(5, 1);
               Serial.println("lights half");
          } else if (count == 2) {
               move(5, 2);
               Serial.println("lights full");
          } else if (count == 3) {
               move(5, 3);
               Serial.println("lights fuller");
          } else if (count == 4) {
               move(5, 4);
               Serial.println("lights fullest");
       }



// BUTTON PRESS MODE SWITCH
  int modeState = digitalRead(5);

  if (modeState != lastModeState) {
       if (modeState != 1) {    
          modecount++;  
          if (modecount >= 2) {
            modecount = 0;
          }
        } else {
          // nothing
        }
  }
  
  lastModeState = modeState;

      // 0- MOTOR MODE
      // 1- PAN/TILT MODE
    
      if (modecount == 0) {
                // MOTOR MODE
                  Serial.println("motor control");
      } else if (modecount == 1) {
                 // PAN-TILT MODE
                  Serial.println("pan/tilt control");
      }


   move(1, val1); // DRIVE
   move(2, val2); // TURN
   move(3, val3); // PAN
   move(4, val4); // TILT

// Short delay else loop goes bonkers
  delay(10);
}

//MOVE FUNCTION AND SEND TO TX
void move(int servo, int angle) {
       SSerial.write(char(255));
       SSerial.write(char(servo));
       SSerial.write(char(angle));
}

