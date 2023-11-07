#include "HYSFR05.h"

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
