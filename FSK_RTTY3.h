//FSK_RTTY3.h

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

  Used with the LoRa device in FSK RTTY mode to send data as upper sideband FSK RTTY at 100 or 200 baud, 7 bit, 1 start bit,
  2 stop bits and no parity. Frequency shift is 366Hz, 6 frequency steps for the LoRa device. The shift is passed to the
  start_FSKRTTY() function.
  
  This vesion of FSK_RTTY, is for the FSKRTTY only tracker where the FSK output is left permanatly on, this increase current 
  consumption but reduces drift. The leadin pips are inverted with short durations of TX off. 

  To Do:

*******************************************************************************************************************************
*/

void Send_FSKRTTY(byte chartosend, unsigned int local_FSKRTTYbaudDelay);
void Start_FSKRTTY(byte local_Regshift, unsigned int local_FSKRTTYleadin, byte local_FSKRTTYpips);
void FSK_RTTY_Low();
void FSK_RTTY_High();


byte ShiftH;                                  //high value of frequency register for FSK RTTY Shift
byte ShiftM;                                  //high value of frequency register for FSK RTTY Shift
byte ShiftL;                                  //high value of frequency register for FSK RTTY Shift
byte NoShiftH;                                //high value of frequency register for unshifted FSK RTTY
byte NoShiftM;                                //high value of frequency register for unshifted FSK RTTY
byte NoShiftL;                                //high value of frequency register for unshifted FSK RTTY
            

void Send_FSKRTTY(byte chartosend, unsigned int local_FSKRTTYbaudDelay)
//send the byte in chartosend as FSK RTTY, assumes mark condition (idle) is already present
//format is 7 bits, no parity and 2 stop bits
{
  byte numbits;
  //byte test;
  
  Serial.write(chartosend);                   //send character to serial terminal for display
  digitalWrite(LED1, LOW);
  FSK_RTTY_Low();                             //send a 0 bit, 366hz shift, low
  delayMicroseconds(local_FSKRTTYbaudDelay);  //delay for 1 bit at baud rate,start bit

  for (numbits = 1;  numbits <= 7; numbits++) //send 7 bits, LSB first
  {
    if ((chartosend & 0x01) != 0)
    {
      digitalWrite(LED1, HIGH);
      FSK_RTTY_High();                         //end a 1 bit, 1342hz shift, high tone
    }
    else
    {
      digitalWrite(LED1, LOW);
      FSK_RTTY_Low();                          //send a 0 bit, 366hz shift, low
    }

    chartosend = (chartosend / 2);             //get the next bit
    delayMicroseconds(local_FSKRTTYbaudDelay);
  }
  digitalWrite(LED1, HIGH);                    //start  mark condition
  FSK_RTTY_High();                             //send a 1 bit, 1342hz shift, high tone
  delayMicroseconds(local_FSKRTTYbaudDelay);   //leave time for the stop bit
  delayMicroseconds(local_FSKRTTYbaudDelay);   //and another stop bit
}


void FSK_RTTY_Low()
{
  lora_Write(lora_RegFrMsb, NoShiftH);
  lora_Write(lora_RegFrMid, NoShiftM);
  lora_Write(lora_RegFrLsb, NoShiftL);
}


void FSK_RTTY_High()
{
  lora_Write(lora_RegFrMsb, ShiftH);
  lora_Write(lora_RegFrMid, ShiftM);
  lora_Write(lora_RegFrLsb, ShiftL);
}


void Start_FSKRTTY(byte local_Regshift, unsigned int local_FSKRTTYleadin, byte local_FSKRTTYpips)
{
  byte i;
  int j;

  NoShiftH = lora_Read(lora_RegFrMsb);
  NoShiftM = lora_Read(lora_RegFrMid);
  NoShiftL = lora_Read(lora_RegFrLsb);

  ShiftH = NoShiftH;
  ShiftM = NoShiftM;
  ShiftL = NoShiftL;

#ifdef DEBUG
  Serial.print(F("FSK NoShift Registers "));
  Serial.print(NoShiftH, HEX);
  Serial.print(F(" "));
  Serial.print(NoShiftM, HEX);
  Serial.print(F(" "));
  Serial.println(NoShiftL, HEX);
#endif

  j = NoShiftL + local_Regshift;

  if (j > 255)
  {
    j = j - 256;
    ShiftL = j;
    ShiftM++;
    if (ShiftM == 256)
    {
      ShiftM = 0;
      ShiftH++;
    }
  }
  else
  {
    ShiftL = j;
    ShiftM = NoShiftM;
    ShiftH = NoShiftH;
  }

#ifdef DEBUG
  Serial.print(F("FSK Shift Registers "));
  Serial.print(ShiftH, HEX);
  Serial.print(F(" "));
  Serial.print(ShiftM, HEX);
  Serial.print(F(" "));
  Serial.println(ShiftL, HEX);
#endif

  lora_Write(lora_RegFdevLsb, 0x00);                //set deviation to 0

  FSK_RTTY_High();

  for (i = 1; i <= local_FSKRTTYpips; i++)           //send FSK lead in pips
  {
    digitalWrite(LED1, HIGH);
    lora_TXONDirect(10);
    delay(950);
    digitalWrite(LED1, LOW);
    Serial.print(F("Pip "));
    lora_TXOFF();
    delay(50);
  }
  lora_TXONDirect(10);
  delay(local_FSKRTTYleadin);
  Serial.println();
  lora_Write(lora_RegPllHop, 0xAD);                  //set fast hop mode, needed for fast changes of frequency
}




