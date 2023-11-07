#include <Arduino.h>
#line 1 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
/*
  Main script for this proyect ultrasonic sensor.

  It uses the HY-SFR05 ultrasonic module, but it can be
  easily replaced with HC-SR04.
  
  And the MCP4725 12 bit DAC to encode the distance read
  into an analog voltage.


  Refer the README file to learn more.

  Author: Jhoselin Adrian Ramirez Montes
  Contact: jhoselin.ramirez92@gmail.com
*/

#include "MCP4725.h"
#include "HYSFR05.h"



//-------- DAC CALIBRATION ---------//
#define DAC_MIN_CODE 105
#define DAC_MAX_CODE 4014
//----------------------------------//
//----------------------------------//


//----------- TIMEOFF --------------//
#define SAFE_TIMEOFF 20
//----------------------------------//
//----------------------------------//


//--------- FREQ TEST PIN ----------//
#define FREQ_TEST_PIN 8
//----------------------------------//
//----------------------------------//







//------------------ FILTERS -------------------//
//----------------------------------------------//


//--- NO FILTER (not recommended)---//
  //#define NO_FILTER
//----------------------------------//


//--------- MOVING AVERAGE ---------//
  #define MOVING_AVERAGE
  #define MOVING_AVERAGE_TABS 15
//----------------------------------//


//--------- COMPLEMENTARY ----------//
  //#define COMPLEMENTARY
  //#define COMPLEMENTARY_GAIN 0.485
//----------------------------------//


//----- FINITE IMPULSE RESPONSE ----//
  //#define FIR
  //#define FIR_ORDER 10
//----------------------------------//


//----------------------------------------------//
//----------------------------------------------//






unsigned long current_time;
unsigned long data_read;

//-------- MAIN FUNCTIONS ----------//
//----------------------------------//
#line 86 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
void setup();
#line 96 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
void loop();
#line 140 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
unsigned long moving_average();
#line 175 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
void to_voltage(unsigned long data);
#line 202 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
uint16_t clamp(uint16_t number, uint16_t min, uint16_t max);
#line 86 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
void setup(){
  dacBegin();
  ultrasonic_begin();
  pinMode(FREQ_TEST_PIN, OUTPUT);
  data_read = 0;
  current_time = millis();
  Serial.begin(115200);
}


void loop(){
  if(millis() - current_time > SAFE_TIMEOFF){
    current_time = millis();
    
    PORTB = B00000001;  // digitalWrite(FREQ_TEST_PIN, HIGH)

    #ifdef NO_FILTER
      data_read = no_filter();
    #elif defined(MOVING_AVERAGE)
      data_read = moving_average();
    #elif defined(COMPLEMENTARY)
      data_read = complementary();
    #elif defined(FIR)
      data_read = fir();
    #endif



    to_voltage(data_read);

    PORTB = B00000000;  // digitalWrite(FREQ_TEST_PIN, LOW)

  }
}
//----------------------------------//
//----------------------------------//





//----- FILTER IMPLEMENTATIONS -----//
//----------------------------------//

#ifdef NO_FILTER
unsigned long no_filter(){
  return ultrasonic_read();
}
#endif

#ifdef MOVING_AVERAGE
uint32_t average_buffer[MOVING_AVERAGE_TABS] = {0};
uint8_t cursor = 0;

unsigned long moving_average(){
  uint32_t average = 0;

  average_buffer[cursor % MOVING_AVERAGE_TABS] = ultrasonic_read();

  for(uint8_t i=0; i<MOVING_AVERAGE_TABS; i++){
    average += average_buffer[i];
  }  

  average /= MOVING_AVERAGE_TABS;
  cursor++;

  return average;
}
#endif

#ifdef COMPLEMENTARY
uint32_t last_read = 0;

uint32_t complementary(){
  uint32_t read = ultrasonic_read();

  last_read += COMPLEMENTARY_GAIN * (long(read) - long(last_read));
  
  return last_read;
}
#endif
//----------------------------------//
//----------------------------------//




//----------- TO VOLTAGE -----------//

void to_voltage(unsigned long data){
  uint16_t real_code = clamp(map(data, 0, MAX_TIME, 0, 4095), DAC_MIN_CODE, DAC_MAX_CODE);
  uint16_t calibrated_code = map(real_code, DAC_MIN_CODE, DAC_MAX_CODE, 100, 4000);
  Serial.println(calibrated_code);
  dacWrite(calibrated_code, DAC_ADDRESS_0);


  // float distance = 0.5 * SOUND_SPEED * data;
  // float voltage = distance / 1000 * 5;
  // uint16_t _real_code = voltage * 4095 / 5;
  // uint16_t _code = map(_real_code, DAC_MIN_CODE, DAC_MAX_CODE, 100, 4000);

  // Serial.print(distance);
  // Serial.print("\t");
  // Serial.print(voltage);
  // Serial.print("\t");
  // Serial.print(_real_code);
  // Serial.print("\t");
  // Serial.print(real_code);
  // Serial.print("\t");
  // Serial.print(_code);
  // Serial.print("\t");
  // Serial.println(calibrated_code);
}

//----------------------------------//
//----------------------------------//
uint16_t clamp(uint16_t number, uint16_t min, uint16_t max){
  return number < min ? min : number > max ? max : number;
}
//----------------------------------//
