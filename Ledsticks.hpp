#include "Ledsticklib.hpp"

class Ledsticks{
protected:
int* array[];
int redvalue;
int greenvalue
int bluevalue;
public:
void start();
void flush();
void advancedcolor(uint_t stick, uint8_t pixel, 
                    int redvalue, int greenvalue, int bluevalue);
void reset();
};