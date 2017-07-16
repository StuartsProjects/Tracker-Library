//SerialGPS.h
/*
Master Copy 04/06/17
*******************************************************************************************************************************
Easy Build LoRaTracker Programs for Arduino

Copyright of the author Stuart Robinson - 04/06/17

http://www.LoRaTracker.uk

These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
free from errors.

This program reads the GPS via serial, can be hardware of softserial. Stores the config settings for UBLOX GPS in Flash to
save on RAM memory. 
  
To Do:
  
*******************************************************************************************************************************
*/




void getprocessGPSchar();
void start_GPSRead();
void gpsOn();
void gpsOff();
void gpsSetup();
void config_UBLOXGPS();
void setup_GPSCyclic();
void setup_GPSPowerSave();
void software_ShutdownGPS();
void setup_GPSGPMode();
void sendConfig(unsigned char *Config, int Length);
void setupFlightMode();


unsigned long GPSonTime = 0;
unsigned long GPSoffTime = 0;
unsigned long GPSFixTime = 0;

void getprocessGPSchar()                   //get and process output from GPS
{
  //unsigned char tempchar;
  while (GPSserial.available() > 0)
    gps.encode(GPSserial.read());
}


void start_GPSRead()
{
//left empty for future use
}


void gpsOn(boolean powercontrol)
{
  //turns on the GPS
  //has to deal with software power control (UBLOX) and hardware power control, for tracker boards with that option
  
  GPSserial.begin(GPSBaud);
   
  if (powercontrol)
  {
  digitalWrite(GPSPOWER, LOW);           //force GPS power on 
  GPSserial.println();                   //wakeup gps, in case software power down is in use       
  }

  Serial.println(F("GPSOn"));

 }



void gpsOff(boolean powercontrol)
{
  //power down GPS, prepare to go to sleep
  //has to deal with software power control (UBLOX) and hardware power control, for tracker boards with that option
      
  if (powercontrol)
  {
  digitalWrite(GPSPOWER, HIGH);          //force GPS power off 
  software_ShutdownGPS(); 
  GPSoffTime = millis();
  Serial.print(F("GPSOff at "));
  GPSFixTime = (GPSoffTime - GPSonTime) + GPSShutdownTimemS;
  Serial.print(GPSFixTime);
  Serial.println(F("mS"));
 }
  
  GPSserial.end();

}



#ifdef UBLOX

void gpsSetup()
{
  config_UBLOXGPS();                      //configure GPS to HAB operation
}


void config_UBLOXGPS()
{
  //each config sentence starts in the array with the nuimber of bytes to send
  //if the number of bytes to send is 0, that is the end of messages to send 
  byte i, j, byteread, Messagesize;
  int k, ptr, Arraysize;
  Serial.println(F("Config Ublox GPS"));

  FLASH_ARRAY(byte, GPSFlash,  
              0x15, 0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0x19, 0x98, //clear current config

              0x14, 0xB5, 0x62, 0x06, 0x3E, 0x0C, 0x00, 0x00, 0x00, 0x20, 0x01, 0x06, 0x08, 0x0E, 0x00, 0x00, 0x00, 0x01, 0x01, 0x8F, 0xB2,  //glonass off
              

              0x10, 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, //GPGLL off

              0x10, 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x46, //GPGLL off

              0x10, 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x31, //GPGLS off

              0x10, 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x38, //GPSGSV off

              0x2C, 0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, //Flight mode on
              0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0xDC,

              0x15, 0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1B, 0xA9, //save current config
              

              0x00);  //messages end

  ptr = 0;

  do
  {
    Messagesize = GPSFlash[ptr];

    ptr++;

    for (j = 1; j <= Messagesize; j++)
    {
      byteread = GPSFlash[ptr];
      GPSserial.write(byteread);
      ptr++;
    }
    Messagesize = GPSFlash[ptr];
    delay(50);
  }
  while  (Messagesize != 0x00);  //0x00 message size terminates list
}


void setup_GPSCyclic()
{
  //turn on cyclic, this is done seperatly after the first fix.
  //unfortunatley if the config sequence is; Turn on GLONASS, set cyclic, set flight at power on
  //the GPS can run for approx 13 seconds and will reset if it has not downloaded enough GPS info, which
  //can happen if the signals are poor. The GPS can be stuck in this loop for many minutues.

  byte byteread, j;
  Serial.print(F("GPS Cyclic "));
  FLASH_ARRAY(byte, CyclicFlash, 0xB5, 0x62, 0x06, 0x11, 0x02, 0x00, 0x08, 0x01, 0x22, 0x92)
  for (j = 0; j <= 9; j++)
  {
    byteread = CyclicFlash[j];
    GPSserial.write(byteread);
  }
  delay(25);
}


void setup_GPSPowerSave()
{
  //turn on power save mode
  byte byteread, j;
  Serial.print(F("GPS PowerSave "));
  FLASH_ARRAY(byte, PM2, 0xB5, 0x62, 0x06, 0x11, 0x02, 0x00, 0x08, 0x01, 0x22, 0x92)
  for (j = 0; j <= 9; j++)
  {
    byteread = PM2[j];
    GPSserial.write(byteread);
  }
  delay(25);
}


void software_ShutdownGPS()
{
  //go into software backup mode, GPS current is then reduced to circa 500uA
  #ifdef UBLOX
  
  byte byteread, j;
  Serial.println(F("Software Shutdown GPS"));
  FLASH_ARRAY(byte, softwareBackup, 0xB5, 0x62, 0x06, 0x57, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x50, 0x4B, 0x43, 0x42, 0x86, 0x46)
  for (j = 0; j <= 15; j++)
  {
    byteread = softwareBackup[j];
    GPSserial.write(byteread);
  }
  delay(25);
  #endif
}
#endif


#ifndef UBLOX   //if no UBLOX defined then these are the setup routines which are null
  void gpsSetup()
  {}
  void setup_GPSCyclic()
  {}
  void setup_GPSPowerSave()
  {}
  void software_GPSBackup()
  {}
#endif


