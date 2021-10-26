#include <Arduino.h>

// IMPORT CLASSES

#include "../lib/UltrasonicSensor/UltrasonicSensor.h"
#include "../lib/ColorSensor/ColorSensor.h"


// DEFINE PINS

// Right Motor
#define IN1 6
#define IN2 7

// Left Motor
#define IN3 8
#define IN4 9

// Ultrasonic
#define trign 3
#define left_echo A0
#define front_echo A1
#define right_echo A2

// Color Sensors
#define s2n 4
#define s3n 5
#define left_out A3
#define right_out A4

// LED RGB 
#define r_pin 11
#define g_pin 12
#define b_pin 13

// Servomotor
#define servoM 10


// VARIABLES

// Color 
int r_color;
int g_color;
int b_color;

// Pulse Width
unsigned int pulse_width;


// OBJECTS

// Ultrasonic Sensor
ultrasonicSensor left_ultrasonic(trign, left_echo);
ultrasonicSensor front_ultrasonic(trign, front_echo);
ultrasonicSensor right_ultrasonic(trign, right_echo);

// Color Sensor
colorSensor left_color(s2n, s3n, left_out, r_pin, g_pin, b_pin, pulse_width);
colorSensor right_color(s2n, s3n, right_out, r_pin, g_pin, b_pin, pulse_width);


// CODE

void setup() {
  // L298N pinModes
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Serial Communication
  Serial.begin(9600);
}


void loop() {
  
  //*********************** A ZONE ***********************//


  //*********************** B ZONE ***********************//


  //*********************** C ZONE ***********************//
  forward();
  byte left = 0;
  byte right = 0;
  byte sum = left + right;

 
}


//****************************MOVEMENT****************************//

void forward() {
// Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  // Backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void right() {
  // Right
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void left() {
  // Left
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stop() {
  // Stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


//**************************** DECIMAL TO BINARY ****************************//
// return decimal to binary
int dec_to_bin(int dec) {
  int bin[8];
  int i = 0;
  while (dec > 0) {
    bin[i] = dec % 2;
    dec = dec / 2;
    i++;
  }
  for (int j = i - 1; j >= 0; j--) {
    Serial.print(bin[j]);
  }
  return bin[8];
}