#include <QTRSensors.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

#define NUM_SENSORSS            3  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             2  // emitter is controlled by digital pin 2


// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtraa((unsigned char[]) {0, 1, 2, 3, 4, 5},NUM_SENSORSS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorVals[NUM_SENSORSS];


class SENSORS
{
 public:
 
      void sensorSet()
      {
	     for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
		  {
			qtraa.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
		  }
      }
          void readSensors()
	  {
	      unsigned int position = qtraa.readLine(sensorVals);
	  }
          int senseForward()
	  {
	    return sensorVals[1];
	  }
	  
	  int senseLeft()
	  {
	     return sensorVals[0];
	  }
	  
	  int senseRight()
	  {
	     return sensorVals[2];
	  }
};
