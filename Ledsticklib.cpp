/*!
@file Ledsticklib.cpp
*This is the source file of the Ledsticklib library. 
 */
#include "Ledsticklib.hpp"

/*!
@brief
*This is the constructor of the class. In the contructor are three types configured.
*The color, the pixellenght and the pin.
@param
*pin  The pin which de ledstick is connected to.
*/
Ledsticklib::Ledsticklib(uint8_t pin) :
configured(false), Byte(NULL), Latch_time(0) {
    confcolor(RGB);
    confpixels();
    confpin(pin);
}

/*!
@brief
*This function will set the Ledstick as output and is required for the basic
*and special functions.
*/
void Ledsticklib::start(void){
pinMode(pin, OUTPUT);
digitalWrite(pin, LOW);
configured = true;
}

/*!
@brief
 This function configures the colorvalue and is part of the constructor.
@param
 color   this is the RBG value declared in the header file
*/
void Ledsticklib::confcolor(uint16_t color){
    red_offset = (color >> 4) & 0b11;
    green_offset = (color >> 2) & 0b11;
    blue_offset = color & 0b11;
}


/*!
@brief
 This function configures the pixel and allocates all_Bytes.
 @param
*/
void Ledsticklib::confpixels(){
free(Byte);
all_Bytes = 24;
if((Byte = (uint8_t *) malloc(all_Bytes))){
    memset(Byte, 0, all_Bytes);
    all_pixels = 8;
   }
}

/*!
@brief
*This function configures the pin and sets the Ledstick as output.
@param
pin  The pin which de ledstick is connected to.
*/
void Ledsticklib::confpin(uint8_t p){
    if(configured) pinMode(pin, INPUT);
    pin = p;
    if(configured){
        pinMode(p, OUTPUT);
        digitalWrite(p, LOW);
    }
}

/*!
@brief 
*This function sends the set byte(which is determined by advancedcolor)
*to the Ledstick.
*/
void Ledsticklib::flush(void){
noInterrupts();

auto SCALE = VARIANT_MCK / 2 / 1000000;
auto INST = 2 * F_CPU / VARIANT_MCK;
auto TH0 = (0.40 * SCALE + 0.5) - (5 * INST);
auto TH1 = (0.80 * SCALE + 0.5) - (5 * INST);
auto CYCLE = (1.25 * SCALE + 0.5) - (5 * INST);

int pinmask, time0bit, time1bit, period, t;
Pio  *port;
volatile WoReg *portset, *portreset, *timevalue, *timeclear;
uint8_t *b, *endbyte, bits, mask;

pmc_set_writeprotect(false);
pmc_enable_periph_clk((uint32_t)TC3_IRQn);
TC_Configure(TC1, 0,
 TC_CMR_WAVE | TC_CMR_WAVSEL_UP | TC_CMR_TCCLKS_TIMER_CLOCK1);
TC_Start(TC1, 0);

pinmask = g_APinDescription[pin].ulPin;
port = g_APinDescription[pin].pPort;
portset = &(port->PIO_SODR);
portreset = &(port->PIO_CODR);
timevalue = &(TC1->TC_CHANNEL[0].TC_CV);
timeclear = &(TC1->TC_CHANNEL[0].TC_CCR);
b = Byte;
endbyte = b + all_Bytes;
bits = *b++;
mask = 0x80;
 
time0bit = TH0;
time1bit = TH1;
period = CYCLE;

for(t = time0bit;; t = time0bit){
    if(bits & mask) t = time1bit;
    while(*timevalue < period);
    *portset = pinmask;
    *timeclear = TC_CCR_CLKEN | TC_CCR_SWTRG;
    while(*timevalue < t);
    *portreset = pinmask;
    if(!(mask >>=1)){
        if(b >= endbyte) break;
        bits = *b++;
        mask = 0x80;
    }
}
    while(*timevalue < period);
    TC_Stop(TC1, 0);
    interrupts();
    Latch_time = micros();
}

/*!
@brief advancedcolor
*This function sets the variabele byte to a colorvalue of a pixel.
param
pixel  The pixel of the ledstick from 0 to 7. Give 8 for all pixels.
param c      The 32 bit color value which can be used to blink the pixel in a different
       color.
*/
void Ledsticklib::advancedcolor(uint16_t pixel, uint32_t colors){
    if(pixel < 8){
        uint8_t *p,
        red = (uint8_t)(colors >> 16),
        green = (uint8_t)(colors >> 8),
        blue = (uint8_t)colors;
        p = &Byte[pixel * 3];
        p[red_offset] = red;
        p[green_offset] = green;
        p[blue_offset] = blue;
    }
    if(pixel == 8){
        uint8_t *p,
        red = (uint8_t)(colors >> 16),
        green = (uint8_t)(colors >> 8),
        blue = (uint8_t)colors;
        for(uint16_t i = 0; i < 8; i++){
        p = &Byte[i * 3];
        p[red_offset] = red;
        p[green_offset] = green;
        p[blue_offset] = blue;
    }
}
}


void Ledsticklib::simplecolor(uint16_t pixel, char color[]){
}

/*!
@brief 
 This function repeatedly turns a pixel on and off and has required and 
 optional parameters.
@param
pixel  The pixel of the ledstick from 0 to 7. Give 8 for all pixels.
@paramc      The 32 bit color value which can be used to blink the pixel in a different
       color.
@paramd      Delay which can be used to blink the pixel faster/slower.
*/
void Ledsticklib::blinkled(uint16_t pixel){
        this->reset();
        this->advancedcolor(pixel, color(100,50,50));
        this->flush();
        delay(500);
        this->advancedcolor(pixel, color(0,0,0));
        this->flush();
         delay(500);
}

void Ledsticklib::blinkled(uint16_t pixel, uint32_t c){
        this->reset();
        this->advancedcolor(pixel, c);
        this->flush();
        delay(500);
        this->advancedcolor(pixel, color(0,0,0));
        this->flush();
         delay(500);
}

void Ledsticklib::blinkled(uint16_t pixel, int d){
        this->reset();
        this->advancedcolor(pixel, color(50,50,50));
        this->flush();
        delay(d);
        this->advancedcolor(pixel, color(0,0,0));
        this->flush();
        delay(d);
}

void Ledsticklib::blinkled(uint16_t pixel, uint32_t c, int d){
        this->reset();
        this->advancedcolor(pixel, c);
        this->flush();
        delay(d);
        this->advancedcolor(pixel, color(0,0,0));
        this->flush();
        delay(d);
}

/*!
@brief
This function turns on a pixel one at the time from left to right and has 
optional parameters.
@param c      The 32 bit color value which can be used to blink the pixel in a different
       color.
@param d      Delay which can be used to blink the pixel faster/slower.
*/
void Ledsticklib::kitt(){
    uint32_t c = color(50, 50 ,50);
    for(int i = 0; i < 8; i++){
        reset();
        this->advancedcolor(i, c);
        this->flush();
        delay(500);
    }
     for(int i = 7; i >= 0; i--){
        reset();
        this->advancedcolor(i, c);
        this->flush();
        delay(50);
    }
}

void Ledsticklib::kitt(uint32_t c){
    for(int i = 0; i < 8; i++){
        reset();
        this->advancedcolor(i, c);
        this->flush();
        delay(50);
    }
     for(int i = 7; i >= 0; i--){
        reset();
        this->advancedcolor(i, c);
        this->flush();
        delay(500);
    }
}

void Ledsticklib::kitt(int d){
    uint32_t c = color(50, 50 ,50);
    for(int i = 0; i < 8; i++){
        reset();
        this->advancedcolor(i, c);
        this->flush();
        delay(d);
    }
     for(int i = 7; i >= 0; i--){
        reset();
        this->advancedcolor(i, c);
        this->flush();
        delay(d);
    }
}

void Ledsticklib::kitt(uint32_t c, int d){
    for(int i = 0; i < 8; i++){
        reset();
        this->advancedcolor(i, c);
        this->flush();
        delay(d);
    }
     for(int i = 7; i >= 0; i--){
        reset();
        this->advancedcolor(i, c);
        this->flush();
        delay(d);
    }
}

/*!
@brief
*This function changes color of each pixel every 100 miliseconds.
@param
*pixel  The pixel of the ledstick from 0 to 7. Give 8 for all pixels.
*/
void Ledsticklib::cyclecolor(uint16_t pixel){
    int redvalue = 50;
    int greenvalue = 0;
    int bluevalue = 0;
    int totalcycle = 6;
    for(int i = 0; i < totalcycle; i++){
        this->reset();
        uint32_t c = color(redvalue, greenvalue, bluevalue);
        this->advancedcolor(pixel, c);
        this->flush();
        delay(100);
       if(i < 1){
           greenvalue = 50;
       }
        else if (i < 2){
          redvalue = 0;
        }
        else if (i < 3){
            bluevalue = 50;
        }
        else if (i < 4){
            greenvalue = 0;
        }
        else if (i < 5){
            redvalue =  50;
        }
        else if (i < 6){
            bluevalue = 0;
        }
      
}
}
/*!
@brief
*This function changes color of each pixel but instead of the function 
*cyclecolor it changes color gradually instead of suddenly.
@param
*pixel  The pixel of the ledstick from 0 to 7. Give 8 for all pixels.
*/
void Ledsticklib::rainbow(uint16_t pixel){
    int redvalue = 50;
    int greenvalue = 0;
    int bluevalue = 0;
    int totalcycle = 300;
    for(int i = 0; i <= totalcycle; i++){
        this->reset();
        uint32_t c = color(redvalue, greenvalue, bluevalue);
        this->advancedcolor(pixel, c);
        this->flush();
        delay(25);
       if(i < 51){
           greenvalue++;
       }
        else if (i < 101){
          redvalue--;
        }
        else if (i < 151){
            bluevalue++;
        }
        else if (i < 201){
            greenvalue--;
        }
        else if (i < 251){
            redvalue++;
        }
        else if (i < 301 ){
            bluevalue--;
        }
      
}
}

/*!
@brief
*This function resets Byte so that new bytes can be send again.
*/
void Ledsticklib::reset(void){
    memset(Byte, 0, all_Bytes);
}

