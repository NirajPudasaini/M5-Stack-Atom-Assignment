#include "M5Atom.h"

float accX = 0, accY = 0, accZ = 0;
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


void setup() {

  Serial.begin(115200);
  M5.begin(true, false, true);
  M5.IMU.Init();

}

void loop() {
        //case 3
        M5.IMU.getAccelData(&accX, &accY, &accZ);
        int x = Serial.println(accX);
        while(x>-3 && x<3)
        {
          setBuff(0x40, 0x00, 0x00);
          delay(30);
        }
        setBuff(0x40, 0x00, 0x00);
        delay(5000);        
}
