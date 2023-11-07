/*
  This module exposes two simple functions to set the output
  voltage of the MCP4725 module.

  The functions are minimal, so no class nor data validation 
  are provided.

  Author: Jhoselin Adrian Ramirez Montes
  Contact: jhoselin.ramirez92@gmail.com
*/

#ifndef __MCP4725_H__
#define __MCP4725_H__

// Module posible address.
#define DAC_ADDRESS_0 0x60
#define DAC_ADDRESS_1 0x61
#define DAC_ADDRESS_2 0x62

// Header use to write into the MCP4725 registers
#define DAC_HEADER 0x40

void dacBegin();
void dacWrite(uint16_t code, uint8_t address = DAC_ADDRESS_0);

#endif