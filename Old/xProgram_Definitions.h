//Program_Definitions.h
/*
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



/*
**************************************************************************************************
  LoRa Static definitions
**************************************************************************************************
*/

//Constant names for bandwidth settings
const byte BW7800 = 0;      //7.8khz
const byte BW10400 = 16;    //10.4khz
const byte BW15600 = 32;    //15.6khz
const byte BW20800 = 48;    //20.8khz
const byte BW31200 = 64;    //31.2khz
const byte BW41700 = 80;    //41.7khz
const byte BW62500 = 96;    //62.5khz
const byte BW12500 = 112;   //125khz
const byte BW250000 = 128;  //250khz
const byte BW500000 = 144;  //500khz

//Constant names for Spreading Factors
const byte SF6 = 6;
const byte SF7 = 7;
const byte SF8 = 8;
const byte SF9 = 9;
const byte SF10 = 10;
const byte SF11 = 11;
const byte SF12 = 12;

//Constant names for coding rate settings
const byte CR45 = 2; //4:5
const byte CR46 = 4; //4:6
const byte CR47 = 6; //4:7
const byte CR48 = 8; //4:8

//Constant names for LoRa Header Settings
const byte Explicit    = 0;  //Use to set explicit header
const byte Implicit    = 1;  //Use to set implicit header

//Miscellaneous definitions
const byte Deviation = 0x52;
const byte LowDoptON = 0x08;    //value to turn low data rate optimization on
const byte LowDoptOFF = 0x00;   //value to turn low data rate optimization off
const byte PrintASCII = 0;      //value to cause buffer print to appear as ASCII
const byte PrintDecimal = 1;    //value to cause buffer print to appear as decimal numbers
const byte PrintHEX = 2;        //value to cause buffer print to appear as hexadecimal numbers
const byte Strip = 1;           //value for setting stip of addressing information on packet
const byte NoStrip = 0;         //value for sending addressing information as part of packet
const byte TXdefaultpower = 10; //default power value for transmitter


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



#ifdef HABTracker5
#define lora_DIO0 2                  //pin connected to DIO0 on LoRa device
#define lora_DIO5 3                  //pin connected to DIO5 on LoRa device
#define lora_DIO3 4                  //pin connected to DIO3 on LoRa device
#define lora_DIO1 5                  //pin connected to DIO1 on LoRa device
#define lora_DIO2 6                  //pin connected to DIO2 on LoRa device
#define lora_TonePin 6               //pin number for radio tone generation, connects to LoRa device pin DIO2
#define lora_DIO4 7                  //pin connected to DIO4 on LoRa device
#define LED1 8                       //pin number for LED on Tracker
#define WDI 8                        //pin for using a watchdog device
#define lora_NReset 9                //pin where LoRa device reset line is connected
#define lora_NSS 10                  //pin number where the NSS line for the LoRa device is connected
#define LED2 13                      //pin number for standard LED on pin 13 of Pro Mini

#define GPSPOWER -1                    //pin controls power to GPS
#define GPSBACKUP -1                  //use for GPS backup power
#define CON2_1 -1                     //connected to CON2 pin 1 on external header
#define SupplyAD A0                   //pin for supply AD
#define TimePulse A1                   //For reading the GPS timepulse signal
#define GPSTX A2                      //pin number for TX output - RX into GPS
#define GPSRX A3                      //pin number for RX input - TX from GPS
#define RCPulse -1                    //unused pin
#define DisplayTX -1                  //unused pin
#define MEMORY_CS -1                  //unused pin          

#define GPSBaud 9600                  //GPS baud rate
#define ADMultiplier 10               //multiplier for supply volts calculation
#endif


#ifdef LoRaLMLV4
#define lora_DIO0 2                  //pin connected to DIO0 on LoRa device
#define lora_DIO5 3                  //pin connected to DIO5 on LoRa device
#define lora_DIO3 4                  //pin connected to DIO3 on LoRa device
#define lora_DIO1 5                  //pin connected to DIO1 on LoRa device
#define lora_DIO2 6                  //pin connected to DIO1 on LoRa device
#define lora_TonePin 6               //pin number for radio tone generation, connects to LoRa device pin DIO2
#define GPSPOWER 7                   //pin controls power to GPS
#define WDI 8                        //pin for using a watchdog device
#define LED1 8                       //pin number for LED on Tracker
#define lora_NReset 9                //pin where LoRa device reset line is connected
#define lora_NSS 10                   //pin number where the NSS line for the LoRa device is connected
#define SupplyAD A0                   //pin for supply AD
#define RCPulse A1                    //pin used to read RC pulse
#define GPSTX A2                      //pin number for TX output - RX into GPS
#define GPSRX A3                      //pin number for RX input - TX from GPS

#define GPSBaud 9600                  //GPS baud rate
#define ADMultiplier 10               //multiplier for supply volts calculation

#include <SoftwareSerial.h>
SoftwareSerial GPSserial(GPSRX, GPSTX);     //Create the serial connection to the GPS device

#endif



#ifdef PIHTracker3
#define lora_DIO0 2                  //pin connected to DIO0 on LoRa device
#define Audio_Out 3                  //pin number for external tone generation
#define lora_TonePin 4               //pin number for radio tone generation, connects to LoRa device pin DIO2
#define WDI 5                        //pin for using a watchdog device
#define Switch1 6                    //pin for switch input
#define lora_NSS 8                   //pin number where the NSS line for the LoRa device is connected
#define lora_NReset 9                //pin where LoRa device reset line is connected
#define LED1 10                      //pin number for LED on Tracker
#define LED2 13                      //pin number for standard LED on pin 13 of Pro Mini

#define GPSPOWER 7                    //pin controls power to GPS
#define GPSBACKUP A1                  //use for GPS backup power
#define CON2_1 A1                     //connected to CON2 pin 1 on external header
#define GPSTX A2                      //pin number for TX output - RX into GPS
#define GPSRX A3                      //pin number for RX input - TX from GPS
#define RCPulse A4                    //pin used to read RC pulse
#define DisplayTX A5                  //soft serial TX pin for Digole Serial LCD
#define SupplyAD A0                   //pin for supply AD
#define TimePulse 3                   //For reading the GPS timepulse signal

#define GPSBaud 9600                  //GPS baud rate
#define ADMultiplier 10               //multiplier for supply volts calculation
#endif


#ifdef PIHTracker2
#define lora_DIO0 2                   //pin connected to DIO0 on LoRa device
#define Audio_Out 3                   //pin number for external tone generation
#define lora_TonePin 4                //pin number for radio tone generation, connects to LoRa device pin DIO2
#define WDI 5                         //pin for using a watchdog device
#define Switch1 6                     //pin for switch input
#define lora_NSS 8                    //pin number where the NSS line for the LoRa device is connected
#define lora_NReset 9                 //pin where LoRa device reset line is connected
#define LED1 10                       //pin number for LED on Tracker
#define LED2 13                       //pin number for standard LED on pin 13 of Pro Mini

#define GPSPOWER A0                   //pin controls power to GPS
#define CON2_1 A1                     //connected to CON2 pin 1 on external header
#define GPSTX A2                      //pin number for TX output - RX into GPS
#define GPSRX A3                      //pin number for RX input - TX from GPS
#define RCPulse A4                    //pin used to read RC pulse
#define DisplayTX A5                  //soft serial TX pin for Digole Serial LCD
#define SupplyAD A7                   //pin for supply AD

#define GPSBaud 9600                  //GPS baud rate
#define ADMultiplier 10               //multiplier for supply volts calculation
#endif


#ifdef Relay
#define lora_DIO0 2                   //pin connected to DIO0 on LoRa device
#define Switch1 3                     //pin for switch
#define lora_DIO5 4                   //pin connected to DIO5 on LoRa device
#define RCPulse 5                     //pin used to read RC pulse
#define lora_DIO2 6                   //pin connected to DIO2 on LoRa device
#define lora_TonePin 6                //pin connected to DIO2 on LoRa device
#define lora_DIO1 7                   //pin connected to DIO1 on LoRa device
#define lora_DIO4 8                   //pin connected to DIO4 on LoRa device
#define lora_DIO3 9                   //pin connected to DIO3 on LoRa device
#define lora_NSS 10                   //pin number where the NSS line for the LoRa device is connected
#define LED2 13                       //pin number for standard LED on pin 13 of Pro Mini

#define lora_NReset A0                //pin where LoRa device reset line is connected
#define SupplyAD A1                   //pin for supply AD
#define WDI A2                        //pin for using a watchdog device
#define LED1 A3                       //pin number for LED on Tracker
#define GPSTX A4                      //pin number for TX output - RX into GPS
#define GPSRX A5                      //pin number for RX input - TX from GPS
#define Audio_Out A7                  //Unused pin
#define GPSPOWER A7                   //Unused pin
#define GPSBaud 9600                  //GPS baud rate
#define ADMultiplier 10               //multiplier for supply volts calculation
#endif


/*********************************************************************************************************
* Start MikrobusShieldV3 Definitions 
/**********************************************************************************************************
*/
#ifdef MikrobusShieldV3                 //third version of Mikrobus Shield, smaller simpler layout with 2 Mikrobus sockets
#define MB2_INT  2
#define MB1_INT  3
#define MB1_CS  4
#define MB2_PWM  5
#define MB1_PWM  6
#define Bluetooth_STATE 7
#define MB2_CS  9
#define SD_CS  10
#define SWITCH1 11
#define AUDIO_OUT  12
#define INT_OUT  13
#define LED2  13
#define ESP01_RX  14
#define ESP01_TX  15
#define MB1_TX  16
#define MB1_RX  17
#define MB2_TX  18
#define MB2_RX  19
#define SDA  20
#define SCL  21
#define GPSPOWER  22
#define CON_EXP_DIG1  23
#define CON_EXP_DIG2  24
#define CON_EXP_DIG3  25
#define CON_EXP_DIG4  26
#define CON_EXP_DIG5  27
#define MEMORY_CS  28
#define MB2_RESET  29
#define LED1 30
#define LED3 31
#define GPSLED 31
#define BUZZ 32
#define DISP_LED 33

#define UNUSEDPIN 53
#define MB1_RESET UNUSEDPIN             //so use of pin is ignored
#define CON_EXP_AN1  A0
#define MB2_AN  A1
#define MB1_AN  A2
#define CON_EXP_AN2  A3
#define WDI  A4
#define DISP_DC  A5
#define DISP_RESET  A6
#define DISP_CS A7
#define Bluetooth_RX A8
#define Bluetooth_TX A9
#define SWITCH_U 64 //A10
#define SWITCH_D 65 //A11
#define SWITCH_R 66 //A12
#define SWITCH_L 67 //A13
#define ESP01_CHPD 68
#define ESP01_RESET 69

//#define MB1Serial Serial2             //this works too HardwareSerial & MKB1_Serial = Serial2;
//#define MB2Serial Serial1

#ifdef GPS_in_MB1
#define GPSSerial Serial2
#endif

#ifdef GPS_in_MB2
#define GPSSerial Serial1
#endif

#endif
/*********************************************************************************************************
* End MikrobusShieldV3 Definitions 
/**********************************************************************************************************
*/



#ifdef MikrobusShield1284P    //1284P version of Mikrobus Shield, smaller simpler layout with 2 Mikrobus sockets
#define RXD 0
#define TXD 1
#define MB2_RX  2
#define MB2_TX  3
#define MB1_CS  4
#define DISP_DC  5
#define SWITCH1 6
#define DISP_RESET 7

#define MB2_PWM  8
#define MB2_CS  9
#define SD_CS  10
#define MOSI  11
#define MIS0  12
#define SCK  13

#define SCL  22
#define SDA  23
#define MB1_RX  24
#define MB1_TX  25
#define Bluetooth_RX  26
#define Bluetooth_TX  27
#define MB2_INT 28
#define MB1_INT2 29
#define MB1_PWM  30 //same as LED2
#define LED2  30  //hardware pin 18 
#define LED1 31   //hardware pin 21
#define WDI 31

#define BAT  A0
#define MB1_AN A1
#define MB2_AN A2
#define BUZZ A3
#define MB1_RESET A4
#define DISP_CS A5
#define SWITCH2 A6
#define MB1_INT  A7

#define GPSPOWER -1           //not used
#define LED3 -1                //not used
#define SWITCH_L -1           //not used  
#define SWITCH_R -1           //not used 
#define SWITCH_U -1           //not used 
#define SWITCH_D -1           //not used 
#define MEMORY_CS -1         //not used

#ifdef GPS_in_MB1
//#define GPSSerial Serial1
#endif

#ifdef GPS_in_MB2
#define GPSserial Serial1
#endif

#ifdef LoRa_Device_in_MB1                 //we will have the LoRa device in MB1
#define lora_TonePin MB1_PWM
#define lora_NReset MB1_RESET
#define lora_NSS MB1_CS
#define lora_DIO0 MB1_INT
#endif

#ifdef LoRa_Device_in_MB2                 //we will have the LoRa device in MB1
#define lora_TonePin MB2_PWM
#define lora_NReset -1
#define lora_NSS MB2_CS
#define lora_DIO0 MB2_INT
#endif


#endif


#ifdef MikrobusShield2560    //2560 version of Mikrobus Shield, smaller simpler layout with 2 Mikrobus sockets
#define SWITCH1 2
//#define SWITCH1_IN 2
#define MB1_INT 3
#define MB1_CS  4
#define MB1_RESET 5
#define MB1_PWM 6
#define LED2 6
#define MB2_PWM 7

#define WDI 8
#define MB2_CS  9
#define SD_CS  10
#define DISP_CS 11
#define MB1_DIG2 12
#define LED1  13

#define MB2_TX  14
#define MB2_RX  15
#define Bluetooth_TX  16
#define Bluetooth_RX  17
#define MB1_TX  18
#define MB1_RX  19
#define SDA 20
#define SCL 21

#define BAT  A0
#define MB1_AN A1
#define MB2_AN A2
#define MB1_AN2 A3
#define DISP_DC A4
#define DISP_RESET A5
#define Buzzer A6

#define MB1_INT2 A8
#define MB2_INT A9
#define SWITCH_U A10
#define SWITCH_L A11
#define SWITCH_R A12
#define SWITCH_D  A13
#define MB1_DIG3 A14
#define MB1_DIG1 A15
#define GPSPOWER -1     //pin not used
#define MEMORY_CS -1    //pin not used
#define LED3 -1         //pin not used

#ifdef GPS_in_MB1
#define GPSSerial Serial1
#endif

#ifdef GPS_in_MB2
#define GPSSerial Serial3
#endif


#ifdef LoRa_Device_in_MB1                 //we will have the LoRa device in MB1
#define lora_TonePin MB1_PWM
#define lora_NReset MB1_RESET
#define lora_NSS MB1_CS
#define lora_DIO0 MB1_INT
#endif

#ifdef LoRa_Device_in_MB2                 //we will have the LoRa device in MB1
#define lora_TonePin MB2_PWM
#define lora_NReset -1
#define lora_NSS MB2_CS
#define lora_DIO0 MB2_INT
#endif


#endif



/*
/#ifdef LoRa_Device_in_MB1                 //we will have the LoRa device in MB1
#define lora_TonePin MB1_PWM
#define lora_NReset MB1_RESET
#define lora_NSS MB1_CS
#define lora_DIO0 MB1_INT
#endif

#ifdef LoRa_Device_in_MB2                 //we will have the LoRa device in MB1
#define lora_TonePin MB2_PWM
#define lora_NReset MB2_RESET
#define lora_NSS MB2_CS
#define lora_DIO0 MB2_INT
#endif
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
const char IsLost = 'H';                  //packet to notify of lost status (Help)
const char Info = 'i';                    //binary info packet
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
const char SearchEnable = 0;         //bit num to set in config byte to enable search mode packet
const char TXEnable = 1;             //bit num to set in config byte to enable transmissions
const char FSKRTTYEnable = 2;        //bit num to set in config byte to enable FSK RTTY
const char CheckFence = 3;           //bit number to control whether fence is checked 0 = NoCheck
const char DozeEnable = 4;          //bit num to set in config byte to put tracker in Doze mode
const char AddressStrip = 6;         //bit number to control address part of payload, 1 to strip, 0 to allow
const char GPSPowerSave = 7;         //bit when set enables GPS power save.


//Status byte settings
const char GPSFix = 0;               //flag bit number to indicate GPS fix
const char GLONASSisoutput = 1;      //flag bit number to indicate GLONASS found
const char NoGPSTestMode = 7;        //flag bit number to indicate tracker in no GPS test mode

const byte wait_command = 3;         //base time in seconds to wait for command
const byte runmA = 4;                //processor run current
const byte GPSmA = 22;               //GPS average current when aquiring fix
const byte RXmA = 11;                //LoRa device receive current
const byte TXmA = 40;                //LoRa device transmit current 10dBm
//const int  GPSShutdownTimemS = 1900; //Software backup mode takes around 1.9secs to power down
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
  adressing information for variables stored in Memory
  This is kept to 512 bytes of storage.
  First 256 bytes is program configuration data and settings
  Second 256 bytes is for storing location data, HAB packets etc.
  The bind data is from addr_StartBindData to addr_EndBindData
  
  0x00 to addr_EndBindData = bind data
  0x80 to 0xFF  general program data
  0x100 + = counters that need to survive reset
  0x200 + last HAB format packet
  0x300 + last received GPS co-ordinates, local and tracker
  ******************************************************************************************************
*/
/*********************************************************************
  Start bind data is from addr_StartBindData to addr_EndBindData
**********************************************************************/

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

const unsigned int addr_EndConfigData = 0xFF;

const unsigned int addr_ResetCount = 0x100;                   //unsigned long int 4 bytes
const unsigned int addr_SequenceNum = 0x104;                  //unsigned long int 4 bytes
const unsigned int addr_mASecs = 0x108;                       //unsigned long int 4 bytes

const unsigned int addr_StartHABPayloadData = 0x200;          //for storing last received HAB tracker packet
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


//#define OptionOff 0
//#define OptionOn 1
//#define Strip 1
//#define NoStrip 0







