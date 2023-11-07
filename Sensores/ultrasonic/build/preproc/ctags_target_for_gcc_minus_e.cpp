# 1 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
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
# 17 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
# 18 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino" 2
# 19 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino" 2



//-------- DAC CALIBRATION ---------//


//----------------------------------//
//----------------------------------//


//----------- TIMEOFF --------------//

//----------------------------------//
//----------------------------------//


//--------- FREQ TEST PIN ----------//

//----------------------------------//
//----------------------------------//







//------------------ FILTERS -------------------//
//----------------------------------------------//


//--- NO FILTER (not recommended)---//
  //#define NO_FILTER
//----------------------------------//


//--------- MOVING AVERAGE ---------//


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
void setup(){
  dacBegin();
  ultrasonic_begin();
  pinMode(8, 0x1);
  data_read = 0;
  current_time = millis();
  Serial.begin(115200);
}


void loop(){
  if(millis() - current_time > 20){
    current_time = millis();

    
# 100 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino" 3
   (*(volatile uint8_t *)((0x05) + 0x20)) 
# 100 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
         = 1; // digitalWrite(FREQ_TEST_PIN, HIGH)




      data_read = moving_average();
# 114 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
    to_voltage(data_read);

    
# 116 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino" 3
   (*(volatile uint8_t *)((0x05) + 0x20)) 
# 116 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
         = 0; // digitalWrite(FREQ_TEST_PIN, LOW)

  }
}
//----------------------------------//
//----------------------------------//





//----- FILTER IMPLEMENTATIONS -----//
//----------------------------------//
# 137 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
uint32_t average_buffer[15] = {0};
uint8_t cursor = 0;

unsigned long moving_average(){
  uint32_t average = 0;

  average_buffer[cursor % 15] = ultrasonic_read();

  for(uint8_t i=0; i<15; i++){
    average += average_buffer[i];
  }

  average /= 15;
  cursor++;

  return average;
}
# 167 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/ultrasonic.ino"
//----------------------------------//
//----------------------------------//




//----------- TO VOLTAGE -----------//

void to_voltage(unsigned long data){
  uint16_t real_code = clamp(map(data, 0, uint32_t(((1000 /* 1000mm = 1m*/)/(((331.3+0.606*(22 /*Celcius*/))/1000.0) /*Speed in mm/us*/)*2)) /* The maximum time expected given MAX_RANGE*/, 0, 4095), 105, 4014);
  uint16_t calibrated_code = map(real_code, 105, 4014, 100, 4000);
  Serial.println(calibrated_code);
  dacWrite(calibrated_code, 0x60);


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
