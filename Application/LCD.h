// include the library code:
#include <LiquidCrystal.h>
#include "bluetooth.h"
/*-----( Declare Constants )-----*/
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

BTconnect bt2;

int lcd_key       = 0;
int adc_key_in    = 0;
int adc_key_prev  = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

class LCD
{

public:    
             void initilize()
             {
               lcd.begin(16, 2);
             }
             
             void clearScreen()
             {
              lcd.clear(); 
             }
           
                  int read_LCD_buttons()
                  {
                     adc_key_in = analogRead(0);      // read the value from the sensor 
                     // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
                     // we add approx 50 to those values and check to see if we are close
                     if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
                     // For V1.1 us this threshold
                     if (adc_key_in < 50)   return btnRIGHT;  
                     if (adc_key_in < 250)  return btnUP; 
                     if (adc_key_in < 450)  return btnDOWN; 
                     if (adc_key_in < 650)  return btnLEFT; 
                     if (adc_key_in < 850)  return btnSELECT;  
                
                  // return btnNONE;  // when all others fail, return this...
                  }
                  
                
    void Decide(int lcd_key)
    {
         lcd.setCursor(0,2);
    	 switch (lcd_key)               // depending on which button was pushed, we perform an action
    	 {
        	  case btnRIGHT:
        	  {
                      lcd.setCursor(0,2);
                      lcd.print("                ");
                      lcd.setCursor(0,2);
        	      lcd.print("MAZE MODE");
                      
        	      break;
        	  }
        	  case btnLEFT:
        	  {
                      lcd.setCursor(0,2);
                      lcd.print("               ");
                      lcd.setCursor(0,2);
         	      lcd.print("WIRELESS MODE");
                       
                       //listen for bluetooth connections
                      //bt2.listening();
        	      break;
        	  }
        	  
    	 }
    }
		void display_intro()
		{
		  // set up the LCD's number of columns and rows: 
		  lcd.begin(16,2);
		  lcd.setCursor(0,0);
		  lcd.print("POWERING UP");
		  delay(1000);
                  lcd.setCursor(0,0);
                  lcd.print("");
                  delay(1000);
		  lcd.setCursor(0,0);
                  lcd.print("HOLTON MOUSE");
                  delay(2000);
                  lcd.setCursor(0,0);
                  lcd.print("");
                  delay(1000);
                  lcd.setCursor(0,0);
                  lcd.print("SELECT A MODE");
		}
		
		void printf(char *display_info)
		{
                   lcd.setCursor(0,0);
		   lcd.print(display_info);
                   return;
                   //lcd.setCursor(0,2);
                   //lcd.print(millis()/1000);
		}
};

		
