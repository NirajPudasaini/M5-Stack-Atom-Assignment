{
  M5.begin(true, false, true);
  delay(50);
  M5.dis.drawpix(0, 0xf00000);
}

uint8_t FSM=0;

unsigned long previousMillis;
unsigned long millisBetweenPrints = 50;
unsigned long previousMillisMPU6886;
unsigned long millisBetweenMPU6886=100;
unsigned long currentMillis;

void readAccel()
{}

void loop() {
  // put your main code here, to run repeatedly:
  if(M5.Btn.wasPressed())
  {
    switch (FSM)
    {
      case 0:
        M5.did.drawpix(0xf00000);
        break;
      case 1:
        M5.did.drawpix(0x00f000);
        break;
      case 2:
        M5.did.drawpix(0x0000f0);
        break:
      case 3:
         M5.did.drawpix(0x707070);
         break;
      default:
        break;
        
    }
    FSM++;
    if (FSM >=4)
    {
      FSM=0;
    }
  }

  delay (100);
  currentMillis=millis();

  if (currentMillis - previousMillis > millisBetweenPrints)
  {
    M5.update();
    previousMillis = millisRightNow;
  }

  delay(50);

  if(currentMillis-previousMillis>millisBetweenMPU6886)
  {
    readAccel();
    previousMillisMPU6886=currentMillis;
  }
  

}
