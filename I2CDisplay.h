/*
******************************************************************************************************

  LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 13/12/17

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without
  the explicit permission of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the
  intended purpose and free from errors.

  To Do:
  Check use of #ifndef I2CDisplay_h

  Changes:


******************************************************************************************************
*/

#ifndef I2CDisplay_h              //this and the #endif at the bottom, prevents problems if the I2CDisplay.h is included twice     
#define I2CDisplay_h

#include "Arduino.h"
#include <Wire.h>

#include "I2CDisplay_Definitions.h"

/*
//these are the commands that go in the first byte of a transfer on the I2C
//Some commnads are a single byte only
ClearDisplay = 0x43;         //'C'
CursorPosition = 0x50;       //'P'
StartText = 0x54;            //'T'
FontScale = 0x53;            //'S'
UpdateDisplay = 0x55;        //'U'

FontStyle = 0x46;            //'F'
DisplayRotation = 0x52;      //'R'
InitialiseDisplay = 0x49;    //'I'
TextColour = 0x31;           //'1'
BackgroundColour = 0x32;     //'2'
ClearRow = 0x33;             //'3'
Contrast = 0x34;             //'4' 
Test = 0x35;                 //'5' 

//I2CDisplay Colours
Black = 0x00;
Blue = 0x01;
Red = 0x02;
Magenta = 0x03;
Green = 0x04;
Cyan = 0x05;
Yellow = 0x06;
White = 0x07;

*/


const byte dowaitready = 1;
const byte nowaitready = 0;



class I2CDisplay : public Print
{
  public:
    I2CDisplay(int Display_Address);             //This function is public, meaning that it can be accessed by people using your library,
    void ClearDisplayRow(byte lrow);
    void Update();
    void SetContrast(byte lcontrast);
    void SetCursorPosition(byte lcol, byte lrow);
    void SetTextScale(byte lscale);
    void Checkforwait();
    void SetwaitReady(byte _wait);
    void WaitReady();
    void SetTextColour(byte lcolour);
    void SetBackgroundColour(byte lcolour);
    void SetDisplayRotation(byte lrotation);
	void Clear();
	void DoTest();

    virtual size_t write(uint8_t _character);         
    //virtual size_t write(const uint8_t *s, size_t size);  
	virtual size_t write(const uint8_t *s);
	
  private:                                       //These functions are private, meaning that they can only be accessed from within the class itself
    int _Display_Address;
    byte _character_ready;
    byte _waitstatus = 1;                        //when set to 0, there is no wait for display to complete write, when set to 1 program waits for display to complete write,
    int GetStatus();
};

#endif
