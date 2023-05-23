#include <Servo.h>
#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"

#define buttonAPin 8
#define buttonBPin 7
#define doorSensorPin 13
#define servoPin 11

SoftwareSerial mySerial(9, 10);
DFRobotDFPlayerMini mp3;

Servo myservo;

bool buttonAState = false;
bool buttonBState = false;
bool doorSensorState = false;

unsigned long audioStartMillis;
bool audioPlaying = false;

void setup() {
  Serial.begin(9600);
  pinMode(buttonAPin, INPUT_PULLUP);
  pinMode(buttonBPin, INPUT_PULLUP);
  pinMode(doorSensorPin, INPUT_PULLUP);
  pinMode(servoPin, OUTPUT);

  myservo.attach(servoPin);
  myservo.write(0);

  mySerial.begin(9600);
  mp3.begin(mySerial);
  mp3.volume(30);
}

void loop() {
  // Stage 1 - Await Input
  Serial.println("Stage 1: Awaiting input from Button A or Button B");
  while (!buttonAState) {
    buttonAState = digitalRead(buttonAPin) == LOW;
    buttonBState = digitalRead(buttonBPin) == LOW;

    if (buttonBState) {
      Serial.println("Button B pressed, activating Click Switch Function");
      clickSwitch();
    }
  }

  Serial.println("Button A pressed, moving to Stage 2");
  buttonAState = false;

  // Stage 2 - Play Audio
  Serial.println("Stage 2: Playing audio");
  playAudio();
  audioPlaying = true;

  // Wait for 10 seconds or until audio has finished playing
  audioStartMillis = millis();
  while (audioPlaying && millis() - audioStartMillis < 10000) {
    audioPlaying = !mp3.available();
  }

  mp3.stop();
  audioPlaying = false;

  // Stage 3 - Enable Door Sensor and Activate Click Switch Function
  Serial.println("Stage 3: Enabling Magnetic Door Sensor");

  pinMode(doorSensorPin, INPUT_PULLUP);  // Enable door sensor

  while (true) {
    // Check if Magnetic Door Sensor is off
    if (digitalRead(doorSensorPin) == HIGH) {
      Serial.println("Magnetic Door Sensor off, activating Click Switch Function");
      clickSwitch();
      break;  // Exit the loop and move back to Stage 1
    }
  }
  doorSensorState = true;  // Reset to inverted default state
}

void clickSwitch() {
  Serial.println("Click Switch Function: Moving servo motor forward and back");
  myservo.write(25);
  delay(500);
  myservo.write(0);
  delay(500);
}

void playAudio() {
  Serial.println("Play Audio Function: Playing MP3 from DFPlayer Mini");

  static int currentMP3 = 1;  // Track the current MP3 file number

  mp3.play(currentMP3);
  currentMP3++;

  if (currentMP3 > 9) {
    currentMP3 = 1;  // Reset to 1 when reaching 9 to repeat the sequence
  }
}

