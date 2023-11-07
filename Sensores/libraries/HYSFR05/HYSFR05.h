/*
  This module exposes two simple functions to read the output
  of the MY-SFR05 module.

  These functions are meant to be used only on this project,
  so only the bare minimal functionality is provided.

  The TRIGGER and ECHO pins cannot be changed, and the 
  read function only gets the raw data, not the actual 
  distance.

  Author: Jhoselin Adrian Ramirez Montes
  Contact: jhoselin.ramirez92@gmail.com
*/

#ifndef __HYSFR05_H__
#define __HYSFR05_H__

#define MAX_RANGE 1000 // 1000mm = 1m
#define AIR_TEMPERATURE 22 //Celcius
#define SOUND_SPEED ((331.3+0.606*(AIR_TEMPERATURE))/1000.0) //Speed in mm/us
#define MAX_TIME uint32_t(((MAX_RANGE)/(SOUND_SPEED)*2)) // The maximum time expected given MAX_RANGE

#define TRIGGER_PIN 3
#define ECHO_PIN 2

void ultrasonic_begin();
unsigned long ultrasonic_read();

#endif