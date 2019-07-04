#include <Ledsticklib.hpp> 

Ledsticklib leds1(6); //Digital pin 6
auto c = Ledsticklib::color(0, 0, 50); //Color blue
int d = 25; //delay is 25 miliseconds
void setup() {
  leds1.start(); //Set pin as output

}

void loop() {
  leds1.reset(); //Reset sent bytes
  leds1.blinkled(0);//Blinks pixel 0(give 8 for all pixels). You can also put the color and delay in this function. Like this example below.
  //leds1.blinkled(0, c) color as extra parameter
  //leds1.blinkled(0, d) delay as extra parameter
  //leds1.blinkled(0, c, d) color and delay as extra parameter
  leds1.flush(); //Sent byte
  delay(50); //50 miliseconds delay

}
