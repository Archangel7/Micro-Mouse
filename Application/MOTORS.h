#include <QTRSensors.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

class MOTORS
{
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

public:

      void motorSet()
	  {
	     Serial.begin(9600);           // set up Serial library at 9600 bps
		 // Serial.println("Adafruit Motorshield v2 - DC Motor test!");

		  AFMS.begin();  // create with the default frequency 1.6KHz
		  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
	  }
	  
	  void forward()
	  {
	        myMotor->setSpeed(100);
		myMotor->run(FORWARD);
		//myMotor->run(RELEASE);
		
		myOtherMotor->setSpeed(100);
		myOtherMotor->run(FORWARD);
		//myOtherMotor->run(RELEASE);
	  }
	  
	  void freeze()
	  {
                myMotor->setSpeed(0);
                myMotor->run(FORWARD);
                myOtherMotor->setSpeed(0);
                myOtherMotor->run(FORWARD);
                
		//myMotor->run(BRAKE);
		//myOtherMotor->run(BRAKE);
	  }
	  
	  void reverse()
	  {
		 myMotor->setSpeed(100);
		 myMotor->run(BACKWARD);
				 
		 myOtherMotor->setSpeed(100);
		 myOtherMotor->run(BACKWARD);
	
	  }
	  
	  void turnRight()
	  {
	        myMotor->setSpeed(100);
		myMotor->run(FORWARD);
	  }
	  
	  void turnLeft()
	  {
	         myOtherMotor->setSpeed(100);
		 myOtherMotor->run(FORWARD);
	  }
          void turn360()
          {
                myMotor->setSpeed(100);
		myMotor->run(FORWARD);
                myMotor->setSpeed(100);
		myMotor->run(BACKWARD);
                myMotor->setSpeed(100);
		myMotor->run(FORWARD);
                myMotor->setSpeed(100);
		myMotor->run(BACKWARD);
          }
          void turn180()
          {
                myMotor->setSpeed(100);
		myMotor->run(FORWARD);
                myMotor->setSpeed(100);
		myMotor->run(BACKWARD); 
          }
 };
