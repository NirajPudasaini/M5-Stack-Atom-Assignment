#include "M5Atom.h"
uint8_t DisBuff[2 + 5 * 5 * 3];
const int n_average = 20;
bool isFlashing = false;
unsigned long lastDisplayTime = 0; //
const unsigned long flashTimeInterval = 50;
const unsigned long sensorTimeInterval = 20;
bool IMU6886Flag = false;
unsigned long currentTime = millis();

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

void flashColor(uint8_t Rdata, uint8_t Gdata, uint8_t Bdata)
{
  //Serial.println("Inside function flashColor");
  if (currentTime - lastDisplayTime <= flashTimeInterval)
  {
    if (isFlashing == false)
    {
      setBuff(Rdata, Gdata, Bdata);
      M5.dis.displaybuff(DisBuff);
      isFlashing = true;
    }
    else
    {
      M5.dis.clear();
      isFlashing = false;
    }
    lastDisplayTime = currentTime;
  }
}

void setup()
{
  M5.begin(true, false, true);
  setBuff(0x00, 0x00, 0x00);
  M5.dis.displaybuff(DisBuff);

  IMU6886Flag = M5.IMU.Init() == 0;

  if (!IMU6886Flag)
  {
    Serial.println("Error initializing the IMU! :-(");
  }

}

uint8_t cycle = 0;

void loop()
{
  //Serial.printf("looping");
  if (M5.Btn.wasPressed())
  {
    cycle++;
    if (cycle > 4)
    {
      cycle = 0;
    }

  }
  switch (cycle)
  {
    case 0:
      {
        setBuff(0x00, 0x00, 0x00);
        M5.dis.displaybuff(DisBuff);
        //Serial.printf("At case 0");
        break;
      }
    case 1:
      {
        //Serial.printf("At case 1");
        flashColor(0xff, 0x00, 0x00);
        Serial.printf("flashing red");
        break;
      }
    case 2:
      {
       // Serial.printf("At case 2");
        flashColor(0x60, 0x60, 0x60);
        Serial.printf("flashing red");
        break;
      }
    case 3:
      {
        Serial.printf("At case 3, : ");
        M5.IMU.getAccelData(&accX, &accY, &accZ);
        delay(40);
        checkDeaccelerating(accX, accY);
        if (isDeaccelerating)
        {
          setBuff(0xff, 0x00, 0x00);
          M5.dis.displaybuff(DisBuff);
          delay(100);
        }
        else
          flashColor(0xff, 0x00, 0x00);
        break;
      }
    case 4:
      {
        Serial.printf("At case 4");
        M5.IMU.getAccelData(&accX, &accY, &accZ);
        delay(40);
        checkDeaccelerating(accX, accY);
        if (isDeaccelerating)
        {
          setBuff(0x60, 0x60, 0x60);
          M5.dis.displaybuff(DisBuff);
          //delay(100);
        }
        else
          flashColor(0x60, 0x60, 0x60);
      break;
      }
  }
  M5.update();
}
