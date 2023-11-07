/*
  Script to calibrate the MCP4725 12 bit DAC module.
  Refer to the README file for the instructions.

  Author: Jhoselin Adrian Ramirez Montes
  Contact: jhoselin.ramirez92@gmail.com
*/



#include <math.h>
#include "MCP4725.h"

#define DATA_POINTS 11 //Do NOT change

//----------------------------------//
//----------- TEST CODES -----------//
  uint16_t code = 100;
  //uint16_t code = 490;
  //uint16_t code = 880;
  //uint16_t code = 1270;
  //uint16_t code = 1660;
  //uint16_t code = 2050;
  //uint16_t code = 2440;
  //uint16_t code = 2830;
  //uint16_t code = 3220;
  //uint16_t code = 3610;
  //uint16_t code = 4000;
//----------------------------------//
//----------------------------------//


//----------------------------------//
//--------- OUTPUT VOLTAGE ---------//
float output_voltage[DATA_POINTS] = {
  0.13, // code 100
  0.60, // code 490
  1.08, // code 880
  1.56, // code 1270
  2.04, // code 1660
  2.52, // code 2050
  3.00, // code 2440
  3.47, // code 2830
  3.95, // code 3220
  4.43, // code 3610
  4.89  // code 4000
};
//----------------------------------//
//----------------------------------//



//----------------------------------//
//  Uncoment this definition to 
//  compute, show and use the 
//  calibration.
//----------------------------------//

  #define TEST_CALIBRATION

//----------------------------------//




//----------------------------------//
//---------- SETUP FUNCTON ---------//
uint16_t codes_used[DATA_POINTS];

void setup(){
  uint16_t max_code;
  uint16_t min_code;
  uint16_t calibrated_code;
  float regression[3];
  double m;  //Slope
  double b;  //Intercept
  double r;  //Correlation

  //Initialize the I2C bus
  dacBegin();

  //Only set the code into the DAC while measuring its real response.
  #ifndef TEST_CALIBRATION

  dacWrite(code, DAC_ADDRESS_0);

  #else
  
  Serial.begin(115200);

  //Fill the codes_used array [100, 490, 880, ... , 4000]
  for(uint8_t i=0; i<DATA_POINTS; i++){
    codes_used[i] = 100 + i*390;
  }

  //Compute the linear regression
  getLinearRegression(regression);
  m = regression[0];
  b = regression[1];
  r = regression[2];

  //Compute the min and max codes 
  min_code = (m*codes_used[0]+b)*4095/5;
  max_code = (m*codes_used[DATA_POINTS-1]+b)*4095/5;

  //Test the calibration
  calibrated_code = map(code, min_code, max_code, 100, 4000);
  dacWrite(calibrated_code, DAC_ADDRESS_1);

  //Pint to calibration information into the serial monitor
  printCalibration(regression, min_code, max_code);
  #endif
  
}
//----------------------------------//
//----------------------------------//


//----------------------------------//
//----- LOOP FUNCTION (unused) -----//
void loop(){}
//----------------------------------//



//------- UTILITY FUNCTIONS --------//

//----------------------------------//
void getLinearRegression(float buffer[3]){
  // 'x' => codes, 'y' => voltage
  double sum_x = 0;
  double sum_y = 0;
  double sum_xy = 0;
  double sum_x2 = 0;
  double avg;     //Average of 'y' values
  double ssr = 0; //Sum Squared errors Residual
  double sst = 0; //Sum Squared error Total
  double m;  //Slope
  double b;  //Intercept
  double r;  //Correlation

  //Computes the parameters used in the linear interpolation
  for(uint8_t i=0; i<DATA_POINTS; i++){
    sum_x += codes_used[i];
    sum_y += output_voltage[i];
    sum_xy += codes_used[i] * output_voltage[i];
    sum_x2 += pow(codes_used[i], 2);
  }

  //Computes the actual interpolation
  m = (DATA_POINTS*sum_xy - sum_x*sum_y) / (DATA_POINTS*sum_x2 - pow(sum_x, 2));
  b = (sum_y - m*sum_x)/DATA_POINTS;

  //Computes the correlation value
  avg = sum_y/DATA_POINTS;
  
  for(uint8_t i=0; i<DATA_POINTS; i++){
    double real_value = output_voltage[i];
    double predicted_value = m*codes_used[i] + b;

    ssr += pow(real_value - predicted_value, 2);
    sst += pow(real_value - avg, 2);
  }

  r = sqrt(1 - ssr/sst);

  //Saves the result interpolation into the buffer
  buffer[0] = m;
  buffer[1] = b;
  buffer[2] = r;
}
//----------------------------------//

//----------------------------------//
void printCalibration(float regression[3], uint16_t min_code, uint16_t max_code){
  Serial.println("");
  Serial.println("******** Linear Regression Info ********");
  Serial.print("Slope:       m = ");
  Serial.println(regression[0], 5);
  Serial.print("Intercept:   b = ");
  Serial.println(regression[1], 5);
  Serial.print("Correlation: r = ");
  Serial.println(regression[2], 5);
  Serial.println("****************************************");
  Serial.println("");
  Serial.print("DAC_MIN_CODE ");
  Serial.println(min_code);
  Serial.print("DAC_MAX_CODE ");
  Serial.println(max_code);
  Serial.println("");
  Serial.println("Copy the MIN and MAX codes into the main script");
  Serial.println("to be used as the calibration for this particular module");
  Serial.println("");
  Serial.println("****************************************");
}
//----------------------------------//