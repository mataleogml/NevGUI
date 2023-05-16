#include <Servo.h>
#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"

#define buttonAPin 2
#define buttonBPin 3
#define doorSensorPin 4
#define servoPin 5

SoftwareSerial mySerial(10, 11);
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
  mp3.volume(20);
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

  // Stage 3 - Await Door Sensor
  Serial.println("Stage 3: Awaiting Magnetic Door Sensor");
  while (!doorSensorState) {
    doorSensorState = digitalRead(doorSensorPin) == LOW;
  }

  doorSensorState = false;
  Serial.println("Magnetic Door Sensor on, activating Click Switch Function");
  clickSwitch();
}

void clickSwitch() {
  Serial.println("Click Switch Function: Moving servo motor forward and back");
  myservo.write(90);
  delay(500);
  myservo.write(0);
    delay(500);

}

void playAudio() {
  Serial.println("Play Audio Function: Playing random MP3 from DFPlayer Mini");
  digitalWrite(buttonAPin, HIGH);
  digitalWrite(buttonBPin, HIGH);

  mp3.play(rand() % 3 + 1);
}
