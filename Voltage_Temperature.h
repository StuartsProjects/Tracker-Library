//Voltage_Temperature.h
/*
*******************************************************************************************************************************
  Easy Build Tracker Programs for Arduino

  Copyright of the author Stuart Robinson - 2/10/17

  

  These programs may be used free of charge for personal, recreational and educational purposes only.

  This program, or parts of it, may not be used for or in connection with any commercial purpose without the explicit permission
  of the author Stuart Robinson.

  The programs are supplied as is, it is up to individual to decide if the programs are suitable for the intended purpose and
  free from errors.

  This Program uses either and external voltage divider and temperature sensor  or  some internal processor 'tricks' to read the
  CPU supply voltage and temperature, each particular CPU needs calibrating.

  To Do:
  Check that external temperature reading works on HAB2 Software 

*******************************************************************************************************************************
*/


unsigned int read_SupplyVoltage();
void print_SupplyVoltage();
float read_Temperature();
void print_Temperature();

//#define TC74_Address 0x4c                      //init with TC74 address, can be 0x48 to 0x4F depending on specific type

#ifdef External_TemperatureRead
#include <TC74_I2C.h>                          //https://github.com/Mario-H/TC74_I2C/blob/master/LICENSE.md
TC74_I2C TC74(TC74_Address);                   //init with TC74 address from settings file
#endif


#ifdef CPU_VoltageRead
unsigned int read_SupplyVoltage()
{
  unsigned long result;                                  //use 1V1 ref
  unsigned int temp;
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(10);                                             //wait for ref to be stable
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC));                      //wait for conversion
  result = ADCL;
  result |= ADCH << 8;
  temp = (unsigned int) (adc_constant / result);
  return temp;
}


void print_SupplyVoltage()
{
  //for the internal VCC read
  Serial.print(F("VCC "));
  Serial.print(read_SupplyVoltage());
  Serial.println(F("mV"));
}
#endif


#ifdef CPU_TemperatureRead
float read_Temperature()
{
  //Internal temperature uses the internal 1V1 reference.
  unsigned int wADC;
  float temp;

  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));       //set the internal reference and mux
  ADCSRA |= _BV(ADEN);                                 //enable the ADC
  delay(20);                                           //wait for voltages to be stable.
  ADCSRA |= _BV(ADSC);                                 //Start ADC

  while (bit_is_set(ADCSRA, ADSC));                    //wait for conversion

  wADC = ADCW;                                         //read the result, low and high
  temp = (wADC - kelvin_offset ) / (temp_conversion_slope);   //use the kelvin_offset to convert to centigrade, slope scales reading

  return temp;                                          //return temp as float
}


void print_Temperature()
{
  Serial.print(F("Temperature "));
  Serial.print(read_Temperature(), 1);
  Serial.println(F("C"));
}
#endif



#ifdef External_VoltageRead
unsigned int read_SupplyVoltage()
{
  //relies on 1V1 internal reference and 91K & 11K resistor divider
  //returns supply in mV @ 10mV per AD bit read
  unsigned int temp, SupplyVolts;
  byte index;


  analogReference(INTERNAL);
  
  temp = analogRead(SupplyAD);                              //first reading after setting reference often not accurate                      
  delay(10);
  
  for (index = 0; index <= 4; index++)                      //sample AD 5 times
  {
    temp = analogRead(SupplyAD);
    SupplyVolts = SupplyVolts + temp;
  }
  SupplyVolts = ((SupplyVolts / 5) * ADMultiplier);
  return SupplyVolts;
}


void print_SupplyVoltage()
{
  //get and display supply volts on terminal or monitor
  Serial.print(F("Supply Volts "));
  Serial.print(read_SupplyVoltage());
  Serial.println(F("mV"));
}
#endif



#ifdef External_TemperatureRead

float read_Temperature()
{
  float temperature;
  TC74.Init();
  TC74.NoPowersave();                        //turn off powesave mode
  temperature = (float) TC74.ReadTemp();
  TC74.Powersave();                           //put TC74 in low current mode, approx 5uA
  return temperature;
}


void print_Temperature()
{
  float temp = read_Temperature() + Temperature_Adjust;
  Serial.print(F("Temperature "));
  Serial.print(temp,0);
  Serial.print(F("C"));
}
#endif

