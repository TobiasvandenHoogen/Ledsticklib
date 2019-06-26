#include "Ledsticklib.hpp"

Ledsticklib::Ledsticklib(uint8_t pin) :
configured(false), Byte(NULL), Latch_time(0) {
    confcolor(RGB);
    confpixels();
    confpin(pin);
}

void Ledsticklib::start(void){
pinMode(pin, OUTPUT);
digitalWrite(pin, LOW);
configured = true;
}

void Ledsticklib::confcolor(uint16_t color){
    red_offset = (color >> 4) & 0b11;
    green_offset = (color >> 2) & 0b11;
    blue_offset = color & 0b11;
}

void Ledsticklib::confpixels(){
free(Byte);
all_Bytes = 24;
if((Byte = (uint8_t *) malloc(all_Bytes))){
    memset(Byte, 0, all_Bytes);
    all_pixels = 8;
   }
}

void Ledsticklib::confpin(uint8_t p){
    if(configured) pinMode(pin, INPUT);
    pin = p;
    if(configured){
        pinMode(p, OUTPUT);
        digitalWrite(p, LOW);
    }
}

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

void Ledsticklib::advancedcolor(uint16_t pixel, uint32_t colors){
    if(pixel < numleds){
        uint8_t *p,
        red = (uint8_t)(colors >> 16),
        green = (uint8_t)(colors >> 8),
        blue = (uint8_t)colors;
        p = &Byte[pixel * 3];
        p[red_offset] = red;
        p[green_offset] = green;
        p[blue_offset] = blue;
    }
}

void Ledsticklib::reset(void){
    memset(Byte, 0, all_Bytes);
}


