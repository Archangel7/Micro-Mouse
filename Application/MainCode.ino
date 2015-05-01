#include <SoftwareSerial.h>
#include <Adafruit_CC3000.h>
#include <Adafruit_CC3000_Server.h>
#include <ccspi.h>
#include <SPI.h>
#include <Wire.h>
#include <QTRSensors.h>
#include <Adafruit_MotorShield.h>
#include <LiquidCrystal.h>
#include "Arduino.h"
#include "sense.h"
#include "LCD.h"
//#include "MOTORS.h"
#include "SoftwareSerial.h"

SENSORS sensor;
MOTORS motors;
LCD lc;
BTconnect bt;

void setup()
{
    Serial.begin(4800);
   // lc.initilize();
    bt.setupBlueToothConnection();
    motors.motorSet();
}
int button;
void loop()
{
   bt.listening();
}
