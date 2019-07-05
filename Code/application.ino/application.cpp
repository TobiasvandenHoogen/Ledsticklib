#include "application.hpp"

void application::main_application(){
 if(start == false){
    this->waiting(); 
 }
}

void application::waiting(){
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

void application::fall(){
int randomnumber = random(1, 7);
int ledstickon = 6;
this->apple(randomnumber);
}

void application::apple(int pixel){
  for(int i = 6; i >= 1; i--){
    int pin = sticks[i];
    Ledsticklib stick = Ledsticklib(pin);
   if(i == 1){
      if((leftposition != pixel) && (rightposition != pixel)){
        lives--;
      }
    }
if(lives <= 0){
  lives = 3;
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

void application::basket(){
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
