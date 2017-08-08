//Program_Definitions2.h

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

For boards; LoRaTrackerHAB1, LoRaTracker_Locator1, PIHTracker3, PIHTracker2, LoRaTracker_Relay1, LoRaTracker_Receiver1 (1284P),
MikrobusShieldV3, MikrobusShield2560,
  
To Do:
  
*******************************************************************************************************************************
*/

const char ACK = 'A';
const char LinkReport = 'B';            //HAB Style in CSV ASCII format
const char bLinkReport = 'b';           //binary style link report
const char ClearToSend = 'C';
const char ClearToSendCommand = 'c';
const char Error = 'E';
const char NoFix = 'F';
const char NoGPS = 'G';
const char GLONASSDetected = 'g';
const char IsLost = 'H';                //packet to notify of lost status (Help)
const char Info = 'i';                  //binary info packet
const char PowerUp = 'P';
const char Memory = 'M';
const char NACK = 'N';
const char NACKCommand = 'n';
const char Repeated = 'R';
const char LocationCSVPacket = 'S';     //Short loacation packet in CSV ASCII format
const char LocationBinaryPacket = 's';  //Short location packet in binary format
const char Testpacket = 'T';            //identifies test packet
const char Test = 'T';
const char Timepacket = 't';            //seconds up time
const char Wakeup = 'W';
const char ResetTracker = 'X';
const char Config1 = 'Y';
const char Config0 = 'Z';

const char Bind = '#';
const char Broadcast = '*';             //broadcast address
const char PacketStart = '$';           //command packets have a payload of at least one byte, so put this at start
const char HABPacket = '$';             //HAB Style location payload in CSV ASCII format
const char WritePacketMemory = '0';     //Write bytes to Memory
const char TestMode1 = '1';             //used to switch to Testmode1 settings
const char TestMode2 = '2';             //used to switch to Testmode2 settings
const char INCFreq = '3';
const char DECFreq = '4';
const char LMLCSVPacket = '8';          //short LML payload; lat,lon,alt in CSV ASCII format
const char LMLCSVPacket_Repeated = '9'; //short LML payload that has been repeated


/*
******************************************************************************************************
  Bit numbers for current_config byte settings  end definitions for packet types
******************************************************************************************************
*/

//Bit numbers for current_config byte settings
const byte SearchEnable = 0;         //bit num to set in config byte to enable search mode packet
const byte TXEnable = 1;             //bit num to set in config byte to enable transmissions
const byte FSKRTTYEnable = 2;        //bit num to set in config byte to enable FSK RTTY
const byte CheckFence = 3;           //bit number to control whether fence is checked 0 = NoCheck
const byte DozeEnable = 4;           //bit num to set in config byte to put tracker in Doze mode
const byte AddressStrip = 6;         //bit number to control address part of payload, 1 to strip, 0 to allow
const byte GPSPowerSave = 7;         //bit when set enables GPS power save.


//Status byte settings
const byte GPSFix = 0;               //flag bit number to indicate GPS fix
const byte GLONASSisoutput = 1;      //flag bit number to indicate GLONASS found
const byte UBLOXDynamicModel6Set = 2; //flag bit set when UBLOX dynamic mode 6 has been set (and Checked)
const byte GPSError = 3;              //flag bit to indicate GPS error or some sort.   
const byte NoGPSTestMode = 7;        //flag bit number to indicate tracker in no GPS test mode

const byte wait_command = 3;         //base time in seconds to wait for command
const byte runmA = 4;                //processor run current
const byte GPSmA = 22;               //GPS average current when aquiring fix
const byte RXmA = 11;                //LoRa device receive current
const byte TXmA = 40;                //LoRa device transmit current 10dBm
const byte SleepmA = 1;              //approx current in sleep, GPS consumes circa 500uA

#define SwitchOn 1                   //for tracker GPS control
#define DontSwitch 0
#define LeaveOff 0
#define LeaveOn 1
#define Enabled 1
#define Disabled 0
#define UseGPSPowerControl 1
#define DoNotUseGPSPowerControl 0

/*
******************************************************************************************************
  Addressing information for variables stored in Memory
  This is kept to 1024 bytes of storage.
  First 256 bytes is program configuration data and settings
  Second 256 bytes is for storing changing data, sequence number, reset count.
  Third 256 bytes is for storing the last received HAB data packet.
  Forth 256 bytes is for storing the location and time of local GPS fix and tracker GPS fix.
  The bind data is from addr_StartBindData to addr_EndBindData, no more than 128bytes.
  ******************************************************************************************************
*/


const unsigned int addr_StartMemory = 0x00;                   //the start of memory
const unsigned int addr_StartConfigData = 0x00;               //the start of config data in memory
const unsigned int addr_StartBindData = 0x00;                 //the start of the Bind data
const unsigned int addr_TrackerMode_Frequency = 0x00;         //unsigned long 4 bytes
const unsigned int addr_SearchMode_Frequency = 0x04;          //unsigned long 4 bytes
const unsigned int addr_CommandMode_Frequency = 0x08;         //unsigned long 4 bytes
const unsigned int addr_TrackerMode_Bandwidth = 0x0C;         //byte 1 byte
const unsigned int addr_SearchMode_Bandwidth = 0x0D;          //byte 1 byte
const unsigned int addr_CommandMode_Bandwidth = 0x0E;         //byte 1 byte
const unsigned int addr_TrackerMode_SpreadingFactor = 0x0F;   //byte 1 byte
const unsigned int addr_SearchMode_SpreadingFactor = 0x10;    //byte 1 byte
const unsigned int addr_CommandMode_SpreadingFactor = 0x11;   //byte 1 byte
const unsigned int addr_TrackerMode_CodeRate = 0x12;          //byte 1 byte
const unsigned int addr_SearchMode_CodeRate = 0x13;           //byte 1 byte
const unsigned int addr_CommandMode_CodeRate = 0x14;          //byte 1 byte
const unsigned int addr_TrackerMode_Power = 0x15;             //byte 1 byte
const unsigned int addr_SearchMode_Power = 0x16;              //byte 1 byte
const unsigned int addr_CommandMode_Power = 0x17;             //byte 1 byte
const unsigned int addr_Default_config1 = 0x18;               //byte 1 byte     
const unsigned int addr_ThisNode = 0x19;                      //char 1 byte
const unsigned int addr_RemoteControlNode = 0x1A;             //char 1 byte
const unsigned int addr_ControlledNode = 0x1B;                //char 1 byte
const unsigned int addr_key0 = 0x1C;                          //char 1 byte
const unsigned int addr_key1 = 0x1D;                          //char 1 byte
const unsigned int addr_key2 = 0x1E;                          //char 1 byte
const unsigned int addr_key3 = 0x1F;                          //char 1 byte
const unsigned int addr_west_fence = 0x20;                    //float 4 bytes
const unsigned int addr_east_fence = 0x24;                    //float 4 bytes
const unsigned int addr_south_fence = 0x28;                   //float 4 bytes
const unsigned int addr_north_fence = 0x2C;                   //float 4 bytes
const unsigned int addr_FlightID = 0x30;                      //Character array 16 bytes max

const unsigned int addr_Default_config2 = 0x40;               //byte 1 byte
const unsigned int addr_promiscuous_Mode = 0x41;              //byte 1  byte

const unsigned int addr_EndBindData = 0x4F;                   //marks the end of the Bind data
const unsigned int addr_BindCRC = 0x50;                       //the 16 bit CRC of the current Bind Data, addr_StartBindData to addr_EndBindData
/*********************************************************************
  END bind data 
**********************************************************************/

const unsigned int addr_CalibrationOffset = 0x80;             //int 2 bytes
const unsigned int addr_kelvin_offset = 0x82;                 //unsigned int 2 bytes
const unsigned int addr_conversion_slope = 0x84;              //float 4 bytes
const unsigned int addr_adc_constant = 0x88;                  //unsigned long int 4 bytes
const unsigned int addr_FSKRTTYbaudDelay = 0x8C;              //unsigned int 2 bytes
const unsigned int addr_Sleepsecs  = 0x90;                     //unsigned int 2 bytes
//const unsigned int addr_numSleeps
const unsigned int addr_WaitGPSFixSeconds = 0x92;             //unsigned int 2 bytes
const unsigned int addr_FSKRTTYRegshift = 0x94;               //unsigned int 2 bytes                

const unsigned int addr_FSKRTTYleadin = 0x96;                 //unsigned int 2 bytes

const unsigned int addr_MinsToLost = 0x98;                    //unsigned int 2 bytes
const unsigned int addr_TXDelaySecs = 0x9A;                   //unsigned int 2 bytes 
const unsigned int addr_TXLostDelaySecs = 0x9C;               //unsigned int 2 bytes
const unsigned int addr_pulseerrorlimit = 0x9E;               //unsigned int 2 bytes
const unsigned int addr_holddifference = 0xA0;                //unsigned int 2 bytes  
const unsigned int addr_RCpulseshort = 0xA2;                  //unsigned int 2 bytes 
const unsigned int addr_RCpulselong = 0xA4;                   //unsigned int 2 bytes
const unsigned int addr_GPSerrorLimit = 0xA6;                 //unsigned int 2 bytes
const unsigned int addr_inc_on_error = 0xA8;                  //char 1 byte
const unsigned int addr_dec_on_OK = 0xA9;                     //char 1 byte
const unsigned int addr_FSKRTTYpips = 0xAA;                   //char 1 byte
const unsigned int addr_Default_config3 = 0xAB;               //byte 1 byte
const unsigned int addr_ASKRTTYbaudDelay = 0xAC;              //unsigned int 2 bytes
const unsigned int addr_Default_config4 = 0xAD;               //byte 1byte
const unsigned int addr_Cmd_WaitSecs = 0xAE;                  //byte 1byte

//const unsigned int addr_ResetCount = 0xc0;                   //unsigned long int 4 bytes
//const unsigned int addr_SequenceNum = 0xc4;                  //unsigned long int 4 bytes
//const unsigned int addr_mASecs = 0xc8;                       //unsigned long int 4 bytes

const unsigned int addr_TestLocation_page0 = 0xFF;            //used as a location for read\write tests  
const unsigned int addr_EndConfigData = 0xFF;

const unsigned int addr_ResetCount = 0x100;                   //unsigned long int 4 bytes
const unsigned int addr_SequenceNum = 0x104;                  //unsigned long int 4 bytes
const unsigned int addr_mASecs = 0x108;                       //unsigned long int 4 bytes

const unsigned int addr_TestLocation_page1 = 0x1FF;           //used as a location for read\write tests 
const unsigned int addr_StartHABPayloadData = 0x200;          //for storing last received HAB tracker packet

const unsigned int addr_TestLocation_page2 = 0x2FF;           //used as a location for read\write tests
const unsigned int addr_EndPayloadData = 0x2FF;               //store up to 256 bytes of HAB Packet

//for storing last received GPS co-ordinates from local and remote tracker GPS
const unsigned int addr_StartCoordinateData = 0x300;
const unsigned int addr_TRLat = 0x300;                        //float 4 bytes
const unsigned int addr_TRLon = 0x304;                        //float 4 bytes
const unsigned int addr_TRAlt = 0x308;                        //unsigned int 2 bytes
const unsigned int addr_TRHour = 0x30C;                       //byte 1 byte;  Note times for last tracker co-ordinates come from local GPS time
const unsigned int addr_TRMin = 0x310;                        //byte 1 byte
const unsigned int addr_TRSec = 0x311;                        //byte 1 byte
const unsigned int addr_TRDay = 0x312;                        //byte 1 byte
const unsigned int addr_TRMonth = 0x313;                      //byte 1 byte
const unsigned int addr_TRYear = 0x314;                       //byte 1 byte
const unsigned int addr_LocalLat = 0x318;                     //float 4 bytes
const unsigned int addr_LocalLon = 0x31C;                     //float 4 bytes 
const unsigned int addr_LocalAlt = 0x320;                     //unsigned int 2 bytes
const unsigned int addr_LocalHour = 0x322;                    //byte 1 byte
const unsigned int addr_LocalMin = 0x323;                     //byte 1 byte
const unsigned int addr_LocalSec = 0x324;                     //byte 1 byte
const unsigned int addr_LocalDay = 0x325;                     //byte 1 byte
const unsigned int addr_LocalMonth = 0x326;                   //byte 1 byte
const unsigned int addr_LocalYear = 0x327;                    //byte 1                                      byte
const unsigned int addr_EndCoordinateData = 0x327;

const unsigned int addr_TRlocationCRC = 0x340;                //the 16 bit CRC of the last tracker location data is saved here
const unsigned int addr_LocallocationCRC = 0x342;             //the 16 bit CRC of the last local location data is saved here

const unsigned int addr_TestLocation_page3 = 0x3FF;           //used as a location for read\write tests
const unsigned int addr_EndMemory = 0x3FF;

/*
******************************************************************************************************
  mode definitions - used to define which LoRa mode to use
******************************************************************************************************
*/

#define TrackerMode 1
#define SearchMode 2
#define CommandMode 3
#define BindMode 4

#define Portable_Mode 1                             //used as flag and return values
#define Terminal_Mode 2                             //used as flag and return values





