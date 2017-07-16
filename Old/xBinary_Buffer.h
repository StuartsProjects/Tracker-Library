//Binary_Read.h
/*
//Master Copy 01/06/17
******************************************************************************************************

LoRaTracker Programs for Arduino

Copyright of the author Stuart Robinson - 30/04/2017

http://www.LoRaTracker.uk

These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without
the explicit permission of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the
intended purpose and free from errors.

To Do:

******************************************************************************************************
*/


float readFloat(byte temp[], byte addr)
{
  int index;
  byte bufferData;

  union
  {
    byte b[4];
    float f;
  } readdata;

  for (int index = 0; index < 4; index++)
  {
    bufferData = temp[addr + index];
    readdata.b[index] = bufferData;
  }
  return readdata.f;
}


byte readByte(byte temp[], byte addr)
{
  return temp[addr];
}


unsigned int readUint(byte temp[], byte addr)
{
  byte lowbyte, highbyte;
  lowbyte = temp[addr];
  highbyte = temp[addr + 1];
  return (lowbyte + (highbyte * 256));
}


void writeByte(byte temp[], byte addr, byte x)
{
  temp[addr] = lowByte(x);
}


void writeUint(byte temp[],byte addr, unsigned int x)
{
temp[addr] = lowByte(x);
temp[addr+1] = highByte(x);
}


void writeFloat(byte temp[], byte addr, float x)
{
  int index;
  byte bufferData;
  
  union
  {
    byte b[4];
    float f;
  } data;
  data.f = x;
  
  for (int index = 0; index < 4; index++)
  {
    bufferData = data.b[index];
    temp[addr+index] = bufferData;
  }

} 





