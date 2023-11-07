# MCP4725 Calibration Script

The MCP4725 it's a 12 bit Digital To Analog (DAC) module. It uses the I2C protocol to communicate to the microcontroller.

Ideally, it maps the input code, which is a 12 bit integer (0 to 4095), to a voltage between 0v and 5v at the output.

In reallity the module only has a linear respone from code 0 to 4000, and even then, the output voltaje is off from the ideal response by a small amount due to the power suppy voltage not being exactly 5v, internal component issues and the output cirquitery.

This calibration method corrects the output voltage to be more close to the ideal response at the expense of a small reduction of the codes available.

___

Here is an example of a module calibrated.

The blue line represents the module ideal response, the red is the real output and the green is the calibrated output.

![calibration_graph](/resourses/calibration_graph.jpg)

As shown, the output remains closer to the ideal response for longer after the calibration with minimal code range lose.

## Instructions

1) Open the `dac_calibration.ino` file in the Arduino code editor and make sure that only the first definition of the `code` variable is uncommented in the `TEST CODES` section.

![script_test_codes](/resourses/script_test_codes.jpg)

2) Make sure the `TEST_CALIBRATION` definition (line 59) is commented.
3) Connect the sensor to a suitable power supply (8v-15v) and measure the voltage at the output.
4) Connect the sensor to the computer through the USB cable and upload the script.
5) Disconnect the USB cable and measure the output voltage. The USB must be completely disconnected before taking the measurement, failing this will result in a voltage shift due to the double power supply, one from the sensor and another from the Arduino.
6) Replace the first value of the `output_voltage` array with the measured voltage.

![script_output_voltage](/resourses/script_output_voltage.jpg)

7) Comment the first definition of the `code` variable, and uncomment the second.

![script_test_codes_2](/resourses/script_test_codes_2.jpg)

8) Upload the script, disconnect the USB cable and measure the output voltage.
9) Replace the second value of the `output_voltage` array with the measured voltage.
10) Repeat this steps until all TEST CODES are used and the corresponding output voltage register.
11) Uncomment the `TEST_CALIBRATION` definition (line 59).
12) Upload the script and open the serial monitor at 115200 baud rate.
13) The serial monitor should give an output similar to:

![script_serial_monitor](/resourses/script_serial_monitor.jpg)

14) Make sure the correlation value is close to 1.
15) Copy the `DAC_MIN_CODE` and `DAC_MIN_CODE` values into the main script. These are the calibration values of that particular module.

Repeat these steps every time the MCP4725 module is replaced.