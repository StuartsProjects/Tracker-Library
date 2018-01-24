//SPIFRAM_Memory_FM25CL64B_MB85RS64.h
/*
*******************************************************************************************************************************
  Easy Build LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 2/10/17

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This program provides a standard set of memory read and write routines for a SPI FRAM. Tested with Cypress FM25CL64B and
  Fujitsu MB85RS64.

  To Do:

*******************************************************************************************************************************
*/



const byte Memory_WREN   = 0b0110;        //Write Enable Latch
const byte Memory_WRDI   = 0b0100;        //Reset Write Enable Latch
const byte Memory_RDSR   = 0b0101;        //Read Status Register
const byte Memory_WRSR   = 0b0001;        //Write Status Register
const byte Memory_READ   = 0b0011;        //Read Memory
const byte Memory_WRITE  = 0b0010;        //Write Memory
const byte Memory_RDID   = 0b10011111;    //Read Device ID


#include <SPI.h>


void Memory_Start()
{
  pinMode(MEMORY_CS, OUTPUT);             //for FRAM CS
  digitalWrite(MEMORY_CS, HIGH);          //set CS high
}


void Memory_End()
{
  //left empty for future use
}



void Memory_EnableWrite()
{
  //Set Write Enable
  digitalWrite(MEMORY_CS, LOW);           //set CS low
  SPI.transfer(Memory_WREN);              //set write enable
  digitalWrite(MEMORY_CS, HIGH);          //set CS high
}


void Memory_DisableWrite()
{
  //Clear Write Enable
  digitalWrite(MEMORY_CS, LOW);           //set CS low
  SPI.transfer(Memory_WRDI);              //OP code for clear write enable
  digitalWrite(MEMORY_CS, HIGH);          //set CS high
}


byte Memory_ReadStatus()
{
  byte j;
  digitalWrite(MEMORY_CS, LOW);           //set CS low
  SPI.transfer(Memory_RDSR);              //OP code for status read
  j = SPI.transfer(0);                    //read the byte
  digitalWrite(MEMORY_CS, HIGH);          //set CS high
  return j;
}


void Memory_WriteByte(unsigned int addr, byte x)
{
  //write a byte to the FRAM
  byte msb, lsb;

  Memory_EnableWrite();
  msb = highByte(addr);
  lsb = lowByte(addr);

  digitalWrite(MEMORY_CS, LOW);          //set CS low
  SPI.transfer(Memory_WRITE);            //OP code for write data byte
  SPI.transfer(msb);                     //write the MSB Address
  SPI.transfer(lsb);                     //write the LSB Address
  SPI.transfer(x);                       //write the data
  digitalWrite(MEMORY_CS, HIGH);         //set CS high
  Memory_DisableWrite();
}


void Memory_WriteInt(unsigned int addr, int x)
{
  //This writes signed or unsigned ints
  byte msb, lsb;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);         //set CS low
  SPI.transfer(Memory_WRITE);           //OP code for write data byte
  SPI.transfer(msb);                    //write the MSB Address
  SPI.transfer(lsb);                    //write the LSB Address
  SPI.transfer(lowByte(x));
  SPI.transfer(highByte(x));
  digitalWrite(MEMORY_CS, HIGH);        //set CS high
  Memory_DisableWrite();
}



void Memory_WriteUInt(unsigned int addr, unsigned int x)
{
  //This writes signed or unsigned ints
  byte msb, lsb;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);         //set CS low
  SPI.transfer(Memory_WRITE);           //OP code for write data byte
  SPI.transfer(msb);                    //write the MSB Address
  SPI.transfer(lsb);                    //write the LSB Address
  SPI.transfer(lowByte(x));
  SPI.transfer(highByte(x));
  digitalWrite(MEMORY_CS, HIGH);        //set CS high
  Memory_DisableWrite();
}



void Memory_WriteFloat(unsigned int addr, float x)
{
  byte i, j, msb, lsb;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);         //set CS low
  SPI.transfer(Memory_WRITE);           //OP code for write data byte
  SPI.transfer(msb);                    //write the MSB Address
  SPI.transfer(lsb);                    //write the LSB Address

  union
  {
    byte b[4];
    float f;
  } data;
  data.f = x;

  for (int i = 0; i < 4; i++)
  {
    j = data.b[i];
    SPI.transfer(j);                    //write the data
  }
  digitalWrite(MEMORY_CS, HIGH);        //set CS high
  Memory_DisableWrite();
}


void Memory_WriteULong(unsigned int addr, unsigned long x)
{
  byte i, j, msb, lsb;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);         //set CS low
  SPI.transfer(Memory_WRITE);           //OP code for write data byte
  SPI.transfer(msb);                    //write the MSB Address
  SPI.transfer(lsb);                    //write the LSB Address

  union
  {
    byte b[4];
    unsigned long f;
  } data;
  data.f = x;

  for (int i = 0; i < 4; i++)
  {
    j = data.b[i];
    SPI.transfer(j);                    //write the data
  }
  digitalWrite(MEMORY_CS, HIGH);        //set CS high
  Memory_DisableWrite();
}


byte Memory_ReadByte(unsigned int addr)
{
  byte lsb, msb, j;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);        //set CS low
  SPI.transfer(Memory_READ);           //OP code for write data byte
  SPI.transfer(msb);                   //write the MSB Address
  SPI.transfer(lsb);                   //write the LSB Address
  j = SPI.transfer(0);                 //read the byte
  digitalWrite(MEMORY_CS, HIGH);       //set CS high
  return j;
}



float Memory_ReadFloat(unsigned int addr)
{
  byte i, j, msb, lsb;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);        //set CS low
  SPI.transfer(Memory_READ);           //OP code for write data byte
  SPI.transfer(msb);                   //write the MSB Address
  SPI.transfer(lsb);                   //write the LSB Address

  union
  {
    byte b[4];
    float f;
  } readdata;

  for (int i = 0; i < 4; i++)
  {
    j = SPI.transfer(0);               //read the byte
    readdata.b[i] = j;
  }
  digitalWrite(MEMORY_CS, HIGH);       //set CS high
  return readdata.f;
}


unsigned long Memory_ReadULong(unsigned int addr)
{
  byte i, j, msb, lsb;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);        //set CS low
  SPI.transfer(Memory_READ);           //OP code for write data byte
  SPI.transfer(msb);                   //write the MSB Address
  SPI.transfer(lsb);                   //write the LSB Address

  union
  {
    byte b[4];
    unsigned long f;
  } readdata;

  for (int i = 0; i < 4; i++)
  {
    j = SPI.transfer(0);               //read the byte
    readdata.b[i] = j;
  }
  digitalWrite(MEMORY_CS, HIGH);       //set CS high
  return readdata.f;
}



unsigned int Memory_ReadUInt(unsigned int addr)
{
  byte lsb, msb;

  msb = highByte(addr);
  lsb = lowByte(addr);

  digitalWrite(MEMORY_CS, LOW);        //set CS low
  SPI.transfer(Memory_READ);           //OP code for write data byte
  SPI.transfer(msb);                   //write the MSB Address
  SPI.transfer(lsb);                   //write the LSB Address
  lsb = SPI.transfer(0);               //read the byte
  msb = SPI.transfer(0);               //read the byte
  digitalWrite(MEMORY_CS, HIGH);       //set CS high
  return (lsb + (msb * 256));
}



int Memory_ReadInt(unsigned int addr)
{
  byte lsb, msb;

  msb = highByte(addr);
  lsb = lowByte(addr);

  digitalWrite(MEMORY_CS, LOW);        //set CS low
  SPI.transfer(Memory_READ);           //OP code for write data byte
  SPI.transfer(msb);                   //write the MSB Address
  SPI.transfer(lsb);                   //write the LSB Address
  lsb = SPI.transfer(0);               //read the byte
  msb = SPI.transfer(0);               //read the byte
  digitalWrite(MEMORY_CS, HIGH);       //set CS high
  return (lsb + (msb * 256));
}




/***************************************************************************
  Start of general purpose memory routines
***************************************************************************/

unsigned int Memory_CRC(unsigned int startaddr, unsigned int endaddr)
{
  uint16_t i, CRC;

  CRC = 0xffff;                            //start value for CRC16
  byte j;

  for (i = startaddr; i <= endaddr; i++)   //element 4 is first character after $$$$ at start
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
  //prints the contents of memory used for storing variables and settings
  byte memory_LLoopv1;
  byte memory_LLoopv2;
  byte memory_Laddr = 0;
  byte memory_Ldata;
  unsigned int CRC;
  Serial.println(F("Memory Contents"));
  Serial.print(F("Lcn    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F"));
  Serial.println();

  for (memory_LLoopv1 = 0; memory_LLoopv1 <= 15; memory_LLoopv1++)
  {
    Serial.print(F("0x"));
    Serial.print(memory_LLoopv1, HEX);                //print the register number
    Serial.print(F("0  "));
    for (memory_LLoopv2 = 0; memory_LLoopv2 <= 15; memory_LLoopv2++)
    {
      memory_Ldata = Memory_ReadByte(memory_Laddr);
      if (memory_Ldata < 0x10) {
        Serial.print(F("0"));
      }
      Serial.print(memory_Ldata, HEX);                //print the register number
      Serial.print(F(" "));
      memory_Laddr++;
    }
    Serial.println();
  }

}


void Memory_Set(unsigned int startaddr, unsigned int endaddr, byte lval)
{
  unsigned int i;
  for (i = startaddr; i <= endaddr; i++)
  {
    Memory_WriteByte(i, lval);
  }
}



void Print_Memory(uint16_t start_addr, uint16_t end_addr)
{
  //print the contents of Memory
  byte data;
  unsigned int i;
   
  uint8_t value;
  for (uint16_t a = start_addr; a <= end_addr; a++) 
  {
    value = Memory_ReadByte(a);
    if ((a % 16) == 0) 
    {
      Serial.print(F("\n 0x")); 
      if (a < 0x10) 
      {
       Serial.print('0');
      }
      Serial.print(a, HEX); 
      Serial.print(F(": "));
    }
    Serial.print(F("0x")); 
    if (value < 0x10) 
      Serial.print('0');
    Serial.print(value, HEX); 
    Serial.print(F(" "));
  }
  Serial.println();
}


