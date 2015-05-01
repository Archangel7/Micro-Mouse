#include <QTRSensors.h>
#include <Wire.h>
#include <LiquidCrystal.h>
//#include "LCD.h"
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// This example is designed for use with six QTR-1A sensors or the first six sensors of a
// QTR-8A module.  These reflectance sensors should be connected to analog inputs 0 to 5.
// The QTR-8A's emitter control pin (LEDON) can optionally be connected to digital pin 2, 
// or you can leave it disconnected and change the EMITTER_PIN #define below from 2 to 
// QTR_NO_EMITTER_PIN.

// The setup phase of this example calibrates the sensor for ten seconds and turns on
// the LED built in to the Arduino on pin 13 while calibration is going on.
// During this phase, you should expose each reflectance sensor to the lightest and
// darkest readings they will encounter.
// For example, if you are making a line follower, you should slide the sensors across the
// line during the calibration phase so that each sensor can get a reading of how dark the
// line is and how light the ground is.  Improper calibration will result in poor readings.
// If you want to skip the calibration phase, you can get the raw sensor readings
// (analog voltage readings from 0 to 1023) by calling qtra.read(sensorValues) instead of
// qtra.readLine(sensorValues).

// The main loop of the example reads the calibrated sensor values and uses them to
// estimate the position of a line.  You can test this by taping a piece of 3/4" black
// electrical tape to a piece of white paper and sliding the sensor across it.  It
// prints the sensor values to the serial monitor as numbers from 0 (maximum reflectance) 
// to 1000 (minimum reflectance) followed by the estimated location of the line as a number
// from 0 to 5000.  1000 means the line is directly under sensor 1, 2000 means directly
// under sensor 2, etc.  0 means the line is directly under sensor 0 or was last seen by
// sensor 0 before being lost.  5000 means the line is directly under sensor 5 or was
// last seen by sensor 5 before being lost.

#define NUM_SENSORS             3  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             2  // emitter is controlled by digital pin 2

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {0, 1, 2, 3, 4, 5}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

#define FRONT    sensorValues[1]
#define LEFT     sensorValues[0]
#define RIGHT    sensorValues[2]

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

void setup() {
    Serial.begin(9600);           // set up Serial library at 9600 bps
 // Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  // read raw sensor values
  qtra.read(sensorValues);
  
  // print the sensor values as numbers from 0 to 1023, where 0 means maximum reflectance and
  // 1023 means minimum reflectance
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();
  
  delay(250);
  
  /*for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }*/
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

}

void loop() {
    // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
    //qtra.read(sensorValues); //instead of unsigned int position = qtra.readLine(sensorValues);
  unsigned int position = qtra.readLine(sensorValues);
  
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
 /*for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }*/
  
  uint8_t i;
 

 // if all three sensors see very low reflectance, take some appropriate action for this 
  // situation.
  if (LEFT < 750 && FRONT < 750 && RIGHT < 750)
  {
    rightMotor->run(BRAKE);
    leftMotor->run(BRAKE);
    // do something.  Maybe this means we're at the edge of a course or about to fall off 
    // a table, in which case, we might want to stop moving, back up, and turn around.
    return;
  }
 
  // compute our "error" from the line position.  We will make it so that the error is zero 
  // when the middle sensor is over the line, because this is our goal.  Error will range from
  // -1000 to +1000.  If we have sensor 0 on the left and sensor 2 on the right,  a reading of 
  // -1000 means that we see the line on the left and a reading of +1000 means we see the 
  // line on the right.
  int error = position - 1000;
 
  int leftMotorSpeed = 100;
  int rightMotorSpeed = 100;
  if (error < -500) { // the line is on the left
    rightMotor->run(FORWARD);
    leftMotor->run(FORWARD);  // turn left
  }
  else  // the line is on the right
    rightMotorSpeed = 0;  // turn right
// set motor speeds using the two motor speed variables above 
}  


    
  