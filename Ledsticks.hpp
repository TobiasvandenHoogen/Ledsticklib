#include "Ledsticklib.hpp"

class Ledsticks{
protected:
Ledsticklib* array;
int size;
int redvalue;
int greenvalue;
int bluevalue;
int xy[2];
public:
Ledsticks(Ledsticklib* array, int size):
array ( array ),
size ( size )
{}
void start();
void flush();
void advancedcolor(uint8_t stick, uint8_t pixel, int redvalue,
int greenvalue, int bluevalue);
void reset();
void blinkled(uint8_t stick, uint8_t pixel);
void horizontalkitt();
void flashing_kitt();
void cyclecolor(uint8_t stick, uint8_t pixel);
void rainbow(uint8_t stick, uint8_t pixel);
void line(int xy1[2], int xy2[2]);
};