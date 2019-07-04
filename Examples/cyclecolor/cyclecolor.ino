#include <Ledsticklib.hpp> 

Ledsticklib leds1(6); //Digital pin 6
void setup() {
  leds1.start(); //Set pin as output

}

void loop() {
  leds1.cyclecolor(0); //Changes the color of the pixel. Give 8 for all pixels.
  delay(50); //50 miliseconds delay

}
