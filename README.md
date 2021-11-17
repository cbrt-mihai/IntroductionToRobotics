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
  
  ### 3. Homework 2 - Streetlight/Semaphore
    
  <p> <b> Components: </b> 5 LEDs, 1 button, 1 buzzer, resistors and wires (per logic) </p>
  <p> <b> General  description: </b> Building  the  traffic  lights  for  a  crosswalk. You will use 2 LEDs to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green). See the states it needs to go through. It’s a traffic lights system for people and cars - don’t overthink it.The system has the following states: </p>
  <ol>
    <li> State 1 (default, reinstated after state 4 ends): green light for cars,red  light  for  people,  no  sounds.   Duration:  indefinite,  changed  bypressing the button. </li>
    <li> State 2 (initiated by counting down 10 seconds after a button press):the  light  should be yellow for cars, red for people and  no  sounds.Duration:  3 seconds. </li>
    <li> State 3 (iniated after state 2 ends): red for cars, green for people anda beeping sound from the buzzer at a constant interval. Duration: 10 seconds. </li>
    <li> State 4 (initiated after state 3 ends): red for cars, blinking green for people and a beeping sound from the buzzer, at a constant interval, faster than the beeping in state 3. Be  careful: pressing  the  button  in  any  state  other  than  state  1  shouldn't yield any actions. </li>
  </ol>
  
  ![hw2_setup](https://github.com/cbrt-mihai/IntroductionToRobotics/blob/main/Homeworks/Homework2/setup.jpg?raw=true)
  
  <p> Link to a video showcasing the functionality: https://youtu.be/ic3xrBNwLmI </p>
  
  ### 4. Homework 3 - EMF/Ghost Detector
  
  <p> <b> Components: </b> a buzzer and a 7-segment display (or a led bar / or 8 ledsin a row that simulate a led bar) </p>
  <p> <b> Task: </b> You should detect EMF (check body and near outlets.  DO NOT INSERT INTO THE OUTLET). It should printthe value on the 7-segment display (or light the led bar)andshould makea sound based on the intensity. </p>
  
  ![hw3_setup](https://github.com/cbrt-mihai/IntroductionToRobotics/blob/main/Homeworks/Homework3/setup.jpg?raw=true)
  
  <p> Link to a video showcasing the functionality: https://youtu.be/rdw2sTlxTsE </p>
  
  ### 5. Homework 4 - 4 Digit 7-Segment Display, controlled by Joystick
  
  <p> <b> Components: </b> a  joystick,  a  4  digit  7-segment  display,  a  74hc595  shift register </p>
  <p> <b> Task: </b> First  state:   you  can  use  a  joystick  axis  to  cycle  through  the  4digits; using the other axis does nothing.  A blinking decimal point showsthe current digit position.  When pressing the button (must use interruptfor  maximum  points!),  you  lock  in  on  the  selected  digit  and  enter  thesecond state.  In this state, the decimal point stays always on, no longerblinking and you can no longer use the axis to cycle through the 4 digits.Instead, using the other axis, you can increment on decrement the numberon the current digit.  Pressing the button again returns you to the previousstate.  For bonus, save the last value in eeprom and load it when startingarduino.  Also, keep in mind that when changing the number, you mustincrement it for each joystick movement - it should not work continuoslyincrement if you keep the joystick in one position. </p>
  
  ![hw4_setup](https://github.com/cbrt-mihai/IntroductionToRobotics/blob/main/Homeworks/Homework4/setup.jpg?raw=true)
  
  <p> Link to a video showcasing the functionality: https://youtu.be/Rzk1c3S49N4 </p>
