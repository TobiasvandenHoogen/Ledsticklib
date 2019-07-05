/*!
@file Ledsticklib.cpp
*This is the source file of the Ledsticks library. 
 */

#include "Ledsticks.hpp"

/*!
@brief
*This function will set the Ledsticks as output and is required for the basic
*and special functions.
*/
void Ledsticks::start(){
    for(int i = 0; i < size; i++){
        array[i].start();
    }
}

/*!
@brief 
*This function sends the set byte(which is determined by advancedcolor)
*to the Ledsticks.
*/
void Ledsticks::flush(){
    for(int i = 0; i < size; i++){
        array[i].flush();
    }
}

/*!
@brief advancedcolor
*This function sets the variabele byte to a colorvalue of a pixel.
@param
stick The stick which is in the array of Ledsticks.
@param
pixel  The pixel of the ledstick from 0 to 7. Give 8 for all pixels.
@param 
redvalue The value on how red the pixel should be (1 to 8 bits)
@param
greenvalue The value on how green the pixel should be (1 to 8 bits)
@param
bluevalue The value on how blue the pixel should be (1 to 8 bits)
*/
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

/*!
@brief
*This function resets Byte so that new bytes can be send again.
*/
void Ledsticks::reset(){
      for(int i = 0; i < size; i++){
        array[i].reset();
    }
}

/*!
@brief 
 This function repeatedly turns a pixel and compared to the blinkled function 
 in the Ledsticklib library you can also give the stick of the array in the 
 parameter.
@param
stick The stick which is in the array of Ledsticks.
@param
pixel  The pixel of the ledstick from 0 to 7. Give 8 for all pixels.
@param
*/
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



/*!
@brief
This function turns on a pixel of each stick one at the time from left to right.
@param
*/
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
/*!
@brief
This function is like horizontalkitt but vertical and has flasing lights.
Don't try this if you are sensitive to flashing lights. */
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

/*!
@brief
*This function changes color on a pixel every 100 miliseconds.
@param
stick The stick which is in the array of Ledsticks.
@param
*pixel  The pixel of the ledstick from 0 to 7. Give 8 for all pixels.
*/
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

/*!
@brief
*This function changes color of each pixel but instead of the function 
*cyclecolor it changes color gradually instead of suddenly.
@param
stick The stick which is in the array of Ledsticks.
@param
*pixel  The pixel of the ledstick from 0 to 7. Give 8 for all pixels.
*/
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