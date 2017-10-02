//LoRa3.h
/*
*******************************************************************************************************************************
  Easy Build LoRaTracker Programs for Arduino

  Copyright of the author Stuart Robinson - 14/08/17

  http://www.LoRaTracker.uk

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This is program is the routines for using the LoRa device and is common for all the newer 'LoRaTracker' programs.

  To Do:



*******************************************************************************************************************************
*/


//Constant names for bandwidth settings
const byte BW7800 = 0;          //7.8khz
const byte BW10400 = 16;        //10.4khz
const byte BW15600 = 32;        //15.6khz
const byte BW20800 = 48;        //20.8khz
const byte BW31200 = 64;        //31.2khz
const byte BW41700 = 80;        //41.7khz
const byte BW62500 = 96;        //62.5khz
const byte BW12500 = 112;       //125khz
const byte BW250000 = 128;      //250khz
const byte BW500000 = 144;      //500khz

//Constant names for Spreading Factors
const byte SF6 = 6;
const byte SF7 = 7;
const byte SF8 = 8;
const byte SF9 = 9;
const byte SF10 = 10;
const byte SF11 = 11;
const byte SF12 = 12;

//Constant names for coding rate settings
const byte CR45 = 2;            //4:5
const byte CR46 = 4;            //4:6
const byte CR47 = 6;            //4:7
const byte CR48 = 8;            //4:8

//Constant names for LoRa Header Settings
const byte Explicit    = 0;     //Use to set explicit header
const byte Implicit    = 1;     //Use to set implicit header

//Miscellaneous definitions
//const byte Deviation = 0x52;
const byte LowDoptON = 0x08;    //value to turn low data rate optimization on
const byte LowDoptOFF = 0x00;   //value to turn low data rate optimization off
const byte PrintASCII = 0;      //value to cause buffer print to appear as ASCII
const byte PrintDecimal = 1;    //value to cause buffer print to appear as decimal numbers
const byte PrintHEX = 2;        //value to cause buffer print to appear as hexadecimal numbers
const byte Strip = 1;           //value for setting stip of addressing information on packet
const byte NoStrip = 0;         //value for sending addressing information as part of packet


//SX1278 Register names
const byte lora_RegFifo = 0x00;
const byte lora_WRegFifo = 0x80;
const byte lora_RegOpMode = 0x01;
const byte lora_RegFdevLsb = 0x05;
const byte lora_RegFrMsb = 0x06;
const byte lora_RegFrMid = 0x07;
const byte lora_RegFrLsb = 0x08;
const byte lora_RegPaConfig = 0x09;
const byte lora_RegOcp = 0x0B;
const byte lora_RegLna = 0x0C;
const byte lora_RegFifoAddrPtr = 0x0D;
const byte lora_RegFifoTxBaseAddr = 0x0E;
const byte lora_RegFifoRxBaseAddr = 0x0F;
const byte lora_RegFifoRxCurrentAddr = 0x10;
const byte lora_RegIrqFlagsMask = 0x11;
const byte lora_RegIrqFlags = 0x12;
const byte lora_RegRxNbBytes = 0x13;
const byte lora_RegRxHeaderCntValueMsb = 0x14;
const byte lora_RegRxHeaderCntValueLsb = 0x15;
const byte lora_RegRxPacketCntValueMsb = 0x16;
const byte lora_RegRxPacketCntValueLsb = 0x17;
const byte lora_RegPktSnrValue = 0x19;
const byte lora_RegPktRssiValue = 0x1A;
const byte lora_RegRssiValue = 0x1B;
const byte lora_RegFsiMSB = 0x1D;
const byte lora_RegFsiLSB = 0x1E;
const byte lora_RegModemConfig1 = 0x1D;
const byte lora_RegModemConfig2 = 0x1E;
const byte lora_RegSymbTimeoutLsb = 0x1F;
const byte lora_RegPreambleLsb = 0x21;
const byte lora_RegPayloadLength = 0x22;
const byte lora_RegFifoRxByteAddr = 0x25;
const byte lora_RegModemConfig3 = 0x26;
const byte lora_RegPacketConfig2 = 0x31;
const byte lora_RegDioMapping = 0x40;
const byte lora_RegPllHop = 0x44;


byte  lora_RXBUFF[lora_RXBUFF_Size];           //buffer where received packets are stored
byte  lora_TXBUFF[lora_TXBUFF_Size];           //buffer for packet to send

byte  lora_RXStart;               //start of packet data in RXbuff
byte  lora_RXEnd;                 //end of packet data in RXbuff
byte  lora_RXPacketType;          //type number of received packet
byte  lora_RXDestination;         //destination address of received packet
byte  lora_RXSource;              //source address of received packet
unsigned int lora_RXpacketCount;  //count of received packets

byte  lora_TXStart;               //start of packet data in TX buffer
byte  lora_TXEnd;                 //end of packet data in TX buffer
byte  lora_TXPacketType;          //type number of transmitted packet
byte  lora_TXDestination;         //destination address of transmitted packet
byte  lora_TXSource;              //source address of transmitted packet
unsigned int lora_TXpacketCount;  //count of transmitted packets

int8_t lora_BackGroundRSSI;       //measured background noise level
int8_t lora_PacketRSSI;           //RSSI of received packet
int8_t lora_PacketSNR;            //signal to noise ratio of received packet
byte  lora_RXPacketL;             //length of packet received, includes source, destination and packet type.
byte  lora_TXPacketL;             //length of packet received, includes source, destination and packet type.
byte  lora_Power;                 //power setting for mode

unsigned long lora_TXTime;        //used to record TX On time
unsigned long lora_StartTXTime;   //used to record when TX starts
unsigned long lora_RXTime;        //used to record RX On time
unsigned long lora_StartRXTime;   //used to record when RX starts



/*
**************************************************************************************************
  Library Functions
**************************************************************************************************
*/


unsigned long lora_returnbandwidth(byte BWregvalue)
{
  switch (BWregvalue)
  {
    case 0:
      return 7800;

    case 16:
      return 10400;

    case 32:
      return 15600;

    case 48:
      return 20800;

    case 64:
      return 31200;

    case 80:
      return 41700;

    case 96:
      return 62500;

    case 112:
      return 125000;

    case 128:
      return 250000;

    case 144:
      return 500000;

    default:
      break;
  }
}


float lora_CalcSymbolTime(float Bandwidth, byte SpreadingFactor)
{
  //calculates symbol time from passed bandwidth (lbandwidth) and Spreading factor (lSF)and returns in mS
  float symbolTimemS;
  symbolTimemS = (Bandwidth / pow(2, SpreadingFactor));
  symbolTimemS = (1000 / symbolTimemS);
  return symbolTimemS;
}


byte lora_GetOptimisation(byte Bandwidth, byte SpreadingFactor)
{
  //from the passed bandwidth (bandwidth) and spreading factor this routine
  //calculates whether low data rate optimisation should be on or off

  unsigned long tempBandwidth;
  float symbolTime;
  tempBandwidth = lora_returnbandwidth(Bandwidth);
  symbolTime = lora_CalcSymbolTime(tempBandwidth, SpreadingFactor);

#ifdef LORADEBUG
  Serial.print(F("Symbol Time "));
  Serial.print(symbolTime, 3);
  Serial.println(F("mS"));
#endif

  if (symbolTime > 16)
  {
#ifdef LORADEBUG
    Serial.println(F("LDR Opt on"));
#endif
    return LowDoptON;
  }
  else
  {
#ifdef LORADEBUG
    Serial.println(F("LDR Opt off"));
#endif
    return LowDoptOFF;
  }


}

void lora_ResetDev()
{
  //resets the LoRa device
  digitalWrite(lora_NReset, LOW);    //take reset line low
  delay(5);
  digitalWrite(lora_NReset, HIGH);   //take it high
}


void lora_Write(byte Reg, byte RegData)
{
  //write a byte to a LoRa register
  digitalWrite(lora_NSS, LOW);       //set NSS low
  SPI.transfer(Reg | 0x80);          //mask address for write
  SPI.transfer(RegData);             //write the byte
  digitalWrite(lora_NSS, HIGH);      //set NSS high
}


byte lora_Read(byte Reg)
{
  //read a byte from a LoRa register
  byte RegData;
  digitalWrite(lora_NSS, LOW);       //set NSS low
  SPI.transfer(Reg & 0x7F);          //mask address for read
  RegData = SPI.transfer(0);         //read the byte
  digitalWrite(lora_NSS, HIGH);      //set NSS high
  return RegData;
}

void lora_SetFreq(uint64_t freq64, int loffset)
{
  freq64 = freq64 + loffset;
  freq64 = ((uint64_t)freq64 << 19) / 32000000;
  lora_Write(lora_RegFrMsb, (byte)(freq64 >> 16));
  lora_Write(lora_RegFrMid, (byte)(freq64 >> 8));
  lora_Write(lora_RegFrLsb, (byte)(freq64 >> 0));
}


uint32_t lora_GetFreq2()
{
  //get the current set LoRa device frequency
  byte Msb, Mid, Lsb;
  unsigned int uinttemp;
  float floattemp;
  Msb = lora_Read(lora_RegFrMsb);
  Mid = lora_Read(lora_RegFrMid);
  Lsb = lora_Read(lora_RegFrLsb);
  floattemp = ((Msb * 0x10000ul) + (Mid * 0x100ul) + Lsb);
  floattemp = ((floattemp * 61.03515625) / 1000000ul);
  uinttemp = (uint32_t)(floattemp * 1000000);
  return uinttemp;
}


float lora_GetFreq()
{
  //get the current set LoRa frequency
  byte lora_LFMsb, lora_LFMid, lora_LFLsb;
  unsigned long lora_Ltemp;
  float lora_Ltemp1;
  lora_LFMsb = lora_Read(lora_RegFrMsb);
  lora_LFMid = lora_Read(lora_RegFrMid);
  lora_LFLsb = lora_Read(lora_RegFrLsb);
  lora_Ltemp = ((lora_LFMsb * 0x10000ul) + (lora_LFMid * 0x100ul) + lora_LFLsb);
  lora_Ltemp1 = ((lora_Ltemp * 61.03515625) / 1000000ul);
  return lora_Ltemp1;
}


byte lora_CheckDevice()
{
  //check there is a device out there, writes a register and read back
  byte RegData;
  lora_Write(lora_RegFrMid, 0xAA);
  RegData = lora_Read(lora_RegFrMid);    //Read RegFrMid
  if (RegData == 0xAA )
  {
    return true;
  }
  else
  {
    return false;
  }
}


void lora_Setup()
{
  //initialize LoRa device registers and check its responding
  lora_ResetDev();                            //Clear all registers to default
  lora_Write(lora_RegOpMode, 0x08);           //RegOpMode, need to set to sleep mode before configure for LoRa mode
  lora_Write(lora_RegOcp, 0x2B);              //RegOcp
  lora_Write(lora_RegLna, 0x23);              //RegLna
  lora_Write(lora_RegSymbTimeoutLsb, 0xFF);   //RegSymbTimeoutLsb
  lora_Write(lora_RegPreambleLsb, 0x0C);      //RegPreambleLsb, default
  lora_Write(lora_RegFdevLsb, Deviation);     //LSB of deviation, 5kHz
}


void lora_TXONDirect(byte TXPower)
{
  //turns on transmitter,in direct mode for FSK and audio  power level is from 2 to 17
#ifdef LORADEBUG
  Serial.print(TXPower);
  Serial.print(F("dBm "));
#endif
  lora_StartTXTime = millis();
  lora_Write(lora_RegPaConfig, (TXPower + 0xEE));
  lora_Write(lora_RegOpMode, 0x0B);           //TX on direct mode, low frequency mode
}


void lora_TXOFF()
{
  //turns off transmitter
  unsigned long temp;
  lora_Write(lora_RegOpMode, 0x08);           //TX and RX to sleep, in direct mode
#ifdef LORADEBUG
  temp = millis() - lora_StartTXTime;
  Serial.print(temp);
  Serial.println(F("mS"));
#endif
  lora_TXTime = lora_TXTime + (millis() - lora_StartTXTime);
}


void lora_DirectSetup()
{
  //setup LoRa device for direct modulation mode
  lora_Write(lora_RegOpMode, 0x08);
  lora_Write(lora_RegPacketConfig2, 0x00);    //set continuous mode
}


void lora_Tone(int ToneFrequency, int ToneLength, int TXPower)
{
  //Transmit an FM tone
  lora_DirectSetup();
  lora_Write(lora_RegFdevLsb, Deviation);     //We are generating a tone so set the deviation, 5kHz
  lora_TXONDirect(TXPower);
  //tone(lora_TonePin, ToneFrequency);
  delay(ToneLength);
  //noTone(lora_TonePin);
  pinMode(lora_TonePin, INPUT);
  lora_TXOFF();
}


void lora_SetModem2(byte Bandwidth, byte SpreadingFactor, byte CodeRate, byte Header)
{
  byte optimisation;
  lora_Write(lora_RegOpMode, 0x08);          //RegOpMode, need to set to sleep mode before configure for LoRa mode
  lora_Write(lora_RegOpMode, 0x88);          //go into LoRa mode
  lora_Write(lora_RegModemConfig1, (Bandwidth + CodeRate + Header));
  lora_Write(lora_RegModemConfig2, (SpreadingFactor * 16 + 7));
  optimisation = lora_GetOptimisation(Bandwidth, SpreadingFactor);
  lora_Write(lora_RegModemConfig3, optimisation);
}


void lora_Print()
{
  //prints the contents of LoRa registers to serial monitor
  byte Loopv1, Loopv2, Reg, RegData;

  Serial.println(F("LoRa Registers"));
  Serial.print(F("Reg    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F"));
  Serial.println();
  Reg = 0;
  for (Loopv1 = 0; Loopv1 <= 7; Loopv1++)
  {
    Serial.print(F("0x"));
    Serial.print(Loopv1, HEX);              //print the register number
    Serial.print(F("0  "));
    for (Loopv2 = 0; Loopv2 <= 15; Loopv2++)
    {
      RegData = lora_Read(Reg);
      if (RegData < 0x10) {
        Serial.print(F("0"));
      }
      Serial.print(RegData, HEX);           //print the register number
      Serial.print(F(" "));
      Reg++;
    }
    Serial.println();
  }
}


/*
**************************************************************************************************
  Library Functions RX
**************************************************************************************************
*/

void lora_RXBuffPrint(byte PrintType)
{
  //Print contents of RX buffer as ASCII,decimal or HEX
  //PrintType = 0 = ASCII
  //PrintType = 1 = Decimal
  //PrintType = 2 = HEX

  byte index, bufferData;
  Serial.write(lora_RXPacketType);
  Serial.write(lora_RXDestination);
  Serial.write(lora_RXSource);

  for (byte index = lora_RXStart; index <= lora_RXEnd; index++)
  {
    if (PrintType == 0)
    {
      Serial.write(lora_RXBUFF[index]);
    }

    if (PrintType == 1)
    {
      Serial.print(lora_RXBUFF[index]);
      Serial.print(F(" "));
    }

    if (PrintType == 2)
    {
      bufferData = lora_RXBUFF[index];
      if (bufferData < 0x10)
      {
        Serial.print(F("0"));
      }
      Serial.print(bufferData, HEX);
      Serial.print(F(" "));
    }
  }
}


void lora_RXOFF()
{
  lora_Write(lora_RegOpMode, 0x89);                //TX and RX to sleep, in direct mode
  lora_RXTime = lora_RXTime + (millis() - lora_StartRXTime);
}


void lora_AddressInfo()
{
  //print the information for packet last received
  Serial.print(F("RXType,"));
  Serial.write(lora_RXPacketType);
  Serial.print(F("  Destination,"));
  Serial.write(lora_RXDestination);
  Serial.print(F("  Source,"));
  Serial.write(lora_RXSource);

  Serial.print(F("  Length,"));
  Serial.print(lora_RXPacketL);
  Serial.print(F(" "));
}

void lora_ReceptionInfo()
{
  //print the information for packet last received
  //note, lora_PacketSNR has already been converted into a signed value
  //lora_PacketRSSI is a signed value also

  Serial.print(F("SNR,"));
  Serial.print(lora_PacketSNR);
  Serial.print(F("dB"));

  Serial.print(F("  RSSI,"));
  Serial.print(lora_PacketRSSI);
  Serial.print(F("dB "));
}



int8_t lora_returnRSSI(byte RegData)
{
  RegData = (137 - RegData) * (-1);
  return RegData;
}


int8_t lora_returnSNR(byte RegData)
{

  if (RegData > 127)
  {
    RegData =  ((255 - RegData) / 4) * (-1);
  }
  else
  {
    RegData = RegData / 4;
  }
  return RegData;
}


void lora_ReadPacket()
{
  byte index, RegData;
  lora_RXpacketCount++;
  lora_RXPacketL = lora_Read(lora_RegRxNbBytes);
  lora_PacketRSSI = lora_returnRSSI(lora_Read(lora_RegPktRssiValue));
  lora_PacketSNR = lora_returnSNR(lora_Read(lora_RegPktSnrValue));

  lora_Write(lora_RegFifoAddrPtr, 0);        //set RX FIFO ptr

  digitalWrite(lora_NSS, LOW);               //start the burst read
  SPI.transfer(lora_RegFifo);                //address for burst read

  lora_RXPacketType = SPI.transfer(0);
  lora_RXDestination = SPI.transfer(0);
  lora_RXSource = SPI.transfer(0);

  lora_RXStart = 0;
  lora_RXEnd = lora_RXPacketL - 4;

  for (index = lora_RXStart; index <= lora_RXEnd; index++)
  {
    RegData = SPI.transfer(0);
    lora_RXBUFF[index] = RegData;
  }
  digitalWrite(lora_NSS, HIGH);

}


void lora_RXONLoRa()
{
  //puts lora device into listen mode and receives packet exits with packet in array lora_RXBUFF(256)

  lora_Write(lora_RegOpMode, 0x09);
  lora_Write(lora_RegFifoRxBaseAddr, 0x00);
  lora_Write(lora_RegFifoAddrPtr, 0x00);
  lora_Write(lora_RegIrqFlagsMask, 0x9F);                //only allow rxdone and crc error
  lora_Write(lora_RegIrqFlags, 0xFF);
  lora_Write(lora_RegDioMapping, 0x00);                  //DIO0 will be RXDone
  lora_Write(lora_RegOpMode, 0x8D);
  lora_StartRXTime = millis();
  lora_BackGroundRSSI = lora_Read(lora_RegRssiValue);    // get the background noise level
}



byte lora_readRXready()
{
  byte RegData;
  RegData = lora_Read(lora_RegIrqFlags);
  return RegData;
}


byte lora_readRXready2()
{
  //reads the DIO0 pin to see if a packet is ready

  if (digitalRead(lora_DIO0))
  {
    return lora_Read(lora_RegIrqFlags);
  }
  else
  {
    return 0;
  }
}


byte lora_waitPacket(char waitPacket, unsigned long waitSeconds)
{
  //wait time specified for a incoming packet, 0 = no timeout
  //returns a value of 0 for timeout, 1 for packet received

  char PacketType;
  byte RegData;
  unsigned long endtime;
  endtime = (millis() + (waitSeconds * 1000));
  lora_RXONLoRa();
#ifdef LORADEBUG
  Serial.print(F("Wait "));
  Serial.write(waitPacket);
  Serial.println();
#endif

  do
  {
    RegData = lora_readRXready();

    if (RegData == 64)
    {
      lora_ReadPacket();
      lora_AddressInfo();
      Serial.println();
      PacketType = lora_RXPacketType;
      lora_RXONLoRa();                          //ready for next and clear flags
    }

    if ((waitSeconds > 0) && (millis() >= endtime))
    {
#ifdef LORADEBUG
      Serial.println(F("Timeout"));
#endif
      return 0;
    }

    if (Serial.available() > 0)
    {
#ifdef LORADEBUG
      Serial.println(F("Serial in ?"));
#endif
      keypress = 1;
      while (Serial.read() != -1);             //clear serial input buffer
      return 0;                                //treat a keypress as a timeout so return 0
    }

  }
  while ((PacketType !=  waitPacket));

  return 1;
}

/*
**************************************************************************************************
  Library Functions TX
**************************************************************************************************
*/



void lora_TXBuffPrint(byte PrintType)
{
  //Print contents of TX buffer as ASCII,decimal or HEX

  byte index, bufferData;
  Serial.write(lora_TXPacketType);
  Serial.write(lora_TXDestination);
  Serial.write(lora_TXSource);

  for (index = lora_TXStart; index <= lora_TXEnd; index++)
  {
    if (PrintType == 0)
    {
      Serial.write(lora_TXBUFF[index]);
    }

    if (PrintType == 1)
    {
      Serial.print(lora_TXBUFF[index]);
      Serial.print(F(" "));
    }

    if (PrintType == 2)
    {
      bufferData = lora_TXBUFF[index];
      if (bufferData < 0x10)
      {
        Serial.print(F("0"));
      }
      Serial.print(bufferData, HEX);
      Serial.print(F(" "));
    }
  }
}


void lora_TXONLoRa(byte TXPower)
{
  //turns on LoRa transmitter, Sends packet, power level is from 2 to 17
#ifdef LORADEBUG
  Serial.print(TXPower);
  Serial.print(F("dBm  "));
#endif
  lora_StartTXTime = millis();
  lora_Write(lora_RegPaConfig, (TXPower + 0xEE));   //set TX power
  lora_Write(lora_RegOpMode, 0x8B);                 //TX on direct mode, low frequency mode
}



void lora_Send(byte TXBuffStart, byte TXBuffEnd, char TXPacketType, char TXDestination, char TXSource, long TXTimeout, byte TXPower, byte StripAddress)
{
  byte index;
  byte BufferData, RegData;
  byte TXPacketL = 0;

  lora_Write(lora_RegOpMode, 0x09);
  lora_Write(lora_RegIrqFlags, 0xFF);
  lora_Write(lora_RegIrqFlagsMask, 0xF7);
  lora_Write(lora_RegFifoTxBaseAddr, 0x00);
  lora_Write(lora_RegFifoAddrPtr, 0x00);            //start burst read

  digitalWrite(lora_NSS, LOW);                      //Set NSS low
  SPI.transfer(lora_WRegFifo);                      //address for burst write

  if (!StripAddress)
  {
    SPI.transfer(TXPacketType);                     //Write the packet type
    SPI.transfer(TXDestination);                    //Destination node
    SPI.transfer(TXSource);                         //Source node
    TXPacketL = 3;                                  //We have added 3 header bytes
  }

  for (index = TXBuffStart; index <= TXBuffEnd; index++)
  {
    TXPacketL++;

    if (TXPacketL > 253)                            //check for overlong packet here, wraps around from limit at 251 to 0
    {
      TXPacketL--;                                  //remove increment to packet length
      break;
    }
    BufferData = lora_TXBUFF[index];
    SPI.transfer(BufferData);
  }

  digitalWrite(lora_NSS, HIGH);                     //finish the burst write
  lora_Write(lora_RegPayloadLength, TXPacketL);
  TXTimeout = TXTimeout * 945;                      //convert seconds to mS, delay in TX done loop is 1ms

  lora_TXONLoRa(TXPower);

  do
  {
    delay(1);
    TXTimeout--;
    RegData = lora_Read(lora_RegIrqFlags);
  }
  while (TXTimeout > 0 && RegData == 0) ;           //use a timeout counter, just in case the TX sent flag is missed

  lora_TXOFF();
}


byte lora_QueuedSend(byte TXBuffStart, byte TXBuffEnd, char TXPacketType, char TXDestination, char TXSource, long TXTimeout, byte TXPower, byte Attempts, byte StripAddress)
{
  //wait time specified for a incoming packet, 0 = no timeout
  //returns a value of 0 for timeout, 1 for packet sent and acknowledged

  byte RegData;
  unsigned int tempAttempts = Attempts;             //to store value of lora_Attempts

#ifdef LORADEBUG
  Serial.print(F("Queue "));
  Serial.write(TXPacketType);
  Serial.write(TXDestination);
  Serial.write(TXSource);
  Serial.print(F(" Attempts "));
  Serial.println(Attempts);
#endif

  do
  {

    if (!lora_waitPacket(ClearToSendCommand, 0))    //returns a value of 0 for timeout, 1 for packet received, no timeout
    {
#ifdef LORADEBUG
      Serial.println(F("Exit QueuedSend"));
#endif
      return 0;                                     //either timeout or key exit
    }

    delay(1000);

#ifdef LORADEBUG
    Serial.print(F("Send "));
    Serial.write(TXPacketType);
    Serial.write(TXDestination);
    Serial.write(TXSource);
#endif

    lora_Send(TXBuffStart, TXBuffEnd, TXPacketType, TXDestination, TXSource, TXTimeout, TXPower, StripAddress);

    if (lora_waitPacket(ACK, 5) == 1)          //when returns the value of lora_RXPacketType may be updated
    {
      return 1;
    }

    if (Serial.available() > 0)
    {
#ifdef LORADEBUG
      Serial.println(F("Serial in ?"));
#endif
      keypress = 1;
      while (Serial.read() != -1);             //clear serial input buffer
      return 0;
    }

    if (tempAttempts != 0)
    {
      Attempts--;
    }
    else
    {
      Attempts = 1;
    }

  }
  while ( (lora_RXPacketType != ACK) && (Attempts > 0) );

#ifdef LORADEBUG
  Serial.println(F("Timeout Waiting for ACK"));
#endif
  return 0;
}

