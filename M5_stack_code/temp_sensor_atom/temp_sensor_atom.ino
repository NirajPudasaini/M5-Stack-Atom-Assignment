// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation. 
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h> 
#include "DHT.h"
#include "M5Atom.h"
#define PIN 27

#define DHTPIN 26     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

double accumulatorC = 0.0;
uint32_t readingsC = 0;
uint32_t averageC = 0;

double accumulatorF = 0.0;
uint32_t readingsF = 0;
uint32_t averageF = 0;

float tf = 0;
float tc = 0;

char* temp = "";

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };
int x    = matrix.width();
int pass = 0;

char *units[] = {" °F", " °C"};
uint8_t selectedUnit = 0;  

uint8_t tempMode = 0; 

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]); 
  dht.begin();
  M5.begin(true, false, true);
  delay(50);
}



void loop() {

   // reset sensor data after 24 hours
    static uint32_t prevTime;
    uint32_t curTime = millis();
  
    if ( curTime - prevTime >= 24*60*60*1000UL )
    {
      prevTime = curTime;
  
      // do things every 24h here
      accumulatorC = 0.0;
      readingsC = 0;
      averageC = 0;
      
      accumulatorF = 0.0;
      readingsF = 0;
      averageF = 0;
    }
  
    if (M5.Btn.pressedFor(1500))
    { 
        selectedUnit++;
        if (selectedUnit >= 2)
        {
            selectedUnit = 0;
        }
        delay(1000);
    }

    if (M5.Btn.pressedFor(3000))
    {
 
        tempMode++;
        if (tempMode >= 2)
        {
            tempMode = 0;
        }
        delay(1000);
    }


      // Read temperature as Celsius (the default)
      float c = dht.readTemperature();
      // Read temperature as Fahrenheit (isFahrenheit = true)
      float f = dht.readTemperature(true);

    if (isnan(c) || isnan(f)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        temp = 0; 
    }else{ 
        tc = c ;
        tf = f;
        collectDataC(c);
        collectDataF(f);
        delay(1000);
    
    }
    
 
    if(tempMode){ 
      displayTemp();
    }else{
      displayAvgTemp();
    }
    
    delay(50);
    M5.update(); 
} 

void displayTemp(){

  matrix.fillScreen(0);
  matrix.setCursor(x, 0); 
  char tempChar[10];
  if(selectedUnit == 0){
    snprintf (tempChar, sizeof(tempChar), "%f", tc);
    strcat( temp, tempChar );
    strcat( temp, units[selectedUnit] );
  }else{
    snprintf (tempChar, sizeof(tempChar), "%f", tf); 
    strcat( temp, tempChar );
    strcat( temp, units[selectedUnit] );
  }
  
  matrix.print(temp);
  if(--x < -96) {
    x = matrix.width();
    if(++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(80);
} 

void displayAvgTemp(){

  matrix.fillScreen(0);
  matrix.setCursor(x, 0); 
  char tempChar[10]; 
  if(selectedUnit == 0){
    snprintf (tempChar, sizeof(tempChar), "%f", averageC); 
    strcat( temp, tempChar );
    strcat( temp, units[selectedUnit] );
  }else{
    snprintf (tempChar, sizeof(tempChar), "%f", averageF); 
    strcat( temp, tempChar );
    strcat( temp, units[selectedUnit] );
  }
  
  matrix.print(temp);
  if(--x < -96) {
    x = matrix.width();
    if(++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(80);
} 

double collectDataC(double value)
{
    accumulatorC += value; // add to accumulator
    readingsC++; // increment count
    averageC = (accumulatorC / readingsC); // return current average
}

double collectDataF(double value)
{
    accumulatorF += value; // add to accumulator
    readingsF++; // increment count
    averageF = (accumulatorF / readingsF); // return current average
}
