#include <Ledsticklib.hpp> 

Ledsticklib leds1(6); //Digital pin 6
auto c = Ledsticklib::color(0, 0, 50); //Color blue

void setup() {
  leds1.start(); //Set pin as output

}

void loop() {
  leds1.reset(); //Reset sent bytes
  leds1.advancedcolor(0, c); //Set pixel and color in byte. Give 8 in first parameter to turn all pixels on.
  leds1.flush(); //Sent byte
  delay(50); //50 miliseconds delay

}
