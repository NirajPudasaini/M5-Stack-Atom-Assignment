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


void setup() {
    M5.begin(true, false, true);
    delay(50);
    setBuff(0xff, 0x00, 0x00);
    M5.dis.displaybuff(DisBuff);
    M5.dis.drawpix(0, 0xf00000);
    M5.dis.drawpix(5, 0xf00000); 
    M5.dis.drawpix(10, 0xf00000);
    M5.dis.drawpix(15, 0xf00000);
    M5.dis.drawpix(20, 0xf00000);
    M5.dis.drawpix(11, 0xf00000);
    M5.dis.drawpix(2, 0xf00000);
    M5.dis.drawpix(7, 0xf00000);
    M5.dis.drawpix(12, 0xf00000);
    M5.dis.drawpix(17, 0xf00000);
    M5.dis.drawpix(22, 0xf00000);
    M5.dis.drawpix(4, 0xf00000);
    M5.dis.drawpix(9, 0xf00000);
    M5.dis.drawpix(14, 0xf00000);
    M5.dis.drawpix(19, 0xf00000);
    M5.dis.drawpix(24, 0xf00000);
    delay(10000);
}

uint8_t counter=0;

void loop() {
  if(M5.Btn.wasPressed())
  {
    switch (counter)
        {
        case 0:
            setBuff(0x40, 0x00, 0x00);
            break;
        case 1:
            setBuff(0x00, 0x40, 0x00);
            break;
        case 2:
            setBuff(0x00, 0x00, 0x40);
            break;
        case 3:
            setBuff(0x20, 0x20, 0x20);
            break;
        default:
            break;
        }
        M5.dis.displaybuff(DisBuff);

        counter++;
        if (counter >= 4)
        {
            counter = 0;
        }
  }
   delay(50);
   M5.update();
}
