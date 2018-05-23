//Display_SD1306_AVR.h
/*
***********************************************************************************************************************************

Easy Build LoRaTracker Programs for Arduino

Copyright of the author Stuart Robinson - 2/10/2017

http://www.LoRaTracker.uk

These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
free from errors.

This program uses the text only Arduino Library for the I2C SD1306 OLED;

https://github.com/greiman/SSD1306Ascii

Download the Zip file, UnZip it and read the installation instructions in the 'Documentation.html' file.

This program is for a directly connected SD1306 OLED, you must set the global constant 'I2C_Address' to the I2C address of 
the SD1306 display before use. 
 
***********************************************************************************************************************************
*/

#define Using_Display_SD1306_Adafruit
#include <Wire.h>
#include <Adafruit_GFX.h>                            //https://github.com/adafruit/Adafruit-GFX-Library 
#include <Adafruit_SSD1306.h>                        //https://github.com/adafruit/Adafruit_SSD1306
#define OLED_RESET 4
Adafruit_SSD1306 disp(OLED_RESET);

byte tsize;


void Display_Clear()
{
disp.clearDisplay();
}


void Display_SetCurPos(byte lcol, byte lrow)
{
  
  if (tsize == 1)
  {
  lcol = lcol * 6;
  lrow = lrow * 8;
  }
  
  if (tsize == 2)
  {
  lcol = lcol * 12;
  lrow = lrow * 16;
  }
  
  disp.setCursor(lcol, lrow);
}


void Display_Setup()
{
  Wire.begin();
  disp.begin(SSD1306_SWITCHCAPVCC, I2C_Address);  // initialize with the I2C addr, normally 0x3C 
  disp.setTextColor(WHITE);
}



void Display_Update()
{
disp.display();
}


void Display_SetContrast(byte lcont)
{
//do nothing
}


void Display_SetTextSize(byte lfont)
{
  if (lfont == 1)                  // font size 1 requested ?
  {
    tsize = 1;
	disp.setTextSize(1);
  }
  if (lfont == 2)                 // font size 2 requested ?
  {
    tsize = 2;
	disp.setTextSize(2);
  }
}
