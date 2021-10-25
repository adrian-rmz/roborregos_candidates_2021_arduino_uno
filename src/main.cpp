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


// TCS3200 Color Sensor
int s2 = 2;
int s3 = 3;
int out_pin = 4;

// Color Variables
int r_color;
int g_color;
int b_color;

// RGB LED
int red_pin = 14;
int green_pin = 15;
int blue_pin = 16;



// PULSE WIDTH
unsigned int pulse_width;


void setup() {
  // L298N pinModes
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // TCS3200 pinModes
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out_pin, INPUT);

  // RGB LED pinModes
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);

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


//***********************COLOR SENSOR***********************//

void color_sensor() {
  // RED
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  pulse_width = pulseIn(out_pin, LOW);
  r_color = pulse_width / 400. - 1;
  r_color = (255 - r_color);

  // GREEN
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  pulse_width = pulseIn(out_pin, LOW);
  g_color = pulse_width / 400. - 1;
  g_color = (255 - g_color);

  // BLUE
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  pulse_width = pulseIn(out_pin, LOW);
  b_color = pulse_width / 400. - 1;
  b_color = (255 - b_color);

  // TEST
  Serial.print(r_color);
  Serial.print(" , ");
  Serial.print(g_color);  
  Serial.print(" , ");  
  Serial.print(b_color);
  Serial.println("");

    
  // RGB LED
  if(r_color > g_color && g_color > b_color){
    r_color = 255;
    g_color = g_color / 2;
    b_color = 0;
  } else if (r_color > b_color && b_color > g_color){
    r_color = 255;
    g_color = 0;
    b_color = b_color / 2;
  } else if (g_color > r_color && r_color > b_color){
    r_color = r_color / 2;
    g_color = 255;
    b_color = 0;
  } else if (g_color > b_color && b_color > r_color){
    r_color = 0;
    g_color = 255;
    b_color = b_color / 2;
  } else if (b_color > r_color && r_color > g_color){
    r_color = r_color / 2;
    g_color = 0;
    b_color = 255;
  } else if (b_color > g_color && g_color > r_color){
    r_color = 0;
    g_color = g_color / 2;
    b_color = 255;
  }
  
  // Parametrize colors
  r_color = r_color * 1.0;
  b_color = b_color * 0.5;
  g_color = g_color * 0.75;

  // RETURN
  Serial.print(r_color);
  Serial.print(" , ");
  Serial.print(g_color);  
  Serial.print(" , ");  
  Serial.print(b_color);
  Serial.println("");
  analogWrite(red_pin, r_color);
  analogWrite(green_pin, g_color);
  analogWrite(blue_pin, b_color);
  delay(250);
}