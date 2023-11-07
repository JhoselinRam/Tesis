#line 1 "/home/adrian/Documents/Tesis/Sensores/ultrasonic/README.md"
# Ultrasonic Sensor

This sensor uses an Arduino nano as the processing unit, but it can be easily replaced with any other microcontroller. The nano was chosen due to its small footprint and its ease to obtain.

It also uses the HY-SFR05 ultrasonic module, but it can be easily replaced with HC-SR04.

And the MCP4725 12 bit Digital to Analog (DAC) to encode the distance read into an analog voltage.

Tho work properly, the DAC module must be previously calibrated (check the dac_calibration folder).

## Filters

You can choose only one of the provided filters, or no filter at all. To do that, uncomment the definition of the filter and all its parameters you intend to use and comment the rest. If more than one definition is uncommented, only the first one seen by the preprocessor will be applied.
