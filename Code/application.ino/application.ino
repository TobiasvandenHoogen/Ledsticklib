#include "application.hpp"

int pins[7] = {12, 11, 10, 9, 8, 7, 6};


application part0(pins);       
void setup() {
}

void loop() {

  part0.waiting();
}