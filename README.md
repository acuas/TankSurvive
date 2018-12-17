# TankSurvive

An arduino game designed on a 8 x 8 matrix and 16 x 2 LCD.

## Prerequisites 
##### Pyshical Parts :
* Arduino UNO
* 1088AS LED Matrix
* MAX7219 Driver
* 16x2 LCD Display
* Joystick 
* 100UF 50V
* 104 ceramic capacitor

##### Software :
* [Arduino IDE](https://www.arduino.cc/en/main/software)

##### Installing :

First, move folders [LcdDisplayVertical](./LcdDisplayVertical), [LedMatrix](./LedMatrix), [Timer](./Timer) to **libraries** folder create by Arduino IDE.
Then, open the arduino file [Project.ino](./Project.ino) with Arduino IDE and click on upload button.

## Gameplay

* To start the game the playes must press on the joystick ; 
* The player must move to the left and right using joystick to avoid the obstacles that will come to him. The playes has 3 lives when the game starts;
* The game has 9 levels. There will be more obstacles at each level, but from level 5 the speed of the game will accelerate.
* [Demonstrative video](https://photos.app.goo.gl/PeZVG7dqJeiL2fMy9)

## Built with

* [Arduino IDE](https://www.arduino.cc/en/main/software)
* [Arduino Timer modified](https://png-arduino-framework.readthedocs.io/timer.html)

## Author

[Auras Popescu](https://www.linkedin.com/in/auras-popescu-29408bb9/)