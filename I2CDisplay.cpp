#include "Arduino.h"
#include "I2CDisplay.h"


I2CDisplay::I2CDisplay(int Display_Address)      //I2CDisplay:: before the name of the function says that the function (I2CDisplay()) is part of the I2CDisplay class.

{
  _Display_Address = Display_Address;            //by convention add _ to make it clear which variables are private
}


size_t I2CDisplay::write(uint8_t _lcharacter)
{
  Wire.beginTransmission(_Display_Address);      //send display address
  Wire.write(StartText);
  Wire.write(_lcharacter);
  Wire.endTransmission();
  Checkforwait();
  return 1;
}


size_t I2CDisplay::write(const uint8_t *s)  
//size_t I2CDisplay::write(const uint8_t *s, size_t size)
{
  byte _character, i = 0;

  Wire.beginTransmission(_Display_Address);  //send backpack address
  Wire.write(StartText);
  while (1)
  {
    _character = s[i++];
    if (_character == 0)
    {
      break;
    }
    Wire.write(_character);
  }
  Wire.endTransmission();

  i--;
  Checkforwait();
  return i;
}


void I2CDisplay::Clear()
{
  Wire.beginTransmission(_Display_Address);  //send backpack address
  Wire.write(ClearDisplay);
  Wire.endTransmission();
  Checkforwait();
}


int I2CDisplay::GetStatus()
{
  Wire.requestFrom(_Display_Address, 1);
  _character_ready = Wire.read();
  return _character_ready;
}


void I2CDisplay::WaitReady()
{
  while (GetStatus());                //wait until backpack returns 0 indicating its ready for next character
}


void I2CDisplay::SetwaitReady(byte wait)
{
  _waitstatus = wait;
}


void I2CDisplay::Checkforwait()
{
  if (_waitstatus)
  {
    WaitReady();
  }
}


void I2CDisplay::SetTextScale(byte lscale)
{
  Wire.beginTransmission(_Display_Address);  //send backpack address
  Wire.write(FontScale);
  Wire.write(lscale);
  Wire.endTransmission();
  Checkforwait();
}


void I2CDisplay::SetCursorPosition(byte lcol, byte lrow)
{
  Wire.beginTransmission(_Display_Address);  //send backpack address
  Wire.write(CursorPosition);
  Wire.write(lcol);
  Wire.write(lrow);
  Wire.endTransmission();
  Checkforwait();
}


void I2CDisplay::SetDisplayRotation(byte lrotation)
{
  Wire.beginTransmission(_Display_Address);  //send backpack address
  Wire.write(DisplayRotation);
  Wire.write(lrotation);
  Wire.endTransmission();
  Checkforwait();
}

void I2CDisplay::SetContrast(byte lcontrast)
{
  Wire.beginTransmission(_Display_Address);  //send backpack address
  Wire.write(Contrast);
  Wire.write(lcontrast);
  Wire.endTransmission();
  Checkforwait();
}

void I2CDisplay::Update()
{
  Wire.beginTransmission(_Display_Address);  //send backpack address
  Wire.write(UpdateDisplay);
  Wire.endTransmission();
  Checkforwait();
}


void I2CDisplay::ClearDisplayRow(byte lrow)
{
  Wire.beginTransmission(_Display_Address);  //send backpack address
  Wire.write(ClearRow);
  Wire.write(lrow);
  Wire.endTransmission();
  Checkforwait();
}


void I2CDisplay::SetTextColour(byte lcolour)
{
  Wire.beginTransmission(_Display_Address);  //send backpack address
  Wire.write(TextColour);
  Wire.write(lcolour);
  Wire.endTransmission();
  Checkforwait();
}


void I2CDisplay::SetBackgroundColour(byte lcolour)
{
  Wire.beginTransmission(_Display_Address);  //send backpack address
  Wire.write(BackgroundColour);
  Wire.write(lcolour);
  Wire.endTransmission();
  Checkforwait();
}

void I2CDisplay::DoTest()
{
  Wire.beginTransmission(_Display_Address);  //send backpack address
  Wire.write(DTest);
  Wire.endTransmission();
  Checkforwait();
}
