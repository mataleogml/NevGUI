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
  while (!buttonAState) {
    buttonAState = digitalRead(buttonAPin) == LOW;
    buttonBState = digitalRead(buttonBPin) == LOW;

    if (buttonBState) {
      clickSwitch();
    }
  }

  buttonAState = false;

  // Stage 2 - Play Audio
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
  while (!doorSensorState) {
    doorSensorState = digitalRead(doorSensorPin) == LOW;
  }

  doorSensorState = false;
}

void clickSwitch() {
  myservo.write(15);
  delay(500);
  myservo.write(0);
}

void playAudio() {
  digitalWrite(buttonAPin, HIGH);
  digitalWrite(buttonBPin, HIGH);

  mp3.play(rand() % 3 + 1);
}
