#include "M5Atom.h"
uint8_t DisBuff[2 + 5 * 5 * 3];
const int n_average = 20;
bool isFlashing = false;
unsigned long lastDisplayTime = 0; //
const unsigned long flashTimeInterval = 50;
const unsigned long sensorTimeInterval = 20;
bool IMU6886Flag = false;
unsigned long currentTime = millis();























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
