#include "Ledsticklib.hpp"
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

class application{
protected:
int leftposition = 3;
int rightposition = 4;
int* sticks;
const int button1 = 4; 
const int button2 = 5; 
int buttonState = 0; 
bool conf = false;
bool start = false;
int lives = 3;
public:
application(int* sticks):
sticks (sticks )
{}
void main_application();
void waiting();
void fall();
void apple(int number);
void basket();
void test();
};

#endif