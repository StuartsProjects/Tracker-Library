//Display_BackPack.h
/*
**************************************************************************************************

  Tracker Programs for Arduino

  Copyright of the author Stuart Robinson - 2/10/17

  

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without
  the explicit permission of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the
  intended purpose and free from errors.

  This is a set of Library routines for the LoRa Tracker Display Backpack.
  
**************************************************************************************************


*/

const byte DisplayDelay = 2;                //delay to allow display backpack time to complete command
const byte ClearDelay = 5;                  //delay to allow display backpack time to clear screen
const byte endcommand = 13;                 //this character value ends a text write. This may be 0 for some digole display modules

#include <SendOnlySoftwareSerial.h>         //https://github.com/disq/i2c-gps-nav/blob/master/I2C_GPS_NAV/SendOnlySoftwareSerial.h
SendOnlySoftwareSerial disp (DISPLAYTX);


void Display_SetContrast(byte lcont)
{
  //Sets the display contrast
  disp.print(F("CT"));                      //print text
  disp.write(lcont);                        //print data
  delay(DisplayDelay);
}

void Display_SetCurPos(byte lcol, byte lrow)
{
  disp.print(F("TP"));                      //print text
  disp.write(char(lcol));                   //print data
  disp.write(char(lrow));                   //print data
  delay(DisplayDelay);
}

void Display_Clear()
{
   disp.print(F("CL"));                     //print text
   delay(ClearDelay);
}


void Display_SetTextSize(byte lsize)
{
  disp.print(F("SF"));
  
  if (lsize == 1)
  {
  disp.write(6);
  }

  if (lsize == 2)
  {
  disp.write(10);
  }
  
  delay(DisplayDelay);
}


void Display_Update()
{
  //nothing to do
}


void Display_Setup()
{
  disp.begin(DISPLAYBAUD);
  Display_SetContrast(contrast5110);
}
