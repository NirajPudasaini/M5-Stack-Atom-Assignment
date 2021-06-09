float deacceleratingThreshold = 0.07;

bool isDeaccelerating = false;

float accX = 0, newAccX = 0, accX_avg = 0;
float accY = 0, newAccY = 0, accY_avg = 0;
float accZ = 0, newAccZ = 0, accZ_avg = 0;
void checkDeaccelerating(float oldAccX, float oldAccY)
{
  float accX = 0, accY = 0, accZ = 0;
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  // Average the acceleration data
  // simple "running average" method without store the data in an array
  accX_avg = ((accX_avg * (n_average - 1)) + accX) / n_average;
  accY_avg = ((accY_avg * (n_average - 1)) + accY) / n_average;
  accZ_avg = ((accZ_avg * (n_average - 1)) + accZ) / n_average;

  Serial.printf("accX_avg is ");
  Serial.print(accX_avg);
  Serial.printf("accX is ");
  Serial.print(accX_avg);

  if ((accX_avg - accX) > deacceleratingThreshold && (accY_avg - accY)>deacceleratingThreshold)
  {
    isDeaccelerating = true;
  }
  else
  {
    isDeaccelerating = false;
  }
  oldAccX = accX; oldAccY = accY;
}

void setBuff(uint8_t Rdata, uint8_t Gdata, uint8_t Bdata)
{
  DisBuff[0] = 0x05;
  DisBuff[1] = 0x05;
  for (int i = 0; i < 25; i++)
  {
    DisBuff[2 + i * 3 + 0] = Rdata;
    DisBuff[2 + i * 3 + 1] = Gdata;
    DisBuff[2 + i * 3 + 2] = Bdata;
  }
}
