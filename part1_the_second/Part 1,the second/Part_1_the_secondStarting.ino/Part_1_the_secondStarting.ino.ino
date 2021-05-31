#include <Arduino.h>
#include "M5Atom.h"


#define CENTER 0
#define LEFT 1
#define RIGHT 2
// if the device was tilted to the left or to the right
int tilt_move = CENTER;
const unsigned char image_numbers[20][77]={
{0x05,0x05, // 0
/* Line   000 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   001 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   002 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   003 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   004 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
},
{0x05,0x05, // 1
/* Line   000 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   001 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   002 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   003 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   004 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, //
},
{0x05,0x05, // 2
/* Line   000 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   001 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   002 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   003 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, // 
/* Line   004 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
},
{0x05,0x05, // 3
/* Line   000 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   001 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   002 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   003 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   004 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
},
{0x05,0x05, // 4
/* Line   000 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   001 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   002 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   003 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   004 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
},
{0x05,0x05, // 5
/* Line   000 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   001 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, // 
/* Line   002 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   003 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   004 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
},
{0x05,0x05, // 6
/* Line   000 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   001 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, // 
/* Line   002 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   003 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   004 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
},
{0x05,0x05, // 7
/* Line   000 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   001 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   002 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, // 
/* Line   003 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, // 
/* Line   004 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, // 
},
{0x05,0x05, // 8
/* Line   000 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   001 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   002 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   003 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   004 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
},
{0x05,0x05, // 9
/* Line   000 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   001 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   002 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   003 */ 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   004 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
},
{0x05,0x05, // 10
/* Line   000 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   001 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   002 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   003 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   004 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
},
{0x05,0x05, // 11
/* Line   000 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   001 */ 0xff,0x00,0xff, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   002 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   003 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   004 */ 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
},
{0x05,0x05, // 12
/* Line   000 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   001 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   002 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   003 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, // 
/* Line   004 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
},
{0x05,0x05, // 13
/* Line   000 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   001 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   002 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   003 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   004 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
},
{0x05,0x05, // 14
/* Line   000 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   001 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   002 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   003 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   004 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
},
{0x05,0x05, // 15
/* Line   000 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   001 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, // 
/* Line   002 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   003 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   004 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
},
{0x05,0x05, // 16
/* Line   000 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, // 
/* Line   001 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, // 
/* Line   002 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   003 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   004 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
},
{0x05,0x05, // 17
/* Line   000 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   001 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   002 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, // 
/* Line   003 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, // 
/* Line   004 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, // 
},
{0x05,0x05, // 18
/* Line   000 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   001 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   002 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   003 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   004 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
},
{0x05,0x05, // 19
/* Line   000 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   001 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   002 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
/* Line   003 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0xff,0x00,0xff, // 
/* Line   004 */ 0xff,0x00,0xff, 0x00,0x00,0x00, 0xff,0x00,0xff, 0xff,0x00,0xff, 0xff,0x00,0xff, // 
}};

#define cBLACK 0
#define cRED 1
#define cGREEN 2
#define cBLUE 3
#define cWHITE 4
#define cCYAN 5
#define cYELLOW 6
#define cMAGENTA 7
const uint8_t RGB_colors[8][3] = {{0x00, 0x00, 0x00},
                                  {0xF0, 0x00, 0x00},
                                  {0x00, 0xF0, 0x00},
                                  {0x00, 0x00, 0xF0},
                                  {0x70, 0x70, 0x70},
                                  {0x00, 0x70, 0x70},
                                  {0x70, 0x70, 0x00},
                                  {0x70, 0x00, 0x70}};

int board[25];
int board_index;
float accX_avg = 0;
uint8_t DisBuff[2 + 5 * 5 * 3];
float low_threshold = 103;
float high_threshold = 105;

uint8_t Celsius = 0;
bool IMU6886Flag = false;
float tempC = 0;

uint8_t Display_Buffer[2 + 5 * 5 * 3];

// predefined display buffers to display some characters and numbers
//#include "characters.c"

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
    delay(20);
    setBuff(0xff, 0x00, 0x00);
    M5.dis.displaybuff(DisBuff);
    IMU6886Flag = M5.IMU.Init() == 0;

    if(!IMU6886Flag)
    {
        Serial.println("Error initializing the IMU! :-(");
    }
}

int counter=0;

void loop() 
{
        M5.IMU.getTempData(&tempC);
        Serial.printf(" Temp : %.2f C \r\n", tempC);
        float Fahrenheit = (tempC * 9 / 5) + 32;
        Serial.printf(" Temp : %.2f F \r\n", Fahrenheit);
        //fillScreen(cRED);
        delay(1000);
        /*if(M5.Btn.wasPressed())
        {
          switch(counter)
          {
            case 0:
              display_number(Celsius);
              break;
            case 1:
            
          }
        }*/
        
        
        M5.update();
    
}

/*void fillScreen(uint8_t color){
    Display_Buffer[0] = 0x05;
    Display_Buffer[1] = 0x05;
    for (int i = 0; i < 25; i++){
        Display_Buffer[2 + i * 3 + 0] = RGB_colors[color][0];
        Display_Buffer[2 + i * 3 + 1] = RGB_colors[color][1];
        Display_Buffer[2 + i * 3 + 2] = RGB_colors[color][2];
    }
    M5.dis.displaybuff(Display_Buffer);
}*/

/*void display_number(uint8_t number){
  if(number < 20){
    M5.dis.displaybuff((uint8_t *)image_numbers[number]);
  } else {
    M5.dis.displaybuff((uint8_t *)image_dot);
  }
}*/
