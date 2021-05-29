/*
 Single pixel blink for 250ms
 */

#include "M5Atom.h"

void setup() 
{
  M5.begin(true, false, true);
  delay(20);
}

void loop() 
{
  M5.dis.drawpix(2, 2, 0xffffff);
  Serial.println(F("Pixel is on"));
  delay(250);
  M5.dis.clear();
  Serial.println(F("Pixel is off"));
  delay(250);
  M5.update();
}
