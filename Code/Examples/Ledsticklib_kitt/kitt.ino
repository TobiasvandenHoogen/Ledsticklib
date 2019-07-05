#include <Ledsticklib.hpp> 

Ledsticklib leds1(6); //Digital pin 6
auto c = Ledsticklib::color(0, 0, 50); //Color blue
int d = 25; //delay is 25 miliseconds
void setup() {
  leds1.start(); //Set pin as output

}

void loop() {
  leds1.reset(); //Reset sent bytes
  leds1.kitt(); //Turn on one pixel at the time and goes on the stick from left to right. You can also put in color and delay as optional parameters like these examples below.
  //leds1.kitt(c) color as extra parameter
  //leds1.kitt(d) delay as extra parameter
  //leds1.kitt(c, d) color and delay as extra parameter
  leds1.flush(); //Sent byte
  delay(50); //50 miliseconds delay

}
