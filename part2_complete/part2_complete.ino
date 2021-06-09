#include <M5Atom.h>
#include <Arduino.h>
#include "characters.c"
#include <WiFi.h>
#include <WiFiClient.h>
#include <SD.h>
#include <SPI.h>
WiFiServer server(80);


long var = 0;
int num[25] = {0};
char check;

int GRB_COLOR_WHITE = 0xffffff;
int GRB_COLOR_BLACK = 0x000000;
int GRB_COLOR_RED = 0x00ff00;
int GRB_COLOR_YELLOW = 0xffff00;
int GRB_COLOR_GREEN = 0xff0000;
int GRB_COLOR_BLUE = 0x0000ff;

String toDisplay = "";
bool IMU6886Flag = false;
float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
float newGyroX = 0, newGyroY = 0, newGyroZ = 0;
bool leftMove = false, midMove = false, rightMove = false;
bool screenActivated = false;
int currentMode = -1;
const float displayDelay = 100;
float lastReadingTime = 0;
int numberToShow;
int randomNum = 0;
bool inGame = false;
uint8_t DisBuff[2 + 5 * 5 * 3];
int activeColor = GRB_COLOR_RED;
int colorList[] = {GRB_COLOR_BLACK, activeColor};
const char *ssid = "Group22";
const char *password = "DandI01234";
int accTolerance = 3;
float gyroTolerance = 400;
float displayGyroZ = 20;
bool shakeDetected = false;
bool spinDetected = false;
const int *displayNumbers[6] = {one, two, three, four, five, six };

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
void LUDOMode()
{
  setBuff(0x00, 0x00, 0x00); // clearing before adding colors to the MATRIX
  DisBuff[0] = 0x05;
  DisBuff[1] = 0x05;
  for (int i = 0; i < 25; i++)
  {
    if ((i == 3) || (i == 4) || (i == 8) || (i == 9)) {
      DisBuff[2 + i * 3 + 0] = 0xff;
      DisBuff[2 + i * 3 + 1] = 0x00;
      DisBuff[2 + i * 3 + 2] = 0x00;
    }
    else if ((i == 0) || (i == 1) || (i == 5) || (i == 6))
    {
      DisBuff[2 + i * 3 + 0] = 0x00;
      DisBuff[2 + i * 3 + 1] = 0xff;
      DisBuff[2 + i * 3 + 2] = 0x00;
    }
    else if ((i == 15) || (i == 16) || (i == 20) || (i == 21))
    {
      DisBuff[2 + i * 3 + 0] = 0x00;
      DisBuff[2 + i * 3 + 1] = 0x00;
      DisBuff[2 + i * 3 + 2] = 0xff;
    }
    else if ((i == 18) || (i == 19) || (i == 23) || (i == 24))
    {
      DisBuff[2 + i * 3 + 0] = 0xff;
      DisBuff[2 + i * 3 + 1] = 0xa5;
      DisBuff[2 + i * 3 + 2] = 0x00;
    }
  }
}

void ROULETTEMode()
{
  setBuff(0x00, 0x00, 0x00); // clearing before adding colors to the MATRIX
  DisBuff[0] = 0x05;
  DisBuff[1] = 0x05;
  for (int i = 0; i < 25; i++)
  {
    if ((i == 2) || (i == 10) || (i == 7) || (i == 11) || (i == 13) || (i == 14) || (i == 17) || (i == 22)) {
      DisBuff[2 + i * 3 + 0] = 0xff;
      DisBuff[2 + i * 3 + 1] = 0x00;
      DisBuff[2 + i * 3 + 2] = 0x00;
    }
    else if ((i == 12))
    {
      DisBuff[2 + i * 3 + 0] = 0xff;
      DisBuff[2 + i * 3 + 1] = 0xff;
      DisBuff[2 + i * 3 + 2] = 0xff;
    }
  }
}

void drawArray(const int arr[], int colors[])
{
  for (int i = 0; i < 25; i++)
  {
    M5.dis.drawpix(i, colors[arr[i]]);
  }
}
int currentModeIs(float x, float y, float z)
{
  {
    if (accX >= 0.85 &&  accY <= 0.1 && accZ <= 0.1 && currentMode < 1) {
      rightMove = true;
    }

    if (accX < 0 && accX > -1 && currentMode >= 0 && (rightMove || leftMove)) {
      midMove = true;
    }

    if (accX <= -0.8 &&  accY <= 0.1 && accZ <= 0.1 && currentMode >= 0) {
      leftMove = true;
    }

    if (midMove && rightMove) {
      currentMode++;
      leftMove = false;
      midMove = false;
      rightMove = false;
      delay(400);
    }

    if (leftMove && midMove) {
      currentMode--;
      leftMove = false;
      midMove = false;
      rightMove = false;
      delay(700);
    }

    if (currentMode > 1) currentMode = 1;
    if (currentMode < 0) currentMode = 0;
    if (screenActivated)
      if (currentMode == 0) {
        LUDOMode();
        M5.dis.displaybuff(DisBuff);
      }
      else if (currentMode == 1)
      {
        ROULETTEMode();
        M5.dis.displaybuff(DisBuff);
      }
  }
  return currentMode;
}
void getRandomNumber(int a, int b )
{
  numberToShow = random(a, b);
}
void isShakeDetected() {
  if (IMU6886Flag)
  {
    M5.IMU.getAccelData(&accX, &accY, &accZ);

    if (abs(accX) > accTolerance || abs(accY) > accTolerance)
    {
      shakeDetected = true;
      M5.dis.clear();
      getRandomNumber(0, 6);
      setBuff(0x00, 0x00, 0x00);
      M5.dis.displaybuff(DisBuff);
      delay(100);
      drawArray(displayNumbers[numberToShow], colorList);
    }
  }
}

void isSpinDetected()
{
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  if (abs(gyroZ) >= gyroTolerance)
  {
    spinDetected = true;
    while (abs(gyroZ) > displayGyroZ) {
      setBuff(0x00, 0x00, 0x00);
      M5.dis.displaybuff(DisBuff);

      M5.IMU.getGyroData(&newGyroX, &newGyroY, &newGyroZ);
      gyroZ = abs(newGyroZ);
      Serial.println(gyroZ);
    }
    Roullete();
  }
}
void whiteNumberDisplay (String msg) {
  int n = msg.length();
  if (n == 1) {
    msg = "0" + msg;
  }
  char char_array[n];
  Serial.printf("Start");
  for (int i = 0; i < 2; i++)
  {
    delay(800);
    char_array[i] = msg[i];
    if (char_array[i] == '0')
    {
      for (int j = 0; j < 25; j++)
      {
        num[j] = zero[j];
      }
    }
    else if (char_array[i] == '1')
    {
      for (int j = 0; j < 25; j++)
      {
        num[j] = one[j];
      }
    }
    else if (char_array[i] == '2')
    {
      for (int j = 0; j < 25; j++)
      {
        num[j] = two[j];
      }
    }
    else if (char_array[i] == '3')
    {
      for (int j = 0; j < 25; j++)
      {
        num[j] = three[j];
      }
    }
    else if (char_array[i] == '4')
    {
      for (int j = 0; j < 25; j++)
      {
        num[j] = four[j];
      }
    }
    else if (char_array[i] == '5')
    {
      for (int j = 0; j < 25; j++)
      {
        num[j] = five[j];
      }
    }
    else if (char_array[i] == '6')
    {
      for (int j = 0; j < 25; j++)
      {
        num[j] = six[j];
      };
    }
    else if (char_array[i] == '7')
    {
      for (int j = 0; j < 25; j++)
      {
        num[j] = seven[j];
      }
    }
    else if (char_array[i] == '8')
    {
      for (int j = 0; j < 25; j++)
      {
        num[j] = eight[j];
      }
    }
    else if (char_array[i] == '9')
    {
      for (int j = 0; j < 25; j++)
      {
        num[j] = nine[j];
      }
    }
    M5.dis.clear();
    for (int k = 0; k < 25; k++)
    {
      if (num[k] == 1)
      {
        M5.dis.drawpix(k, 0x808080);
      }
      else if (num[k] == 0)
      {
        if (check == 'R')
          M5.dis.drawpix(k, 0x008000);
        else if (check == 'B')
          M5.dis.drawpix(k, 0x000000);
        else if (check == 'G')
          M5.dis.drawpix(k, GRB_COLOR_GREEN);
      }
    }
    delay(500);
  }
}
void runGame()
{
  Serial.printf("in physical game mode");
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  //delay(400);
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  currentMode = currentModeIs(accX, accY, accZ);
  if ( M5.Btn.wasPressed() && screenActivated == false )
  {
    screenActivated = true;
    currentMode = currentModeIs(accX, accY, accZ);
  }
  else if (screenActivated && M5.Btn.wasPressed())
  {
    switch (currentMode)
    {
      case 0:     {           //case for showing acive temp + units

          Serial.print("Game 1");
          while (1)
          {
            isShakeDetected();
          }
          break;
        }

      case 1:
        {
          Serial.print("Game 2");
          while (1)
          {
            isSpinDetected();
          }
          break;
        }
    }
    delay(100);
  }
}

void Roullete() {
  getRandomNumber(0, 38);
  setBuff(0x00, 0x00, 0x00);
  M5.dis.displaybuff(DisBuff);
  delay(200);
  if (numberToShow == 15 || numberToShow == 4 || numberToShow == 2 || numberToShow == 17 || numberToShow == 6 || numberToShow == 13 || numberToShow == 11 || numberToShow == 8 || numberToShow == 10 || numberToShow == 24 || numberToShow == 33 || numberToShow == 20 ||
      numberToShow == 31 || numberToShow == 22 || numberToShow == 29 || numberToShow == 28 || numberToShow == 35 || numberToShow == 26) {
    setBuff(0xff, 0x00, 0x00);
    check = 'B';
    toDisplay = String(numberToShow);
    whiteNumberDisplay(toDisplay);
    Serial.print(toDisplay);
    //M5.dis.displaybuff(DisBuff);
    delay(500);

  }
  else if (numberToShow == 32 || numberToShow == 19 || numberToShow == 21 || numberToShow == 25 || numberToShow == 34 || numberToShow == 27
           || numberToShow == 36 || numberToShow == 30 || numberToShow == 23 || numberToShow == 5 || numberToShow == 16 || numberToShow == 1 ||
           numberToShow == 14 || numberToShow == 9 || numberToShow == 18 || numberToShow == 7 || numberToShow == 12 || numberToShow == 03) //RED
  {
    check = 'R';
    setBuff(0x00, 0x00, 0x00);
    toDisplay = String(numberToShow);
    whiteNumberDisplay(toDisplay);
    Serial.print(toDisplay);
    //M5.dis.displaybuff(DisBuff);
    delay(500);
  }
  else if (numberToShow == 0)
  {
    check = 'G';
    setBuff(0x00, 0x00, 0xff);
  }
}

void onlineLUDO() {
  getRandomNumber(0, 6);
  activeColor = GRB_COLOR_RED;
  setBuff(0x00, 0x00, 0x00);
  M5.dis.displaybuff(DisBuff);
  delay(200);
  drawArray(displayNumbers[numberToShow], colorList);
}

void setup()
{
  M5.begin(true, false, true);
  if (!M5.IMU.Init()) IMU6886Flag = true;

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}
void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Welcome!</h2>\n");
            client.print("<p style=\"font-size: 1.5em;\">Play <strong>LUDO</strong> or <strong>ROULETTE</strong></p>\n");
            client.print("<button onclick=\"location.href='/H'\" type=\"button\">\n"
                         "Roll the Dice</button><p>&emsp;</p><p>&emsp;</p><p>&emsp;</p><p>&emsp;</p>");
            client.print("<button onclick=\"location.href='/L'\" type=\"button\">\n"
                         "Spin the Roulette</button>");

            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        if (currentLine.endsWith("GET /H")) {
          // GET /H turns the LED on
          onlineLUDO();
          //client.println(var);

        }
        else if (currentLine.endsWith("GET /L"))
        {
          Roullete();
          //client.println("Roulette Value");

        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
  else
  {
    runGame(); //physical game MODE
  }
  M5.update();
}
