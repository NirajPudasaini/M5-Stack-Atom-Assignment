#include "M5Atom.h"

uint8_t Display_Buffer[2 + 5 * 5 * 3];

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

void setup() {
  // put your setup code here, to run once:
  M5.begin(true, false, true);
  delay(50);
  M5.dis.drawpix(0, 0xf00000);

  IMU6886Flag = M5.IMU.Init() == 0;

    if(!IMU6886Flag)
    {
        Serial.println("Error initializing the IMU! :-(");
    }
}



void loop() {
  // put your main code here, to run repeatedly:
  
  //start of part h. iii.
  //this is the part for displaying a color for each temperature range
  M5.IMU.getTempData(&tempC);
  if(tempC<25)
  {
    M5.dis.drawpix(0, 0x707070);
  }
  else if(tempC>25&&tempC<32)
  {
    M5.dis.drawpix(0, 0x00f000);
  }
  else if(tempC>32&&tempC<40)
  {
   
  }
  else if(tempC>40)
  {
    M5.dis.drawpix(0, 0x0000f0);
  }


  M5.update();
}
