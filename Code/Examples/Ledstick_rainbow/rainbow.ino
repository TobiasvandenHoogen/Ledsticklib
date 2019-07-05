#include <Ledsticklib.hpp> 

Ledsticklib leds1(6); //Digital pin 6
void setup() {
  leds1.start(); //Set pin as output

}

void loop() {
  leds1.rainbow(0); //Gradually changes color of the pixel. Give 8 in parameter for all pixels.
  delay(50); //50 miliseconds delay
}
