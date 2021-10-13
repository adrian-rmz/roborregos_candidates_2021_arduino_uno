#include <Arduino.h>

// L298N
// Right Motor
int IN1 = 8;
int IN2 = 7;
int ENA = 9;

// Left Motor
int IN3 = 13;
int IN4 = 12;
int ENB = 11;

// Front Ultrasonic
int trigger_front = A0;
int echo_front = A1;

// Right Ultrasonic
int trigger_right = A2;
int echo_right = A3;

// Left Ultrasonic
int trigger_left = A4;
int echo_left = A5;

// Speeds 
int min_speed = 85;
int mid_speed = 170;
int max_speed = 255;


void setup() {
  // L298N pinModes
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Serial Communication
  Serial.begin(9600);
}


void loop() {
  
  
 
}


//****************************MOVEMENT****************************//

void forward(int speed) {
// Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void backward(int speed) {
  // Backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}

void right(int speed) {
  // Right
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void left(int speed) {
  // Left
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}

void stop() {
  // Stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}


//****************************DISTANCE****************************//

float distance_front() {
  digitalWrite(trigger_front, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_front, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_front, LOW);
  float duration_front = pulseIn(echo_front, HIGH);
  float distance_front = duration_front * 0.34 / 2;
  return distance_front;
}

float distance_right() {
  digitalWrite(trigger_right, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_right, LOW);
  float duration_right = pulseIn(echo_right, HIGH);
  float distance_right = duration_right * 0.34 / 2;
  return distance_right;
}

float distance_left() {
  digitalWrite(trigger_left, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_left, LOW);
  float duration_left = pulseIn(echo_left, HIGH);
  float distance_left = duration_left * 0.34 / 2;
  return distance_left;
}