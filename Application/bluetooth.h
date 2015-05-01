
#include "MOTORS.h"
MOTORS motor;
SENSOR sensee;
SoftwareSerial blueToothSerial(6,7);

class BTconnect
{
 
  
  private: 
            char bufferr[100];
            int readvar();
            char recvchar;
            String mystring ="";
   public:                        
            //The following code is necessary to setup the bluetooth shield ------copy and paste----------------
            void setupBlueToothConnection()
            {
                pinMode(6, INPUT);
                pinMode(7,OUTPUT);
              
                Serial.begin(4800);
                blueToothSerial.begin(9600);// BluetoothBee BaudRate to default baud rate 38400
                blueToothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
                blueToothSerial.print("\r\n+STNA=HC-05\r\n"); //set the bluetooth name as "SeeedBTSlave"
                blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
                blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
                delay(2000); //This delay is required.
                blueToothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable
                Serial.println("The slave bluetooth is inquirable!");
                delay(2000); // This delay is required.
                blueToothSerial.flush();
                
                //lcd.setCursor(0,0);
                //lcd.print("setup complete");
            }
            
            void listening()
            {                   
                    if(blueToothSerial.available() > 0 )
                    {
                        recvchar = blueToothSerial.read();
                        
                        if(recvchar == '1')
                        {
                            Serial.println("forward");
                            //blueToothSerial.write("1");
                            motor.forward();
                            
                        }
                        if(recvchar == '2')
                        {
                           Serial.println("turning left");
                           blueToothSerial.print("2");
                           motor.turnLeft();
                        }
                        if(recvchar == '3')
                        {
                           Serial.println("turning right");
                           blueToothSerial.print("3");
                           motor.turnRight();
                        }
                        if(recvchar == '4')
                        {
                           Serial.println("Revrsing");
                           blueToothSerial.print("4");
                           motor.reverse();
                        }
                        if(recvchar == '0')
                        {
                          Serial.println("stop");
                          motor.freeze();
                        }
                    } 
            }           
           
};
