#include "Arduino.h"
#include "HYSFR05.h"

/*
  Set the correct pin mode of the
  HY-SRF05 trigger and echo pins.
*/
void ultrasonic_begin(){
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIGGER_PIN, LOW);
}


/*
  Reads the travel time of the wave 
  sent in microseconds (us)

  To obtain the distance, this value
  must be multiplied by the sound speed
  and divided by 2.
*/
unsigned long ultrasonic_read(){
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  return pulseIn(ECHO_PIN, HIGH, MAX_TIME + 1);
}