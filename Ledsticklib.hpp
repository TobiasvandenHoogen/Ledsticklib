/*!
@file Ledsticklib.hpp
*This is the header file of the Ledsticklib Library. The functions declared
in the class are elaborated in the cpp file.

@mainpage Library for driving Adafruit Neopixel 8x50 RGB led sticks and other ws

 */




#ifndef LEDSTICKLIB_HPP
#define LEDSTICKLIB_HPP
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif 


#define RGB ((1<<6) | (1<<4) | (0<<2) | (2))

/*!
@brief
*This is the class for one Ledstick. In the access specifier protected
*are the variables stored including the byte which will be sent to the 
*Ledstick and the pin. In the acces specifier public are the functions stored 
*which are divided into basic functions and special functions;
*/

class Ledsticklib{
protected:
boolean configured;
uint8_t pin;
uint8_t *Byte;  
uint16_t all_Bytes;
uint32_t Latch_time;
uint8_t red_offset;
uint8_t green_offset;
uint8_t blue_offset;

public:
Ledsticklib(uint8_t pin);

//Basic functions
void start(void);

void confpin(uint8_t p);

void confcolor(uint16_t color);

void confpixels();

void advancedcolor(uint16_t pixel, uint32_t color);

void simplecolor(uint16_t pixel, char color[]);

void flush(void);

void reset(void);

static uint32_t color(uint8_t red, uint8_t green, uint8_t blue){
    return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
}

//Special functions
void blinkled(uint16_t pixel);

void blinkled(uint16_t pixel, uint32_t c);

void blinkled(uint16_t pixel, int d);

void blinkled(uint16_t pixel, uint32_t c, int d);

void blinkall();

void kitt();

void kitt(uint32_t c);

void kitt(int d);

void kitt(uint32_t c, int d);

void cyclecolor();

void rainbow(uint16_t pixel);

};

#endif