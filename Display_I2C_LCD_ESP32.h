//Display_I2C_LCD2.h
/*
*******************************************************************************************************************************
  Easy Build Tracker Programs for Arduino

  Copyright of the author Stuart Robinson - 2/10/17

  

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
#include <LiquidCrystal_I2C.h>      //http://www.esp32learning.com/wp-content/uploads/2017/12/LiquidCrystal_I2C-master.zip  

LiquidCrystal_I2C disp(0x3F, 20, 4); // set the LCD address to 0x3F for a 16 chars and 2 line display



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
  Wire.begin();
  disp.begin(20,4);                   //initialize the lcd for 20 chars 4 lines, turn on backlight
  disp.backlight();
  Display_Clear();
}  


