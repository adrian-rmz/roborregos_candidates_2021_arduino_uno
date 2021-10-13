#include <Arduino.h>

// Right Motor
int right_motor_1 = 3;
int right_motor_2 = 4;

// Left Motor
int left_motor_1 = 5;
int left_motor_2 = 6;

// Front Ultrasonic
int trigger_front = A0;
int echo_front = A1;

// Right Ultrasonic
int trigger_right = A2;
int echo_right = A3;

// Left Ultrasonic
int trigger_left = A4;
int echo_left = A5;


void setup() {
  // pinModes
  pinMode(right_motor_1, OUTPUT);
  pinMode(right_motor_2, OUTPUT);

  pinMode(left_motor_1, OUTPUT);
  pinMode(left_motor_2, OUTPUT);

    // Serial Communication
  Serial.begin(9600);
}


void loop() {
  
  
 
}


//****************************MOVEMENT****************************//

void forward() {
// Forward
  digitalWrite(right_motor_1, HIGH);
  digitalWrite(right_motor_2, LOW);
  digitalWrite(left_motor_1, HIGH);
  digitalWrite(left_motor_2, LOW);
}

void backward() {
  // Backward
  digitalWrite(right_motor_1, LOW);
  digitalWrite(right_motor_2, HIGH);
  digitalWrite(left_motor_1, LOW);
  digitalWrite(left_motor_2, HIGH);
}

void right() {
  // Right
  digitalWrite(right_motor_1, LOW);
  digitalWrite(right_motor_2, HIGH);
  digitalWrite(left_motor_1, HIGH);
  digitalWrite(left_motor_2, LOW);
}

void left() {
  // Left
  digitalWrite(right_motor_1, HIGH);
  digitalWrite(right_motor_2, LOW);
  digitalWrite(left_motor_1, LOW);
  digitalWrite(left_motor_2, HIGH);
}

void stop() {
  // Stop
  digitalWrite(right_motor_1, LOW);
  digitalWrite(right_motor_2, LOW);
  digitalWrite(left_motor_1, LOW);
  digitalWrite(left_motor_2, LOW);
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