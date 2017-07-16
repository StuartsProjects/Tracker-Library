//Internal_CPU.h
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
  
This Program uses either and external voltage divider and temperature sensor  or  some internal processor 'tricks' to read the
CPU supply voltage and temperature, needs calibrating for each particular CPU.    
  
To Do:
  
*******************************************************************************************************************************
*/


long read_SupplyVoltage();
void print_SupplyVoltage();
float read_Temperature();
void print_Temperature();



#ifdef CPU_VoltageRead
long read_SupplyVoltage()
{
long result;                                           //use 1V1 ref
ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
delay(10);                                             //wait for ref to be stable 
ADCSRA |= _BV(ADSC);  
while (bit_is_set(ADCSRA,ADSC));                       //wait for conversion
result = ADCL; 
result |= ADCH<<8;
result = adc_constant / result;                        //calculate VCC reading in mV
return result;
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
  //Internal temperature uses the internal 1v1 reference.
  unsigned int wADC;
  float temp;
  
  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));       //set the internal reference and mux
  ADCSRA |= _BV(ADEN);                                 //enable the ADC

  delay(20);                                           //wait for voltages to be stable.

  ADCSRA |= _BV(ADSC);                                 //Start ADC
  
  while (bit_is_set(ADCSRA,ADSC));                     //wait for conversion

  wADC = ADCW;                                         //read the result, low and high

  temp = (wADC - kelvin_offset ) / (temp_conversion_slope);   //use the kelvin_offset to convert to centigrade, slope scales reading


 return (temp);                                        //return temp as float
}


void print_Temperature()
{
Serial.print(F("Temperature "));
Serial.print(read_Temperature(),1);
Serial.println(F("C"));
}
#endif



#ifdef External_VoltageRead
long read_SupplyVoltage()
{
  //relies on 1V1 internal reference and 91K & 11K resistor divider
  //returns supply in mV @ 10mV per AD bit read
  int SupplyVolts, temp;
  byte index;
  
  SupplyVolts = 0;
  
  analogReference(INTERNAL);
  for (index = 0; index <= 4; index++)                      //sample AD 3 times
  {
    temp = analogRead(SupplyAD);
    SupplyVolts = SupplyVolts + temp;
  }
  SupplyVolts = (int) ((SupplyVolts / 5) * ADMultiplier);
  return SupplyVolts;
}


void print_SupplyVoltage()
{
  //get and display supply volts on terminal or monitor
  Serial.print(F("Supply Volts "));
  Serial.print((int) read_SupplyVoltage());
  Serial.println(F("mV"));
}
#endif


#ifdef External_TemperatureRead
float read_Temperature()
{
//nothing to do
}
void print_Temperature()
{
//nothing to do
}
#endif

