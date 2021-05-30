//Librariess of M5Stack and DHT
#include <M5Stack.h>
#include <SimpleDHT.h>
 
// define colors
#define BLACK           0x0000
#define RED             0xF800
#define CYAN            0x07FF
#define YELLOW          0xFFE0 
#define WHITE           0xFFFF
 
#define DHTPIN 5
 
//constructor of the object to communicate with the sensor
SimpleDHT22 dht;
 
//variable responsible for counting the number of readings taken and the X-axis value indicator
int currentReading = 1;


#define POS_X       30
#define POS_Y       3
#define Height      180
#define Length 270
#define POS_X_DATA 30
#define POS_Y_DATA 200
 

int humidity = 0;
int temperature = 0;
 
int exampleLine = 20;
int fator = 1; 

void setup(void) {
  Serial.begin(115200);

  M5.begin();
 
  M5.Lcd.fillScreen(BLACK);
 
  M5.Lcd.drawFastVLine(POS_X,POS_Y, Heigtht,WHITE);
  M5.Lcd.drawFastHLine(POS_X,Height+1,Length,WHITE); 
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(WHITE);
 
 
  M5.Lcd.setCursor(POS_X_DATA, POS_Y_DATA);
  M5.Lcd.print("T: "); //temperature
  M5.Lcd.setCursor(POS_X_DATA+105, POS_Y_DATA);
  M5.Lcd.print(" U: "); //humidity
}
