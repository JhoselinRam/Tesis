#include <Arduino.h>
#line 1 "/home/adrian/Documents/Tesis/Sensores/ultrasonic_test/ultrasonic_test.ino"
#include "HYSFR05.h"

#line 3 "/home/adrian/Documents/Tesis/Sensores/ultrasonic_test/ultrasonic_test.ino"
void setup();
#line 9 "/home/adrian/Documents/Tesis/Sensores/ultrasonic_test/ultrasonic_test.ino"
void loop();
#line 3 "/home/adrian/Documents/Tesis/Sensores/ultrasonic_test/ultrasonic_test.ino"
void setup()
{
	ultrasonic_begin();
  Serial.begin(115200);
}

void loop()
{
  Serial.println(ultrasonic_read());
  delay(20);
}

