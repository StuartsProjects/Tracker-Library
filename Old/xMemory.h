//Memory.h
/*
**************************************************************************************************

  Easy Build LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 13/01/17

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.
**************************************************************************************************
*/





/***************************************************************************
  Start of EEPROM Routines
  /***************************************************************************/

#ifdef USE_EEPROM_MEMORY
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


/*void Memory_WriteInt(int addr, int x)
{
  //byte lowbyte, highbyte;
  //byte temp;

  if (x > 32767)       //check if its negative
  {

    x = ((~x) + 32768);               //use EXOR to convert to twos compliment and reset bit 15
  }

  EEPROM.put(addr, lowByte(x));
  EEPROM.put((addr + 1), highByte(x));
}
*/

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



/*int Memory_ReadInt(unsigned int addr)
{
  byte lowbyte, highbyte;
  EEPROM.get(addr, lowbyte);
  EEPROM.get((addr + 1), highbyte);
  return (lowbyte + (highbyte * 256));
}
*/

unsigned long Memory_ReadULong(unsigned int addr)
{
  unsigned long x;
  EEPROM.get(addr, x);
  return x;
}
#endif
/***************************************************************************
  End of EEPROM Routines
  /***************************************************************************/




/***************************************************************************
  Start of SPI FRAM Routines
  /***************************************************************************/
#ifdef USE_SPI_FRAM_MEMORY


const byte Memory_WREN   = 0b0110;        //Write Enable Latch
const byte Memory_WRDI   = 0b0100;        //Reset Write Enable Latch
const byte Memory_RDSR   = 0b0101;        //Read Status Register
const byte Memory_WRSR   = 0b0001;        //Write Status Register
const byte Memory_READ   = 0b0011;        //Read Memory
const byte Memory_WRITE  = 0b0010;        //Write Memory
const byte Memory_RDID   = 0b10011111;    //Read Device ID


void Memory_EnableWrite()
{
  //Set Write Enable
  digitalWrite(MEMORY_CS, LOW);        // set NSS low
  SPI.transfer(Memory_WREN);           // set write enable
  digitalWrite(MEMORY_CS, HIGH);       // set CS high
}


void Memory_DisableWrite()
{
  //Clear Write Enable
  digitalWrite(MEMORY_CS, LOW);        // set CS low
  SPI.transfer(Memory_WRDI);           // OP code for clear write enable
  digitalWrite(MEMORY_CS, HIGH);       // set CS high
}


byte Memory_ReadStatus()
{
  byte j;
  digitalWrite(MEMORY_CS, LOW);        //set CS low
  SPI.transfer(Memory_RDSR);           //OP code for status read
  j = SPI.transfer(0);             //read the byte
  digitalWrite(MEMORY_CS, HIGH);       //set CS high
  return j;
}


void Memory_Init()
{
//nothing to do for FRAM  
}


void Memory_WriteByte(unsigned int addr, byte lvar1)
{
  //write a byte to the FRAM
  byte msb, lsb;

  Memory_EnableWrite();
  msb = highByte(addr);
  lsb = lowByte(addr);

  digitalWrite(MEMORY_CS, LOW);     //set CS low
  SPI.transfer(Memory_WRITE);       //OP code for write data byte
  SPI.transfer(msb);                //write the MSB Address
  SPI.transfer(lsb);                //write the LSB Address
  SPI.transfer(lvar1);              //write the data
  digitalWrite(MEMORY_CS, HIGH);    //set CS high
  Memory_DisableWrite();
}


void Memory_WriteInt(int addr, int x)
{
  //This writes signed or unsigned ints
  //Serial.println(F("Write Uint"));
  byte msb, lsb;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);     //set CS low
  SPI.transfer(Memory_WRITE);       //OP code for write data byte
  SPI.transfer(msb);                //write the MSB Address
  SPI.transfer(lsb);                //write the LSB Address
  SPI.transfer(lowByte(x));
  SPI.transfer(highByte(x));
  digitalWrite(MEMORY_CS, HIGH);    //set CS high
  Memory_DisableWrite();
}

 

void Memory_WriteUInt(unsigned int addr, unsigned int x)
{
  //This writes signed or unsigned ints
  //Serial.println(F("Write Uint"));
  byte msb, lsb;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);     //set CS low
  SPI.transfer(Memory_WRITE);       //OP code for write data byte
  SPI.transfer(msb);                //write the MSB Address
  SPI.transfer(lsb);                //write the LSB Address
  SPI.transfer(lowByte(x));
  SPI.transfer(highByte(x));
  digitalWrite(MEMORY_CS, HIGH);    //set CS high
  Memory_DisableWrite();
}



void Memory_WriteFloat(unsigned int addr, float x)
{
  byte i, j, msb, lsb;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);    //set CS low
  SPI.transfer(Memory_WRITE);      //OP code for write data byte
  SPI.transfer(msb);               //write the MSB Address
  SPI.transfer(lsb);               //write the LSB Address

  union
  {
    byte b[4];
    float f;
  } data;
  data.f = x;

  for (int i = 0; i < 4; i++)
  {
    j = data.b[i];
    SPI.transfer(j);                //write the data
  }
  digitalWrite(MEMORY_CS, HIGH);    //set CS high
  Memory_DisableWrite();
}


void Memory_WriteULong(unsigned int addr, unsigned long x)
{
  byte i, j, msb, lsb;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);    //set CS low
  SPI.transfer(Memory_WRITE);      //OP code for write data byte
  SPI.transfer(msb);               //write the MSB Address
  SPI.transfer(lsb);               //write the LSB Address

  union
  {
    byte b[4];
    unsigned long f;
  } data;
  data.f = x;

  for (int i = 0; i < 4; i++)
  {
    j = data.b[i];
    SPI.transfer(j);                //write the data
  }
  digitalWrite(MEMORY_CS, HIGH);    //set CS high
  Memory_DisableWrite();
}


byte Memory_ReadByte(unsigned int addr)
{
  byte lsb, msb, j;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);    //set NSS low
  SPI.transfer(Memory_READ);       //OP code for write data byte
  SPI.transfer(msb);               //write the MSB Address
  SPI.transfer(lsb);               //write the LSB Address
  j = SPI.transfer(0);         //read the byte
  digitalWrite(MEMORY_CS, HIGH);   //set NSS high
  return j;
}



float Memory_ReadFloat(unsigned int addr)
{
  byte i, j, msb, lsb;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);      //set NSS low
  SPI.transfer(Memory_READ);         //OP code for write data byte
  SPI.transfer(msb);                 //write the MSB Address
  SPI.transfer(lsb);                 //write the LSB Address

  union
  {
    byte b[4];
    float f;
  } readdata;

  for (int i = 0; i < 4; i++)
  {
    j = SPI.transfer(0);              //read the byte
    readdata.b[i] = j;
  }
  digitalWrite(MEMORY_CS, HIGH);      //set NSS high
  return readdata.f;
}


unsigned long Memory_ReadULong(unsigned int addr)
{
  byte i, j, msb, lsb;

  msb = highByte(addr);
  lsb = lowByte(addr);
  Memory_EnableWrite();

  digitalWrite(MEMORY_CS, LOW);      //set NSS low
  SPI.transfer(Memory_READ);         //OP code for write data byte
  SPI.transfer(msb);                 //write the MSB Address
  SPI.transfer(lsb);                 //write the LSB Address

  union
  {
    byte b[4];
    unsigned long f;
  } readdata;

  for (int i = 0; i < 4; i++)
  {
    j = SPI.transfer(0);              //read the byte
    readdata.b[i] = j;
  }
  digitalWrite(MEMORY_CS, HIGH);      //set NSS high
  return readdata.f;
}



unsigned int Memory_ReadUInt(unsigned int addr)
{
  byte lsb, msb;

  msb = highByte(addr);
  lsb = lowByte(addr);

  digitalWrite(MEMORY_CS, LOW);        //set NSS low
  SPI.transfer(Memory_READ);           //OP code for write data byte
  SPI.transfer(msb);                   //write the MSB Address
  SPI.transfer(lsb);                   //write the LSB Address
  lsb = SPI.transfer(0);               //read the byte
  msb = SPI.transfer(0);               //read the byte
  digitalWrite(MEMORY_CS, HIGH);       //set NSS high
  return (lsb + (msb * 256));
}



int Memory_ReadInt(unsigned int addr)
{
  //byte llowbyte, lhighbyte;
  //int i;
  //byte j;
  byte lsb, msb;

  msb = highByte(addr);
  lsb = lowByte(addr);

  digitalWrite(MEMORY_CS, LOW);        //set NSS low
  SPI.transfer(Memory_READ);           //OP code for write data byte
  SPI.transfer(msb);                   //write the MSB Address
  SPI.transfer(lsb);                   //write the LSB Address
  lsb = SPI.transfer(0);               //read the byte
  msb = SPI.transfer(0);               //read the byte
  digitalWrite(MEMORY_CS, HIGH);       //set NSS high
  return (lsb + (msb * 256));
}

#endif
/***************************************************************************
  End of SPI FRAM Routines
***************************************************************************/

/***************************************************************************
  Start of I2C FRAM Routines
***************************************************************************/
#ifdef USE_I2C_FRAM_MEMORY 

//for MB85RC16PNF I2C FRAM
const int Memory_I2C_Addr = 0x50;                 //base address of FRAM


void Memory_Init()
{
Wire.begin();  
}  


void Start_Store_Settings()
{
}

void End_Store_Settings()
{
}


/***************************************************************************
 Write Routines
/***************************************************************************/

void Memory_WriteByte(unsigned int addr, byte x)
{
  byte msb_addr = (highByte(addr) & 0x07);            //mask off bottom 3 bytes of address top 3 bits of addr only are used, 2K FRAM 
  byte lsb_addr = lowByte(addr);

  Wire.beginTransmission(Memory_I2C_Addr + msb_addr);
  Wire.write(lsb_addr);
  Wire.write(x);
  Wire.endTransmission();
}


void Memory_WriteFloat(unsigned int addr, float x)
{
  byte index, val;
  byte msb_addr = (highByte(addr) & 0x07);            //mask off bottom 3 bytes of address top 3 bits of addr only are used, 2K FRAM 
  byte lsb_addr = lowByte(addr);
    
  union
  {
    byte b[4];
    float f;
  } data;
  
  data.f = x;

  Wire.beginTransmission(Memory_I2C_Addr + msb_addr);
  Wire.write(lsb_addr);
  
  for (index = 0; index < 4; index++)
  {
    val = data.b[index];
    Wire.write(val);              // write the data
  }

  Wire.endTransmission();
}


void Memory_WriteInt(unsigned int addr, int x)
{

 byte msb_addr = (highByte(addr) & 0x07);            //mask off bottom 3 bytes of address top 3 bits of addr only are used, 2K FRAM 
 byte lsb_addr = lowByte(addr);
 byte msb_data = highByte(x);
 byte lsb_data = lowByte(x);
 

  Wire.beginTransmission(Memory_I2C_Addr + msb_addr);
  Wire.write(lsb_addr);
  Wire.write(lsb_data);
  Wire.write(msb_data);
  Wire.endTransmission();
}


void Memory_WriteUInt(unsigned int addr, unsigned int x)
{

 byte msb_addr = (highByte(addr) & 0x07);            //mask off bottom 3 bytes of address top 3 bits of addr only are used, 2K FRAM 
 byte lsb_addr = lowByte(addr);
 byte msb_data = highByte(x);
 byte lsb_data = lowByte(x);
 

  Wire.beginTransmission(Memory_I2C_Addr + msb_addr);
  Wire.write(lsb_addr);
  Wire.write(lsb_data);
  Wire.write(msb_data);
  Wire.endTransmission();
}





void Memory_WriteULong(unsigned int addr, unsigned long x)
{
  byte index, val;
  byte msb_addr = (highByte(addr) & 0x07);            //mask off bottom 3 bytes of address top 3 bits of addr only are used, 2K FRAM 
  byte lsb_addr = lowByte(addr);
    
  union
  {
    byte b[4];
    unsigned long f;
  } data;
  
  data.f = x;

  Wire.beginTransmission(Memory_I2C_Addr + msb_addr);
  Wire.write(lsb_addr);
  
  for (index = 0; index < 4; index++)
  {
    val = data.b[index];
    Wire.write(val);              // write the data
  }

  Wire.endTransmission();
}




/***************************************************************************
 Read Routines
/***************************************************************************/

byte Memory_ReadByte(unsigned int addr)
{
  byte data;
  byte msb_addr = (highByte(addr) & 0x07);            //mask off bottom 3 bytes of address top 3 bits of addr only are used, 2K FRAM 
  byte lsb_addr = lowByte(addr);
  
  byte val;
  Wire.beginTransmission(Memory_I2C_Addr + msb_addr);
  Wire.write(lsb_addr);
  Wire.endTransmission();
  Wire.requestFrom((Memory_I2C_Addr + msb_addr), 1);
  data = Wire.read();
  return data;
}  


int Memory_ReadInt(unsigned int addr)
{

 byte lsb_data, msb_data;
 
 byte msb_addr = (highByte(addr) & 0x07);            //mask off bottom 3 bytes of address top 3 bits of addr only are used, 2K FRAM 
 byte lsb_addr = lowByte(addr);


  Wire.beginTransmission(Memory_I2C_Addr + msb_addr);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.requestFrom(Memory_I2C_Addr + msb_addr, 2);
  lsb_data = Wire.read();
  msb_data = Wire.read();
  
  return (lsb_data + (msb_data * 256));
}


unsigned int Memory_ReadUInt(unsigned int addr)
{

 byte lsb_data, msb_data;
 
 byte msb_addr = (highByte(addr) & 0x07);            //mask off bottom 3 bytes of address top 3 bits of addr only are used, 2K FRAM 
 byte lsb_addr = lowByte(addr);


  Wire.beginTransmission(Memory_I2C_Addr + msb_addr);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.requestFrom(Memory_I2C_Addr + msb_addr, 2);
  lsb_data = Wire.read();
  msb_data = Wire.read();
  
  return (lsb_data + (msb_data * 256));
}




float Memory_ReadFloat(unsigned int addr)
{
  byte index, val;
  
  byte msb_addr = (highByte(addr) & 0x07);            //mask off bottom 3 bytes of address top 3 bits of addr only are used, 2K FRAM 
  byte lsb_addr = lowByte(addr);

  Wire.beginTransmission(Memory_I2C_Addr + msb_addr);
  Wire.write(lsb_addr);
  Wire.endTransmission();
  Wire.requestFrom(Memory_I2C_Addr + msb_addr, 4);
    
  union
  {
    byte b[4];
    float f;
  } readdata;


  for (int index = 0; index < 4; index++)
  {
    val = Wire.read();          // read the byte
    readdata.b[index] = val;
  }
  return readdata.f;
}

unsigned long Memory_ReadULong(unsigned int addr)
{
  byte index, val;
  byte msb_addr = (highByte(addr) & 0x07);            //mask off bottom 3 bytes of address top 3 bits of addr only are used, 2K FRAM 
  byte lsb_addr = lowByte(addr);
  
  Wire.beginTransmission(Memory_I2C_Addr + msb_addr);
  Wire.write(lsb_addr);
  Wire.endTransmission();
  Wire.requestFrom(Memory_I2C_Addr + msb_addr, 4);

  union
  {
    byte b[4];
    unsigned long f;
  } readdata;

  for (int index = 0; index < 4; index++)
  {
    val = Wire.read();          // read the byte
    readdata.b[index] = val;
  }
  
  return readdata.f;
}



#endif
/***************************************************************************
  End of I2C FRAM Routines
***************************************************************************/



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



void Memory_Print()
{
  //prints the contents of memory used for storung variables and settings
  byte memory_LLoopv1;
  byte memory_LLoopv2;
  byte memory_Laddr = 0;
  byte memory_Ldata;
  unsigned int CRC;
  Serial.println(F("Memory Contents"));
  Serial.print(F("Lcn    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F"));
  Serial.println();

  for (memory_LLoopv1 = 0; memory_LLoopv1 <= 7; memory_LLoopv1++)
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




