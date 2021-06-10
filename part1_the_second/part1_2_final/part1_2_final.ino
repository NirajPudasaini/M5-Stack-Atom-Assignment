#include <M5Atom.h>
#include <Arduino.h>
#include "characters.c"

float lastFiveTemp[5] = {0};
float avgTemp = 0;
float tempF = 0;
bool isFahrenheit = false;
int pressedTwice = 0;
float tempC = 0;
const int minDelay = 10000;
int minCount = 0;
float currentTime;
float tempReading[8640] = {0};
uint8_t DisBuff[2 + 5 * 5 * 3];

//initializations for displaying different modes and numbers on Matrix
uint8_t * modes[5] = { (uint8_t *)image_numbers[1] , (uint8_t *)image_numbers[2], (uint8_t *)image_numbers[3], (uint8_t *)image_numbers[4], (uint8_t *)image_numbers[5] };
uint8_t * num[10] = {(uint8_t *)image_numbers[0] , (uint8_t *)image_numbers[1], (uint8_t *)image_numbers[2], (uint8_t *)image_numbers[3], (uint8_t *)image_numbers[4],
                     (uint8_t *)image_numbers[5] , (uint8_t *)image_numbers[6], (uint8_t *)image_numbers[7], (uint8_t *)image_numbers[8], (uint8_t *)image_numbers[9]
                    };

//custom made array to show celcius, degrees, and fahrenheit


//fuction to display temperature's unit
void displayTemperatureUnit(bool isF)
{
  delay(300);
  if (isF == false) {
    for (int i = 0; i < 25; i++)
    {
      if (C[i] == 1)
      {
        M5.dis.drawpix(i, 0x00ff00);
      }
      else M5.dis.drawpix(i, 0x000000);
    }
  }
  else
  { for (int i = 0; i < 25; i++)
    {
      if (F[i] == 1)
      {
        M5.dis.drawpix(i, 0x0000f0);
      }
      else M5.dis.drawpix(i, 0x000000);
    }
  }
  delay (700);
}

//cobimining temp as message and displaying
void onScreenDisplay (String msg)
{
  int n = msg.length();
  int i = 0;
  char char_array[n];
  for (i = 0; i < n; i++)
  {
    char_array[i] = msg[i];
    if ((char_array[i] == 'C') || (char_array[i] == 'F'))
    {
      delay(300);
      displayTemperatureUnit(isFahrenheit);
      delay(700);
    }
    else if (char_array[i] == '.')
    {
      delay(300);
      for (int i = 0; i < 25; i++)
      {
        if (dot[i] == 1)
        {
          M5.dis.drawpix(i, 0x00ff00);
        }
        else {
          M5.dis.drawpix(i, 0x000000);
        }
      }
      delay(700);
    }
    else
    {
      M5.dis.clear();
      delay(300);
      M5.dis.displaybuff(num[char_array[i] - ('0')]);
      delay(700);
    }
  }
}

//running average temp calculation
float getTempAverage(float tempReading[2880], int minCount) {
  float sum = 0;
  int cnt = 0;
  int mc = minCount;
  float avg = 0;
  while (mc >= 1) {
    sum = sum + tempReading[cnt];
    cnt++;
    mc--;
  }
  return (sum / (cnt));
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
//displaying range of temp measured with the range at the last row
void showTempRange(uint8_t Rdata, uint8_t Gdata, uint8_t Bdata)
{
  DisBuff[0] = 0x05;
  DisBuff[1] = 0x05;
  for (int i = 0; i < 20; i++)
  {
    DisBuff[2 + i * 3 + 0] = Rdata;
    DisBuff[2 + i * 3 + 1] = Gdata;
    DisBuff[2 + i * 3 + 2] = Bdata;
  }
  for (int i = 21; i < 22; i++)
  {
    DisBuff[2 + i * 3 + 0] = 0xff;
    DisBuff[2 + i * 3 + 1] = 0xff;
    DisBuff[2 + i * 3 + 2] = 0xff;
  }
  for (int i = 23; i < 24; i++)
  {
    DisBuff[2 + i * 3 + 0] = 0xff;
    DisBuff[2 + i * 3 + 1] = 0xa5;
    DisBuff[2 + i * 3 + 2] = 0x00;
  }
  for (int i = 22; i < 23; i++)
  {
    DisBuff[2 + i * 3 + 0] = 0x00;
    DisBuff[2 + i * 3 + 1] = 0xf0;
    DisBuff[2 + i * 3 + 2] = 0x00;
  }
  for (int i = 24; i < 25; i++)
  {
    DisBuff[2 + i * 3 + 0] = 0xf0;
    DisBuff[2 + i * 3 + 1] = 0x00;
    DisBuff[2 + i * 3 + 2] = 0x00;
  }
  M5.dis.displaybuff(DisBuff);
  delay(500);
}


bool IMU6886Flag = false;
float accX, accY, accZ;

bool leftMove = false, midMove = false, rightMove = false;
bool screenActivated = false;
bool isFacingUp = false;
bool isFacingDown = false;
int currentMode = -1;
bool startMode = false;
float lastReadingTime = 0;

//fuctions to check the orientation of devices
void facingUp(float x, float y, float z)
{
  if (z < -0.75 && abs(x) < 0.15 && abs(y) < 0.15) {
    isFacingUp = true;
    isFacingDown = false;
  }
}

void facingDown(float x, float y, float z)
{
  if (z > 0.75 && abs(x) < 0.15 && abs(y) < 0.15) {
    isFacingUp = false;
    isFacingDown = true;
  }
}

//check the current mode based on the orientation of the ATOM matrix
int currentModeIs(float x, float y, float z)
{
  {
    if (accX >= 0.85 && currentMode < 4) {
      rightMove = true;
    }

    if (accX < 0 && accX > -1 && currentMode >= 0 && (rightMove || leftMove)) {
      midMove = true;
    }

    if (accX <= -0.85 && currentMode >= 0) {
      leftMove = true;
    }

    if (midMove && rightMove) {
      currentMode++;
      leftMove = false;
      midMove = false;
      rightMove = false;
      delay(700);
    }

    if (leftMove && midMove) {
      currentMode--;
      leftMove = false;
      midMove = false;
      rightMove = false;
      delay(700);
    }

    if (currentMode > 4) currentMode = 4;
    if (currentMode < 0) currentMode = 0;
    if (screenActivated)
      M5.dis.displaybuff(modes[currentMode]);
  }
  return currentMode;
}

//plotting graph of the last five measured samples of temperature on the predetermined intervals
//colors determine the temperature range
void plotGraph(float lastFiveTemp[5]) {
  M5.dis.clear();
  for (int i = 0; i < 5; i++) {
    if (lastFiveTemp[i] >= 40)
    {
      M5.dis.drawpix(14 - i, 0x00ff00);
    }
    else  if ((tempC < 40) && (tempC >= 31))
    {
      M5.dis.drawpix(14 - i, 0x80f000);
    }
    else if ((tempC < 31) && (tempC >= 24))
    {
      M5.dis.drawpix(14 - i, 0xff0000);
    }
    else if (tempC < 24)
    {
      M5.dis.drawpix(14 - i, 0xffffff);
    }
    else {
      M5.dis.drawpix(14 - i, 0x000000);
    }
  }
  delay(3000);
}


void setup()
{
  M5.begin(true, false, true);
  if (!M5.IMU.Init()) IMU6886Flag = true;
}

void loop() {
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  currentMode = currentModeIs(accX, accY, accZ);
  facingUp(accX, accY, accZ);
  facingDown(accX, accY, accZ);
  currentTime = millis();
  if (currentTime - lastReadingTime >= minDelay)
  {
    M5.IMU.getTempData(&tempC);
    tempReading[minCount] = tempC;
    lastReadingTime = currentTime;
    minCount++;
    if (minCount >= 2880)
      minCount = 0;
  }
  if (isFacingDown) {
    screenActivated = false;
    setBuff(0x00, 0x00, 0x00);
    M5.dis.displaybuff(DisBuff);
    //numPressed = -1;
    currentMode = -1;
  }
  else if (isFacingUp && M5.Btn.wasPressed() && screenActivated == false)
  {
    screenActivated = true;
    delay(100);
    currentMode = currentModeIs(accX, accY, accZ);
  }
  else if (screenActivated && M5.Btn.wasPressed())
  {
    switch (currentMode)
    {
      case 0:     {           //case for showing acive temp + units
          M5.IMU.getTempData(&tempC);
          delay(200);
          String toDisplay = String(tempC, 2);
          if (isFahrenheit == false) {
            toDisplay = toDisplay + "C";
          }
          else {
            tempF = tempC * 1.8 + 32;
            toDisplay = String(tempF, 2);
            toDisplay = toDisplay + "F";
          }
          //Serial.printf("Show temp on device");
          Serial.print(toDisplay);
          onScreenDisplay(toDisplay);
          break;
        }

      case 1:
        {
          if (minCount == 0)
          {
            M5.IMU.getTempData(&tempC);
            avgTemp = tempC;
          }
          else
          {
            avgTemp = getTempAverage(tempReading, minCount);
          }
          //Serial.printf("Show average of last four hours + units");
          //Serial.print(avgTemp);
          String toDisplay = String(avgTemp, 2);
          if (isFahrenheit == false) {
            toDisplay = toDisplay + "C";
          }
          else {
            avgTemp = avgTemp * 1.8 + 32;
            toDisplay = String(avgTemp, 2);
            toDisplay = toDisplay + "F";
          }
          onScreenDisplay(toDisplay);
          break;
        }

      case 2:
        { //color tempCerature range + current tempC as color
          //Serial.printf("Show color tempCerature range + current tempC as color");
          M5.IMU.getTempData(&tempC);
          if (tempC >= 39)
          {
            showTempRange(0x80, 0x00, 0x00);
          }
          else  if ((tempC < 39) && (tempC >= 31))
          {
            showTempRange(0xf0, 0x80, 0x00);
          }
          else if ((tempC < 31) && (tempC >= 24))
          {
            showTempRange(0x00, 0x80, 0x00);
          }
          else if (tempC < 24)
          {
            showTempRange(0x80, 0x80, 0x80);
          }
          delay(2000);
          break;
        }

      case 3:
        {
          for (int i = 0; i < 5; i++)
          {
            if (minCount < 5)
            {
              lastFiveTemp[i] = tempReading[0];
            }
            else
            {
              lastFiveTemp[i] = tempReading[minCount - 5 + i];
            }
            Serial.println(lastFiveTemp[i]);    //fill the array in increasing order of temp measured
          }
          Serial.printf("In mode 4");
          plotGraph(lastFiveTemp);
          delay(300);
          break;
        }

      case 4:                   //change units
        if (isFahrenheit == false)
          isFahrenheit = true;
        else isFahrenheit = false;
        Serial.printf("units changed !");
        break;
    }
    delay(100);
  }
  M5.update();
}
