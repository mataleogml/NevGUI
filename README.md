# Oh My Gato Inator

This Arduino project involves a button on the wall with a face on it that controls a servo motor, which in turn switches the light switch on and off. The code provided here demonstrates the functionality of the project.

## Hardware Components

To replicate this project, you will need the following hardware components:

- Arduino board (such as Arduino Uno)
- Servo motor
- Button A
- Button B
- Magnetic door sensor
- DFPlayer Mini MP3 module
- Speaker or audio output device
- Jumper wires
- Breadboard or circuit board
- Light switch

## Software Libraries

The following software libraries are required for this project:

- Servo.h
- SoftwareSerial.h
- DFRobotDFPlayerMini.h

Make sure to install these libraries in your Arduino IDE before uploading the code.

## Wiring Instructions

Before uploading the code to your Arduino board, connect the components as follows:

- Connect the servo motor's signal pin to digital pin 9 of the Arduino.
- Connect button A to digital pin 12 of the Arduino.
- Connect button B to digital pin 13 of the Arduino.
- Connect the magnetic door sensor to digital pin 8 of the Arduino.
- Connect the DFPlayer Mini MP3 module's TX pin to digital pin 10 of the Arduino.
- Connect the DFPlayer Mini MP3 module's RX pin to digital pin 11 of the Arduino.
- Connect the speaker or audio output device to the DFPlayer Mini MP3 module's audio output.

Ensure that all connections are secure and accurate to avoid any issues.

## Code Explanation

The provided Arduino code consists of the following major functions:

```cpp
#include <Servo.h>
#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"

#define buttonAPin 12
#define buttonBPin 13
#define doorSensorPin 8
#define servoPin 9

SoftwareSerial mySerial(10, 11);
DFRobotDFPlayerMini mp3;

Servo myservo;

bool buttonAState = false;
bool buttonBState = false;
bool doorSensorState = false;

unsigned long audioStartMillis;
bool audioPlaying = false;

void setup() {
  // Initialization code
}

void loop() {
  // Main logic code
}

void clickSwitch() {
  // Code to control servo motor
}

void playAudio() {
  // Code to play audio using DFPlayer Mini MP3 module
}
```

## Running the Project

To run this project:

1. Set up the hardware components according to the wiring instructions provided above.

2. Install the required software libraries (Servo.h, SoftwareSerial.h, DFRobotDFPlayerMini.h) in your Arduino IDE.

3. Copy and paste the provided code into your Arduino IDE.

4. Upload the code to your Arduino board.

5. Ensure that the power supply is connected and the light switch is in the off position.

6. Press Button A or Button B to start the project. Button A will trigger the audio playback, and Button B will activate the servo motor to control the light switch.

Feel free to modify the code and experiment with different functionalities to customize the project according to your preferences.
