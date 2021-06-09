//include necessary library
#include <M5Stack.h>

const int ledPin = 21;
void setup() {
  // put your setup code here, to run once:
  // test code for github
  // niraj test branch
  //hi, i am testing
  //karl test comment
  // setup pin 5 (or whichever) as digital output pin
 pinMode (ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // LED on
  digitalWrite (ledPin, HIGH);  
  // after 10s (10000ms) wait, it will turn off
  delay(10000); 
  // LED off
  digitalWrite (ledPin, LOW); 
m5.update();
}
