/*!
@file Ledsticks.hpp
*This is the header file of the Ledsticks Library. The functions declared
in the class are elaborated in the cpp file.
*/

#include "Ledsticklib.hpp"

/*!
@brief
This is the class for multible ledsticks. In the access specifier protected
are the variables stored including the size of the sticks and the colorvalues.
In the public section there are basic functions which are needed to run the code
and there are special functions which are optional. */

class Ledsticks{
protected:
Ledsticklib* array;
int size;
int redvalue;
int greenvalue;
int bluevalue;
int xy[2];
public:

/*!
@brief
This is the constructor in the class which initialise two vairables.
@param
array  An array of Ledsticklib objects.
@param 
size The size of the array. */
Ledsticks(Ledsticklib* array, int size):
array ( array ),
size ( size )
{}

//Basic functions
void start();

void flush();

void advancedcolor(uint8_t stick, uint8_t pixel, int redvalue,
int greenvalue, int bluevalue);

void reset();

//Special functions
void blinkled(uint8_t stick, uint8_t pixel);

void horizontalkitt();

void flashing_kitt();

void cyclecolor(uint8_t stick, uint8_t pixel);

void rainbow(uint8_t stick, uint8_t pixel);

};