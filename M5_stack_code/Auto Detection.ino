#include "M5Atom.h"           
const int xpin = 3;                  
//const int ypin = A2;                 
//const int zpin = A1;
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
    setBuff(0x00, 0x00, 0x00);
    M5.dis.displaybuff(DisBuff);  
    Serial.begin(9600);

}

void loop() {

  if(analogRead(xpin)>0.8&&analogRead(xpin)<1.3)
  {
    do
    {
      setBuff(0xff, 0x00, 0x00);
            M5.dis.displaybuff(DisBuff);
    }
    while(!M5.Btn.wasPressed());
  }
  else if(analogRead(xpin)<0.8||analogRead(xpin)>1.3)
  {
    do
    {
      setBuff(0x40, 0x40, 0x40);
            M5.dis.displaybuff(DisBuff);
    }
    while(!M5.Btn.wasPressed());
  }
  M5.update();
}
