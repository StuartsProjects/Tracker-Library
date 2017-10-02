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

This program uses the text only Arduino Library for the I2C SSD1306 OLED;

https://github.com/greiman/SSD1306Ascii

Download the Zip file, UnZip it and read the installation instructions in the 'Documentation.html' file.
 
***********************************************************************************************************************************
*/

#define Using_Display_SD1306_AVR

#include "SSD1306Ascii.h"                            //https://github.com/greiman/SSD1306Ascii
#include "SSD1306AsciiAvrI2c.h"
SSD1306AsciiAvrI2c disp;
#define I2C_ADDRESS 0x3C                             //address will be 0x3C or 0x3D

byte tsize;


void Display_Clear()
{
disp.clear();
}


void Display_SetCurPos(byte lcol, byte lrow)
{
  lcol = lcol * 6;
  disp.setCursor(lcol, lrow);
}


void Display_Setup()
{
  disp.begin(&Adafruit128x64, I2C_ADDRESS);
  disp.setFont(System5x7);
}


void Display_Update()
{
//not required disp.display();
}


void Display_SetContrast(byte lcont)
{
//do nothing
}


void Display_SetTextSize(byte lfont)
{
  if (lfont == 1)                  // font size 1 requested ?
  {
    disp.set1X();
  }
  if (lfont == 2)                 // font size 2 requested ?
  {
    disp.set2X();
  }
}
