//Display_5110.h
/*
*******************************************************************************************************************************
  Easy Build Tracker Programs for Arduino

  Copyright of the author Stuart Robinson - 2/10/17

  

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This program creates a standard set of functions to use with the Nokia 5110 display. There are similar programs for other
  displays. This allows for different displays to be used without needing chnages to the main programs.
  
  This program is for a directly connected Nokia %110 display.

  To Do:

*******************************************************************************************************************************
*/

#define Using_Display_5110

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 disp = Adafruit_PCD8544(DISP_DC, DISP_CS, DISP_RESET);

byte currentsize = 1;               //used to keep track of current text size 1 or 2


void Display_Update()
{
  //update screen from buffer
  disp.display();
}


void Display_Clear()
{
  disp.clearDisplay();
  Display_Update();
}


void Display_SetContrast(byte contrast)
{
  disp.setContrast(contrast5110);
}


void Display_SetTextSize(byte textsize)
{
  currentsize = textsize;
  disp.setTextSize(textsize);
}


void Display_Char(char character)
{
  disp.write(character);
}


void Display_SetCurPos(byte col, byte row)
{
  if (currentsize == 1)               //test for the font size currently in use
  {
    col = col * 6;                    //Calculate the column position
    row = (row * 8);                  //Calculate the row position
  }

  if (currentsize == 2)
  {
    col = col * 12;                   //Calculate the column position
    row = (row * 16);                 //Calculate the row position
  }

  disp.setCursor(col, row);           //done the conversion so position the cursor
}


void Display_Setup()
{
  disp.begin();                       //Start the display
  disp.setContrast(contrast5110);     //Set default contrast, this is a compromise, most LCDs should have a visible display
  disp.setTextSize(1);                //Set text size, equivalent to font 6 on Digole
  disp.setTextColor(BLACK);
  disp.clearDisplay();
  disp.display();
}


