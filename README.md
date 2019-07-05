# Ledsticklib
This is a library designed for the Adafruit Neopixel 8x50 led stick. But other ws2812b led sticks can also be used for this library. Ledsticklib is an library designed for a 8x50 ws21812 led stick. In this library you can set basic functions on a ledstick such as turning a pixel on and change the color of the pixel. There are also special functions such as blink, kitt and rainbow. 

The other library I made is Ledsticks and has functions based of Ledsticklib. The only difference between Ledsticks and Ledsticklib is that the purpose of Ledsticks is to control multible ledsticks at once in an easier and more flexible way.

The application I made is called catch. To make this application work you need two pull down resitors and at least seven ledsticks. The aim of this game is to catch red balls with the two blue pixels in the ledstick below. To start the game press the most left button and to control the blue pixels you use both buttons. If you missed 5 red balls you lose and the game will return to waiting mode.


There are three ways to use Ledsticklib:

1: The Arduino IDE. This is the easiest way but I don't recommend it since the code editor is not very flexible and can be very annoying sometimes. 

2. Visual studio code. This is in my opinion the most recommended way because i think that Visual studio code is the most flexible and user oriented code editor. But since the library uses Arduino functions and port manipulation it is recommended that you dowload the Arduino IDE and the Arduino extension. The link below is a walktrough on how you can dowload and configure the Arduino library on Visual studio code.
https://medium.com/home-wireless/use-visual-studio-code-for-arduino-2d0cf4c1760b

3. Other code editors. Because i haven't got any expierence with other code editors i don't have a excact walktrough on how you implement Ledsticklib on other code editors. But be sure to download the Arduino IDE and include the Arduino.h file(makefile is recommended) in your code.

Some of this code has been inspired by the following people and repositories:

https://github.com/adafruit/Adafruit_NeoPixel

https://github.com/FastLED/FastLED

https://wp.josh.com/2014/05/13/ws2812-neopixels-are-not-so-finicky-once-you-get-to-know-them/
