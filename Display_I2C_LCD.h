//Display_I2C_LCD.h
/*
*******************************************************************************************************************************
  Easy Build LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 2/10/17

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This program creates a standard set of programs to use with a 20x4 LCD displays driven with the low cost PCF8574 I2C driver PCB. 

  To Do:

*******************************************************************************************************************************
*/

#define Using_Display_I2C_LCD

#include <Wire.h>  
#include <LiquidCrystal_I2C.h>                                   //https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/ (version 1.3.4)

LiquidCrystal_I2C disp(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  //Set the LCD I2C address and pins used

byte currentsize = 1;                     //used to keep track of current text size 1 or 2


void Display_Update()
{
 //null routine - nothing to do
}


void Display_Clear()
{
disp.clear();
}


void Display_SetContrast(byte contrast)
{
//null routine - nothing to do 
}


void Display_SetTextSize(byte textsize)
{
//null routine - nothing to do  
}


void Display_Char(char character)
{
  disp.write(character);
}


void Display_SetCurPos(byte col, byte row)
{
  disp.setCursor(col, row);           //done the conversion so position the cursor
}


void Display_Setup()
{
  disp.begin(20,4);                   //initialize the lcd for 20 chars 4 lines, turn on backlight
  disp.backlight();
  Display_Clear();
}  


