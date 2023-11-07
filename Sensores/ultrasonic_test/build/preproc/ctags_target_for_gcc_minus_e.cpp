# 1 "/home/adrian/Documents/Tesis/Sensores/ultrasonic_test/ultrasonic_test.ino"
# 2 "/home/adrian/Documents/Tesis/Sensores/ultrasonic_test/ultrasonic_test.ino" 2

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
