/*Implemented first 3 funtions of
 * OFF LEDS,
 * RED FLASH,
 * WHITE FLASH
 * Braking Solid RED
 * Braking Solid White
 */

#include "M5Atom.h"
uint8_t DisBuff[2 + 5 * 5 * 3];
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

float deacceleratingThreshold = 0.1;

float accX = 0;
float accY = 0;
float accZ = 0;

bool IMU6886Flag = false;

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
    setBuff(0x00, 0x00, 0x00);
    M5.dis.displaybuff(DisBuff);
    delay(40);
    break;
  case 1:
    setBuff(0xff, 0x00, 0x00);
    M5.dis.displaybuff(DisBuff);
    delay(40);
    M5.dis.clear();
    delay(40);
    break;
  case 2:
    setBuff(0x80, 0x80, 0x80);
    M5.dis.displaybuff(DisBuff);
    delay(40);
    M5.dis.clear();
    delay(40);
    break;
  case 3:
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    if (abs(accX) > deacceleratingThreshold && abs(accY) > deacceleratingThreshold&& abs(accZ) > deacceleratingThreshold)
    {
      setBuff(0xff, 0x00, 0x00);
      M5.dis.displaybuff(DisBuff);
      delay(40);
      M5.dis.clear();
      delay(40);
    }

    else
    {
      setBuff(0xff, 0x00, 0x00);
      M5.dis.displaybuff(DisBuff);
      delay(40);
    }
    break;

  case 4:
    M5.IMU.getAccelData(&accX, &accY, &accZ);
     if ((abs(accX) > deacceleratingThreshold) && (abs(accY) > deacceleratingThreshold))
    {
      setBuff(0x80, 0x80, 0x80);
      M5.dis.displaybuff(DisBuff);
      delay(40);
      M5.dis.clear();
      delay(40);
    }

    else
    {
      setBuff(0x80, 0x80, 0x80);
      M5.dis.displaybuff(DisBuff);
      delay(40);
      
    }
    break;
  }

  M5.update();
}
