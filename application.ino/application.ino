#include "Ledsticklib.hpp"

#include "Ledsticklib.hpp"

class application{
private:
int leftposition = 3;
int rightposition = 4;
int* sticks;
const int button1 = 4; 
const int button2 = 5; 
int buttonState = 0; 
bool conf = false;
bool start = false;
int lives = 5;
public:
application(int* sticks):
sticks (sticks )
{}

void main_application(){
 if(start == false){
    this->waiting(); 
 }
 else if( start == true){
   this->fall();
 }
}
void waiting(){
if(start == false){
for(int i = 0; i < 8; i++){
  Ledsticklib pixels = Ledsticklib(sticks[i]);
  pixels.start();
  pixels.kitt(25);
  pinMode(button1, INPUT);
  int buttonState1 = digitalRead(button1);
  if (buttonState1 == HIGH) {
   start = true;  
   delay(100);
   break;
  }
}
}
else{
  this->fall();
}
}
void fall(){
int randomnumber = random(1, 7);
int ledstickon = 6;
this->apple(randomnumber);
}

void apple(uint16_t pixel){
    for(int i = 6; i >= 1; i--){
    int pin = sticks[i];
    Ledsticklib stick = Ledsticklib(pin);
   if(i == 1){
      if((leftposition != pixel) && (rightposition != pixel)){
        lives--;
      }
    }
if(lives <= 0){
  lives = 5;
  start = false;
  break;
}
    this->basket();
    auto r = Ledsticklib::color(50, 0, 0);
    auto w = Ledsticklib::color(0, 0, 0);
    stick.start();
    stick.advancedcolor(pixel, r);
    stick.flush();
    delay(350);
    stick.reset();
    stick.advancedcolor(pixel, w);
    stick.flush();
    }
}

void basket(){
Ledsticklib leds(sticks[0]);
leds.reset();
auto c = Ledsticklib::color(0, 0, 50);
if(conf == false){
leds.start();
pinMode(button1, INPUT);
pinMode(button2, INPUT);
conf = true;
}
 leds.advancedcolor(leftposition, c);
 leds.advancedcolor(rightposition, c);
 int buttonState1 = digitalRead(button1);
 int buttonState2 = digitalRead(button2);
 leds.flush();
 if ((buttonState1 == HIGH) && (leftposition > 0)) {
   leftposition--;
   rightposition--;
  }
 if ((buttonState2 == HIGH) && (rightposition <7)) {
   leftposition++;
   rightposition++;
  }
}

void countdown(){
    auto w = Ledsticklib::color(0, 0, 0);
}

void wipeallpixels(){
  auto w = Ledsticklib::color(0, 0, 0);
  for(int i = 0; i < 8; i++){
     int pinnumber = sticks[i];
      Ledsticklib stick = Ledsticklib(pinnumber);
      stick.start();
      stick.advancedcolor(8, w);
      stick.flush();
  }
}

void line(int*xy1, int*xy2){
auto w = Ledsticklib::color(0, 50, 0);
for(int j = 0; j < xy2[1]; j++){
int pinnumber = sticks[j];
Ledsticklib stick = Ledsticklib(pinnumber);
stick.start();
for(int i = xy1[0]; i <= xy2[0]; i++){
      stick.advancedcolor(i, w);
}
stick.flush();
delay(10);
stick.reset();
}
}
};

int pins[7] = {12, 11, 10, 9, 8, 7, 6};
int xy1[2] = {0,0};
int xy2[2] = {4, 0};

application part0(pins);       
void setup() {
}

void loop() {

  part0.waiting();
}