#ifndef LEDSTICKLIB_HPP
#define LEDSTICKLIB_HPP
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif 

#define RGB ((1<<6) | (1<<4) | (0<<2) | (2))


class Ledsticklib{
protected:
boolean configured;
uint8_t pin;
uint16_t all_pixels;
uint8_t *Byte;  
uint16_t all_Bytes;
uint32_t Latch_time;
uint8_t red_offset;
uint8_t green_offset;
uint8_t blue_offset;

public:
Ledsticklib(uint8_t pin);

void start(void);

void confpin(uint8_t p);

void confcolor(uint16_t color);

void confpixels();

void advancedcolor(uint16_t pixel, uint32_t color);

void simplecolor();

void flush(void);

void reset(void);

static uint32_t color(uint8_t red, uint8_t green, uint8_t blue){
    return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
}


};


#endif