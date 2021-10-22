# Introduction to Robotics, FMI UniBuc 2021
<p align="right" >  <i> author: Burța Mihai-Cătălin </i> </p>

## Description

  <p> This repository was created in order to store, monitor and showcase my learning process, while taking the "Introduction to Robotics" Course from FMI UniBuc. </p>

## Homeworks

### 1. Homework 0
  <p> Installed Arduino IDE and created this repository for monitoring and storing all the files related to the course (Code, Images, Homeworks etc.) </p>
  
### 2. Homework 1 - Controllable RGB led
  <p> <b> Components: </b>  RBG led (1 minimum), potentiometers (3 minimum), re-sistors and wires (per logic) </p>
  <p> <b> Technical Task: </b> Use a separat potentiometer in controlling each of thecolor of the RGB led (Red,Green andBlue).  The control must be donewithdigital electronics(aka you must read the value of the potentiome-ter with Arduino, and write a mapped value to each of the pins connectedto the led. </p>

![hw1_setup](https://github.com/cbrt-mihai/IntroductionToRobotics/blob/main/Homeworks/Homework1/setup.jpeg?raw=true)

  <p> Link to a video showcasing the functionality: https://youtu.be/tUqZCBJ2I1U </p>
  <p> I've made a controllable RGB led using 3 potentiometers and some code written in the Arduino IDE. I get the signal from each of the potentiometers. The signals are in range 0-1023, and the led accepts a range 0-255. Using the map() function, I've mapped all the signals individually to the correct 0-255 range and fed them to the RGB led through each of their respective pins. </p>
