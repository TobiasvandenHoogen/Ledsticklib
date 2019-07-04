#include "Ledsticks.hpp"

void Ledsticks::start(){
    for(int i = 0; i < size; i++){
        array[i].start();
    }
}

void Ledsticks::flush(){
    for(int i = 0; i < size; i++){
        array[i].flush();
    }
}


void Ledsticks::advancedcolor(uint8_t stick, uint8_t pixel, int redvalue
,int greenvalue, int bluevalue){
    auto c = Ledsticklib::color(redvalue, greenvalue, bluevalue);
    int firststick = 0;
    int laststick = size;
    if(stick < 8){
        firststick = stick;
        laststick = stick;
    }
    for(int i = firststick; i <= laststick; i++){
        array[i].advancedcolor(pixel, c);
    }
}

void Ledsticks::reset(){
      for(int i = 0; i < size; i++){
        array[i].reset();
    }
}

void Ledsticks::blinkled(uint8_t stick, uint8_t pixel){
    auto w = Ledsticklib::color(50, 50, 50);
    auto c = Ledsticklib::color(0, 0, 0);
    int firststick = 0;
    int laststick = size;
    this->reset();
    if(stick < 8){
        firststick = stick;
        laststick = stick;
    }
    for(int i = firststick; i <= laststick; i++){
        array[i].advancedcolor(pixel, w);
    }
    this->flush();
    delay(500);
    this->reset();
    for(int i = firststick; i <= laststick; i++){
        array[i].advancedcolor(pixel, c);
    }
    this->flush();
    delay(500);


}


void Ledsticks::horizontalkitt(){
 auto w = Ledsticklib::color(50, 50, 50);
 for(int i = 0; i < 8; i++){
 this->reset();
 for(int j = 0; j < size; j++){
     array[j].advancedcolor(i, w);
 }
 this->flush();
 delay(50);
 }
for(int i = 6; i >= 0; i--){
this->reset();
for(int j = 0; j < size; j++){
     array[j].advancedcolor(i, w);
 }
 this->flush();
 delay(50);
 }
 
}

void Ledsticks::flashing_kitt(){
 auto w = Ledsticklib::color(50, 50, 50);
 auto c = Ledsticklib::color(0, 0, 0);
 for(int i = 0; i < size; i++){
     array[i].advancedcolor(8, w);
     this->flush();
     delay(100);
     this->reset();
     array[i].advancedcolor(8, c);
     this->flush();
     delay(50);
     this->reset();
    delay(50);
 }
}
void Ledsticks::cyclecolor(uint8_t stick, uint8_t pixel){
    int red = 50;
    int green = 0;
    int blue = 0;
    int totalcycle = 6;
    for(int i = 0; i < totalcycle; i++){
        auto w = Ledsticklib::color(red, green, blue);
        this->reset();
        int firststick = 0;
        int laststick = size;
        if(stick < 8){
        firststick = stick;
        laststick = stick;
        }
        for(int j = firststick; j <= laststick; j++){
        array[j].advancedcolor(pixel, w);
        this->flush();
        }
       if(i < 1){
        green = 50;
       }
        else if (i < 2){
          red = 0;
        }
        else if (i < 3){
            blue = 50;
        }
        else if (i < 4){
            green = 0;
        }
        else if (i < 5){
            red =  50;
        }
        else if (i < 6){
            blue = 0;
        }
        delay(100);
}
}

void Ledsticks::rainbow(uint8_t stick, uint8_t pixel){
    int redvalue = 50;
    int greenvalue = 0;
    int bluevalue = 0;
    int totalcycle = 300;
    for(int i = 0; i < totalcycle; i++){
        auto c = Ledsticklib::color(redvalue, greenvalue, bluevalue);
        this->reset();
        int firststick = 0;
        int laststick = size;
        if(stick < 8){
        firststick = stick;
        laststick = stick;
        }
        for(int j = firststick; j <= laststick; j++){
        array[j].advancedcolor(pixel, c);
        this->flush();
        }
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
          delay(25);
      
}
}
void Ledsticks::line(int xy1[2], int xy2[2]){
auto w = Ledsticklib::color(50, 50, 50);
for(int i = xy1[1]; i <= xy2[1]; i++){
for(int j = xy1[0]; j <= xy2[0]; j++){
    array[0].advancedcolor(j, w);
}
}
this->flush();
delay(50);
this->reset();
}