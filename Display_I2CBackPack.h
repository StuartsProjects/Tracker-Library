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

  This is a set of Library routines for the LoRa Tracker Display Backpack connected via an I2C interface.
  You must set the global constant 'Display_Address' to the I2C address of the backpack before use.

  
**************************************************************************************************


*/

#include "I2CDisplay.h"                        //include library file from Tracker library
I2CDisplay disp(Display_Address);              //create the display class


void Display_SetContrast(byte lcont)
{
//left blank for compatibility
}

void Display_SetCurPos(byte lcol, byte lrow)
{
 disp.SetCursorPosition(lcol,lrow);
}


void Display_Clear()
{
 disp.Clear();
}


void Display_SetTextSize(byte lsize)
{
  disp.SetTextScale(lsize);
}


void Display_SetRotation(byte lrotation)
{
  disp.SetDisplayRotation(lrotation);
}


void Display_Update()
{
  disp.Update();
}


void Display_Setup()
{
  disp.SetwaitReady(1);			               //Wait for display to finish update before continuing						
  disp.SetTextColour(White);                   //ignored on non-colour screens
  disp.SetBackgroundColour(Black);             //ignored on non-colour screens 
}


void Display_Char(char character)
{
  disp.write(character);
}

