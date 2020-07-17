//AFSK_RTTY.h
/*
******************************************************************************************************

  Easy Build Tracker Programs for Arduino

  Copyright of the author Stuart Robinson - 02/10/17

  

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without
  the explicit permission of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the
  intended purpose and free from errors.

  This program sends data as audio tones (AFSK RTTY) at 300 baud, 7 bit, 1 start bit, 2 stop bits and no
  parity. Tones are 634Hz for a 0 bit and 1000hz for 1 bit. Tones are on pin Audio_Out.

  Can be used for transmitting ASFK RTTY over the air or for a direct link to a PC sound card

  AFSKrttybaud = 1475 for 300baud for 1284P with 8Mhz Crystal

  To Do:


******************************************************************************************************
*/



void start_AFSK_RTTY()
{
  tone(Audio_Out, tonehighHz);               //lead in is high tone
  delay(afskleadinmS);
}


void end_AFSK_RTTY()
{
  delay(500);                                 //500mS seconds of high tone to finish
  noTone(Audio_Out);
  digitalWrite(LED1, LOW);
}



void SendAFSKRTTY(byte chartosend)
//send the byte in chartosend as AFSK RTTY, assumes mark condition (idle) is already present
//Format is 7 bits, no parity and 2 stop bits
{
  byte numbits;
  //byte test;
  Serial.write(chartosend);                   //send character to serial terminal for display
  digitalWrite(LED1, LOW);
  tone(Audio_Out, tonelowHz);
  delayMicroseconds(AFSKrttybaud);            //delay for 1 bit at baud rate,start bit
  delayMicroseconds(AFSKrttybaud);

  for (numbits = 1;  numbits <= 7; numbits++) //send 7 bits, LSB first
  {
    if ((chartosend & 0x01) != 0)
    {
      digitalWrite(LED1, HIGH);
      tone(Audio_Out, tonehighHz);
    }
    else
    {
      digitalWrite(LED1, LOW);
      tone(Audio_Out, tonelowHz);              //send a 0 bit, 366hz shift, low
    }

    chartosend = (chartosend / 2);             //get the next bit
    delayMicroseconds(AFSKrttybaud);
    delayMicroseconds(AFSKrttybaud);
  }
  digitalWrite(LED1, HIGH);                    //start  mark condition
  tone(Audio_Out, tonehighHz);                 //send a 1 bit high tone
  delayMicroseconds(AFSKrttybaud);             //leave time for the stop bit
  delayMicroseconds(AFSKrttybaud);             //and another stop bit
  delayMicroseconds(AFSKrttybaud);
  delayMicroseconds(AFSKrttybaud);
}


