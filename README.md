# Arduino_solar_track
A self orienting solar panel that is able to track the sunlight.

Link to Tinkercad project: [Solar tracker](https://www.tinkercad.com/things/gveaNrLVcNt-solartrackarduino)

![alt text](https://github.com/grebano/Arduino_solar_track/blob/main/Photos/Real_implementation.jpg?raw=true)

## Code
The [code](/Arduino_Solar_Tracker2.ino) for this project is written in C++. It is provided in a .ino file, which can be opened in the arduino IDE. Just download the relevant libraries and it should work right out of the box.

If you would like to use a different IDE (like PlatformIO in VSCode for instance) you will just need to add:
```
#include <Arduino.h>
```
at the top of the file.

## Materials
<div align="center">

| Part      | Quantity | Notes| 
| :-------------- | :---: | :------ |
| Arduino Uno | 1 | You can use any arduino with analog inputs |
| Photoresistors | 4 | Consider their resistance |
| Wires    | a lot | Create freely your wire nest |
| 1 Kohm resistor  | 4 | Resistors used in order to create a voltage divider with photoresistors | 
| LED  | 1 | I used 1 Led to visualize if the motors are on or off | 
| potentiometers | 4 | Used only in the real device in order to calibrate resistors and get the same values |
| Servo Motors   | 2 | One for vertical axis and one for horizontal axis |
| Switch  | 1 | I used a switch to manually power off the device |
| Breadboard  | 1 | Useful for easy and rapid wiring |
</div>

## Circuit:
Pdf and jpg schematics are available here: [Circuit](/Circuit)

![alt text](https://github.com/grebano/Arduino_solar_track/blob/main/Circuit/Solar_track_circuit.jpg?raw=true)
