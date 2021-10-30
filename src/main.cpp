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

  int show_left_color = left_color.detect_and_show();

  float left_distance = left_ultrasonic.distance(); 
  float front_distance = front_ultrasonic.distance(); 
  float right_distance = right_ultrasonic.distance();

  if (show_left_color == (255, 255, 0)) { // Detect A zone (yellow color)

    
  //*********************** A ZONE ***********************//
  float left_distance = left_ultrasonic.distance(); 
  float front_distance = front_ultrasonic.distance(); 
  float right_distance = right_ultrasonic.distance();

  if (front_distance < 10) { // Front Wall
    
    if (left_distance < 10 && right_distance < 10) { // Front Wall & Left Wall & Right Wall
      turn_left();
      delay(30);
      turn_left();
      delay(30);
      backward(); // To align the robot with the wall
      delay(1000); 
      forward();
    } else if (right_distance < 10) { // Front Wall & Right Wall
      turn_left();
      delay(30);
      backward(); // To align the robot with the wall
      delay(1000);
      forward();
    } else if (left_distance < 10) { // Front Wall & Left Wall
      turn_right();
      delay(30);
      backward(); // To align the robot with the wall
      delay(1000);
      forward();
    } 

    //delay(3000) // Wait until the robot reaches the next square

  } else {
    forward();
  }
    
  } else if ((show_left_color == (0, 0,255)) && (front_distance > 50) && (left_distance < 10) && (right_distance < 10)) { // Detect B zone 

    //*********************** B ZONE ***********************//

  } else if (show_left_color == (153, 0, 255)) { // Detect C zone 

    //*********************** C ZONE ***********************//
    left_color.turn_off();
    right_color.turn_off();
    int detect_left_color = left_color.detect_color();
    int detect_right_color = right_color.detect_color();
    forward();
    byte left = 0;
    byte right = 0;
    
    if (detect_left_color == (255, 255, 0)) { // yellow
      left += 1;
    } else if (detect_left_color == (0, 255, 0)) { // green
      left += 2;
    } else if (detect_left_color == (0, 0, 0)) {  // black
      right = 0;
    } else if (detect_left_color == (255, 255, 255)) { // white
      left += 0;
    }

    if (detect_right_color == (255, 255, 0)) { // yellow
      right += 1;
    } else if (detect_right_color == (0, 255, 0)) { // green
      right += 2;
    } else if (detect_right_color == (0, 0, 0)) {  // black
      left = 0;
    } else if (detect_right_color == (255, 255, 255)) { // white
      right += 0;
    }

    byte sum = left + right;
    byte binary_sum = dec_to_bin(sum);


    // Front Wall
    float front_distance = front_ultrasonic.distance();
    if ((front_distance < 10) && (binary_sum % 2 == 0)) { // pair
      turn_left();
    } else if ((front_distance < 10) && (binary_sum % 2 != 0)) { // odd
      turn_right();
    } 
  
  } else if (show_left_color == (255, 0, 164)) { // Detect Ramp
  
  }   

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

void turn_right() {
  // Right
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turn_left() {
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

int dec_to_bin(int dec) {
  int bin[8];
  int lenght = sizeof(bin);

  for (int i = 0; i < 8; i++){
    bin[i] = dec % 2;  
    dec = dec / 2;
  }

  for (int i = 7; i >= 0; i--){
    if(bin[i] == 0) {
      red_led();
    } else if (bin[i] == 1) {
      green_led();
    }
  }

  blue_led();
  return bin[last_element(bin, lenght)];
}


// RGB Led Colors
void red_led() {
  // Show Led in Red
  analogWrite(r_pin, 255);
  analogWrite(g_pin, 0);
  analogWrite(b_pin, 0);
  delay(500);

  // Turn Off Led
  analogWrite(r_pin, 0);
  analogWrite(g_pin, 0);
  analogWrite(b_pin, 0);
  delay(500);
}

void green_led() {
  // Show Led in Green
  analogWrite(r_pin, 0);
  analogWrite(g_pin, 255);
  analogWrite(b_pin, 0);
  delay(500);

  // Turn Off Led
  analogWrite(r_pin, 0);
  analogWrite(g_pin, 0);
  analogWrite(b_pin, 0);
  delay(500);
}

void blue_led() {
  // Show Led in Blue
  analogWrite(r_pin, 0);
  analogWrite(g_pin, 0);
  analogWrite(b_pin, 255);
  delay(1000);

  // Turn Off Led
  analogWrite(r_pin, 0);
  analogWrite(g_pin, 0);
  analogWrite(b_pin, 0);
  delay(1000);
}


// Get Last Element
int last_element(int aray[],int lenght){
    int last=0;
    last = (lenght / sizeof(aray[0]) - 8 );
    return last;
}