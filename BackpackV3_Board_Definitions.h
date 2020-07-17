//BackpackV3_Board_Definitions.h

/*
*******************************************************************************************************************************
  Easy Build Tracker Programs for Arduino

  Copyright of the author Stuart Robinson - 12/12/17

  

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This is the hardware definitions for the BackpackV3 board, PCB with date 030416.

  To Do:

*******************************************************************************************************************************
*/

/*
Pin connections for ILI9341
---------------------------

VCC to  VCC 3.3V
GND to GND
CS to 10
RESET to 9
D\C to 8
SDI(MOSI) to 11
SCK to 13
LED to VCC 3.3V
SDO(MISO) to 12

Pin connections for Nokia5110
-----------------------------
RST to 9
CE to 10
DC to 8
DIN to 11
CLK to 13
VCC to VCC 3.3V
LIGHT to GND for backlight
GND to GND
*/


#define DISP_CS 10
#define DISP_RESET 9
#define DISP_DC 8