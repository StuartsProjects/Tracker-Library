//EEPROM_Memory.h
/*
*******************************************************************************************************************************
Easy Build LoRaTracker Programs for Arduino

Copyright of the author Stuart Robinson - 04/06/17

http://www.LoRaTracker.uk

These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
free from errors.
  
To Do:
  
*******************************************************************************************************************************
*/


void Memory_WriteByte(unsigned int addr, byte x)
{
  //write a byte to the EEPROM
  EEPROM.put(addr, x);
}


void Memory_WriteUInt(unsigned int addr, unsigned int x)
{
  EEPROM.put(addr, x);
}


void Memory_WriteInt(unsigned int addr, int x)
{
  EEPROM.put(addr, x);
}


void Memory_WriteULong(unsigned int addr, unsigned long x)
{
  EEPROM.put(addr, x);
}

void Memory_WriteFloat(unsigned int addr, float x)
{
  EEPROM.put(addr, x);
}


byte Memory_ReadByte(unsigned int addr)
{
  byte x;
  EEPROM.get(addr, x);
  return x;
}

float Memory_ReadFloat(unsigned int addr)
{
  float x;
  EEPROM.get(addr, x);
  return x;
}

int Memory_ReadInt(unsigned int addr)
{
  int x;
  EEPROM.get(addr, x);
  return x;
}

unsigned int Memory_ReadUInt(unsigned int addr)
{
  unsigned int x;
  EEPROM.get(addr, x);
  return x;
}


unsigned long Memory_ReadULong(unsigned int addr)
{
  unsigned long x;
  EEPROM.get(addr, x);
  return x;
}



/***************************************************************************
  Start of general purpose memory routines
***************************************************************************/

unsigned int Memory_CRC(unsigned int startaddr, unsigned int endaddr)
{
  uint16_t i, CRC;

  CRC = 0xffff;                               //start value for CRC16
  byte j;

  for (i = startaddr; i <= endaddr; i++)                     //element 4 is first character after $$$$ at start
  {
    CRC ^= ((uint16_t)Memory_ReadByte(i) << 8);
    for (j = 0; j < 8; j++)
    {
      if (CRC & 0x8000)
        CRC = (CRC << 1) ^ 0x1021;
      else
        CRC <<= 1;
    }
  }
  return CRC;

}


void Config_Memory_Print()
{
  //prints the contents of memory used for storung variables and settings
  byte memory_LLoopv1;
  byte memory_LLoopv2;
  byte memory_Laddr = 0;
  byte memory_Ldata;
  unsigned int CRC;
  Serial.println(F("Config Memory Contents"));
  Serial.print(F("Lcn    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F"));
  Serial.println();

  for (memory_LLoopv1 = 0; memory_LLoopv1 <= 15; memory_LLoopv1++)
  {
    Serial.print(F("0x"));
    Serial.print(memory_LLoopv1, HEX);                             //print the register number
    Serial.print(F("0  "));
    for (memory_LLoopv2 = 0; memory_LLoopv2 <= 15; memory_LLoopv2++)
    {
      memory_Ldata = Memory_ReadByte(memory_Laddr);
      if (memory_Ldata < 0x10) {
        Serial.print("0");
      }
      Serial.print(memory_Ldata, HEX);                 //print the register number
      Serial.print(F(" "));
      memory_Laddr++;
    }
    Serial.println();
  }

  CRC = Memory_CRC(addr_StartBindData, addr_EndBindData);
  Serial.print(F("Memory CRC 0x"));
  Serial.println(CRC, HEX);
  Serial.println();
  
}


void Memory_Set(unsigned int startaddr, unsigned int endaddr, byte lval)
{
  unsigned int i;
  for (i = startaddr; i <= endaddr; i++)
  {
    Memory_WriteByte(i, lval);
  }
}




