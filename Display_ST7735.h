//Display_ST7735.h
/*
**************************************************************************************************

  Easy Build LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 2/10/17

  http://www.LoRaTracker.uk

These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
free from errors.

These routines are for the ST7735 TFT display. 

This program uses the Adafruit_GFX and Adafruit_PCD8544 Arduino Libraries

https://github.com/adafruit/Adafruit-ST7735-Library
https://github.com/adafruit/Adafruit-GFX-Library

ToDo: 

**************************************************************************************************
*/

#define Using_Display_ST7735

#include <Adafruit_GFX.h>    // Core graphics library - https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_ST7735.h> // Hardware-specific library -  https://github.com/adafruit/Adafruit-ST7735-Library

Adafruit_ST7735 disp = Adafruit_ST7735(DISP_CS,  DISP_DC, DISP_RESET);


// Color definitions
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define INITR_BLACKTAB   0x2

const byte contrast = 45;
byte tsize = 1;



void Display_Clear()
{
  disp.fillScreen(BLACK);
  disp.setTextColor(WHITE);
}

void Display_White()
{
  disp.fillScreen(WHITE);
  disp.setTextColor(BLACK);
}


void Display_SetCurPos(byte lcol, byte lrow)
{
  if (tsize == 1)                 // test for the font size currently in use
  {
    lcol = lcol * 6;              // Calculate the column position
    lrow = (lrow * 8);            // Calculate the row position
    //display.setCursor(lcol, lrow);  // done the conversion so position the cursor
  }

  if (tsize == 2)
  {
    lcol = lcol * 12;             // Calculate the column position
    lrow = (lrow * 16);           // Calculate the row position
    //display.setCursor(lcol, lrow);  // done the conversion so position the cursor
  } 
  
  if (tsize == 3)
  {
    lcol = lcol * 18;             // Calculate the column position
    lrow = (lrow * 24);           // Calculate the row position
    //display.setCursor(lcol, lrow);  // done the conversion so position the cursor
  } 
   
  disp.setCursor(lcol, lrow);  // done the conversion so position the cursor
}


void Display_Setup()
{
  disp.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  Display_Clear();
  disp.setTextWrap(false); // Allow text to run off right edge
  disp.fillScreen(BLACK);
  disp.setTextColor(WHITE);
  disp.setRotation(1);
  Display_SetCurPos(0, 0);
  
}


void Display_Update()
{
  //disp.display();						//update screen from buffer
}

void Display_SetContrast(byte lcont)
{

}

void Display_SetTextSize(byte lsize)
{
  tsize = lsize;
  disp.setTextSize(lsize);
}

void Display_Char(char Lchar)
{
disp.write(Lchar);       
}





/******************************************************
Clear and set text routines
*******************************************************/

/*void Display_Clearset1()
{
  Display_Setup();
  disp.setTextSize(1);
  Display_SetCursor(0, 0);
}


void Display_Clearset2()
{
  Display_Setup();
  disp.setTextSize(2);
  Display_SetCursor(0, 0);
}


void Display_Clearset3()
{
  Display_Setup();
  disp.setTextSize(3);
  Display_SetCursor(0, 0);
}
*/




