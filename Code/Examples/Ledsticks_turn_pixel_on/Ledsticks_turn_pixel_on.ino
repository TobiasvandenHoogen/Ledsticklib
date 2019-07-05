#include "Ledsticks.hpp"

Ledsticklib leds[7] = {
    Ledsticklib(12),
    Ledsticklib(11),
    Ledsticklib(10),
    Ledsticklib(9),
    Ledsticklib(8),
    Ledsticklib(7),
    Ledsticklib(6)
};

Ledsticks sticks(leds, 7);

void setup() {
  sticks.start();

}

void loop() {
  sticks.advancedcolor(3, 5, 0, 50, 50);
}
