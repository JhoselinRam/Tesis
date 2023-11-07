#include "Arduino.h"
#include "Wire.h"
#include "MCP4725.h"

/*
  Initialize the I2C buss.
  
  It must be called in the setup function.
*/
void dacBegin(){
  Wire.begin();
  Wire.setWireTimeout();
}

/*
  Writes the provided code to the module registers.

  The code must be an integer between 0 and 4095, failing
  this will lead to an undefined behavior.

  The address can change from module to module. It
  defaults to 0x60, but you can try any of the defined
  values DAC_ADDRESS_0, DAC_ADDRESS_1 or DAC_ADDRESS_2.
*/
void dacWrite(uint16_t code, uint8_t address){
  uint8_t buffer[3] = {DAC_HEADER, code >> 4, code << 4};

  Wire.beginTransmission(address);
  Wire.write(buffer, 3);
  Wire.endTransmission();
}