//Generate_NMEA.h
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

  Proram Generates GPGGA and GPRMC sentences from decimal Latitude, Longitude and Altitude values and sends NMEA sentence to
  Serial port.

  For use with mapping applications such as MemoryMap (PC) and AlpinQuest (Android)

  The GPS Bluetooth Mouse application for Android requires;
  1. That GPGGA and GPRMC sentances are present
  2. That the time field (GPGGA and GPRMC) be present
  3. That the date field (GPRMC) be present
  4. The sentence checksum can be wrong or missing

  For Memory Map (PC) the above applies but the checksum need to be correct.

  Unfortunately Memory Map will report an GPS communications error if it does not receive data approx every 5 seconds
  The 'data' does not need to be a NMEA sentence it can be replaced with a CR/LF as a keep alive.

  The combination of Bluetooth GPS mouse and Alpinquest on Android devices is not so fussy.

  Tested sending serial data to a Bluetooth HC06 on pin Bluetooth_TX, uses SendOnlySoftwareSerial.
  
  This version of the NMEA Generator uses the lora_RXBuff for sending to reduce the memory requirement

  To Do:

*******************************************************************************************************************************
*/

#define USING_BLUETOOTH                                    //so the rest of the program can know if Bluetooth is in use

#define Bluetooth_buff lora_RXBUFF

void print_NMEA_Bluetooth(byte lCount)
{
  //prints payload to Bluetooth port
  byte i, j;

  for (i = 0; i <= lCount; i++)
  {
    j = Bluetooth_buff[i];
    Bluetooth_Serial.write(j);
  }
  Bluetooth_Serial.println();
  Bluetooth_Serial.println();
}


void print_NMEA_Terminal(byte lCount)
{
  //prints payload to console port
  byte i, j;

  for (i = 0; i <= lCount; i++)
  {
    j = Bluetooth_buff[i];
    Serial.write(j);
  }
  Serial.println();
}


float convert_degrees(float decimaldegrees)
{
  int integerdegrees;
  float decimals, answer;
  integerdegrees = (int) decimaldegrees;
  decimals = decimaldegrees - integerdegrees;
  decimals = (decimals * 6) / 10;
  answer = (integerdegrees + decimals) * 100;
  return answer;
}


char Hex2(char lchar)
{
  //used in CRC calculation
  char Table[] = "0123456789ABCDEF";
  return Table[lchar];
}


void replaceSpaces(byte lcount)
{
  //there can be spaces (0x20) characters in the buffer, they need to be removed
  byte i;
  for (i = 0; i <= lcount; i++)
  {
    if (Bluetooth_buff[i] == ' ')
    {
      Bluetooth_buff[i] = '0';
    }
  }
}


byte addChecksum(byte lcount)
{
  byte i, checksum;

  checksum = 0;

  for (i = 1; i <= lcount; i++)
  {
    checksum = checksum ^ Bluetooth_buff[i];
  }

  Bluetooth_buff[lcount++] = '*';
  Bluetooth_buff[lcount++] = Hex2((checksum >> 4) & 15);   //first digit of checksum
  Bluetooth_buff[lcount] = Hex2(checksum & 15);            //last digit of checksum
  return lcount;
}


void send_NMEA(float latfloat, float lonfloat, float alt)
{
  //this is the routine called from the main program
  byte checksum, count, i;
  int intalt;
  float latitude, longitude;

  char LatArray[12], LonArray[12], AltArray[10];
  char Latquad = 'N', Lonquad = 'E';

  if (latfloat < 0)
  {
    Latquad = 'S';
    latfloat = -latfloat;
  }

  if (lonfloat < 0)
  {
    Lonquad = 'W';
    lonfloat = -lonfloat;
  }

  latitude = convert_degrees(latfloat);
  longitude = convert_degrees(lonfloat);
  intalt = (int) alt;

  dtostrf(latitude, 9, 4, LatArray);                        //this will create spaces where leading zeros would be present in NMEA output
  dtostrf(longitude, 10, 4, LonArray);
  dtostrf(intalt, 1, 0, AltArray);

  memset(Bluetooth_buff, 0, sizeof(Bluetooth_buff));        //clear array

  Serial.println(F("Send NMEA"));

  snprintf(Bluetooth_buff,
           Bluetooth_Buff_Size,
           "$GPGGA,000000.000,%s,%c,%s,%c,1,4,3.16,%s.0,M,53.3,M,,",
           LatArray,
           Latquad,
           LonArray,
           Lonquad,
           AltArray
          );

  count = strlen(Bluetooth_buff);                            //how long is the array ?
  replaceSpaces(count);                                      //replace spaces with 0s
  count = addChecksum(count);                                //checksum adds characters to array, need to pick up new end value

  for (i = 1; i <= 2; i++)
  {
   Bluetooth_Serial.println("Wakeup Bluetooth Mouse!!");
  }

  print_NMEA_Bluetooth(count);                               //print the GPGGA
  //print_NMEA_Terminal(count);

  memset(Bluetooth_buff, 0, sizeof(Bluetooth_buff));         //clear array

  //Serial.print(F("Send NMEA > "));

  snprintf(Bluetooth_buff,
           Bluetooth_Buff_Size,
           "$GPRMC,000000.000,A,%s,%c,%s,%c,0.00,0.00,010101,,,A",
           LatArray,
           Latquad,
           LonArray,
           Lonquad,
           AltArray
          );

  count = strlen(Bluetooth_buff);                             //how long is the array ?
  replaceSpaces(count);                                       //replacespaces with 0s
  count = addChecksum(count);                                 //checksum adds characters to array, need to pick up new end value
  print_NMEA_Bluetooth(count);                                //print the GPRMC
  //print_NMEA_Terminal(count);
}


void Bluetooth_Serial_Setup()
{
  Bluetooth_Serial.begin(BluetoothBaud);
}


