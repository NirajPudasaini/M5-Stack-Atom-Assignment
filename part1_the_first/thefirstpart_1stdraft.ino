/*Implemented first 3 funtions of 
 * OFF LEDS, 
 * RED FLASH, 
 * WHITE FLASH
 */

#include "M5Atom.h"
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

void setup()
{
    M5.begin(true, false, true);
    setBuff(0x00, 0x00, 0x00);
    M5.dis.displaybuff(DisBuff);
}

uint8_t cycle = 0;

void loop()
{
   if (M5.Btn.wasPressed())
    {
      if (cycle >2)
        {
            cycle = 0;
        }
        cycle++;
    }

      switch (cycle)
          {
       case 0:
            setBuff(0x00, 0x00, 0x00);
            M5.dis.displaybuff(DisBuff);
            delay(50);
            M5.dis.clear();
            delay(50); 
            break;
        case 1:
            setBuff(0xff, 0x00, 0x00);
            M5.dis.displaybuff(DisBuff);
            delay(50);
             M5.dis.clear();
        delay(50); 
            break;
        case 2:
            setBuff(0x40, 0x40, 0x40);
            M5.dis.displaybuff(DisBuff);
            delay(50);
             M5.dis.clear();
        delay(50); 
            break;
        /*case 3: To implement automatic rear for red
            setBuff(0x00, 0x00, 0x40);
            break;
        case 4: To implement automatic rear for white
            setBuff(0x20, 0x20, 0x20);
            break;
        */
       
        }
       
        M5.update();
 }
