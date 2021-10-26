#include "UltrasonicSensor.h"

#include <Arduino.h>


ultrasonicSensor::ultrasonicSensor(byte trig, byte echo) {
  
  _trig = trig;
  _echo = echo;

  // Ultrasonic pinModes
  pinMode(_trig, OUTPUT);
  pinMode(_echo, INPUT);

}


float ultrasonicSensor::distance() {

  digitalWrite(_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trig, LOW);

  _duration = pulseIn(_echo, HIGH);
  dist = _duration * 0.034 / 2;
  return dist;  

}

