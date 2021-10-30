#include "ColorSensor.h"

#include <Arduino.h>

colorSensor::colorSensor(byte s2, byte s3, byte out, byte r_pin, byte g_pin, byte b_pin, unsigned int pulse_width) {
  
  _s2 = s2;
  _s3 = s3;
  _out = out;

  _r_pin = r_pin;
  _g_pin = g_pin;
  _b_pin = b_pin;

  _pulse_width = pulse_width;

  // Color Sensor pinModes
  pinMode(_s2, OUTPUT);
  pinMode(_s3, OUTPUT);
  pinMode(_out, INPUT);

  // RGB LED pinModes
  pinMode(_r_pin, OUTPUT);
  pinMode(_g_pin, OUTPUT);
  pinMode(_b_pin, OUTPUT);
}


int colorSensor::detect_and_show() {
  
  // RED
  digitalWrite(_s2, LOW);
  digitalWrite(_s3, LOW);
  _pulse_width = pulseIn(_out, LOW);
  _r_color = _pulse_width / 400. - 1;
  _r_color = (255 - _r_color);

  // GREEN
  digitalWrite(_s2, HIGH);
  digitalWrite(_s3, HIGH);
  _pulse_width = pulseIn(_out, LOW);
  _g_color = _pulse_width / 400. - 1;
  _g_color = (255 - _g_color);

  // BLUE
  digitalWrite(_s2, LOW);
  digitalWrite(_s3, HIGH);
  _pulse_width = pulseIn(_out, LOW);
  _b_color = _pulse_width / 400. - 1;
  _b_color = (255 - _b_color);


  // RGB LED
  if(_r_color > _g_color && _g_color > _b_color){
    _r_color = 255;
    _g_color = _g_color / 2;
    _b_color = 0;
  } else if (_r_color > _b_color && _b_color > _g_color){
    _r_color = 255;
    _g_color = 0;
    _b_color = _b_color / 2;
  } else if (_g_color > _r_color && _r_color > _b_color){
    _r_color = _r_color / 2;
    _g_color = 255;
    _b_color = 0;
  } else if (_g_color > _b_color && _b_color > _r_color){
    _r_color = 0;
    _g_color = 255;
    _b_color = _b_color / 2;
  } else if (_b_color > _r_color && _r_color > _g_color){
    _r_color = _r_color / 2;
    _g_color = 0;
    _b_color = 255;
  } else if (_b_color > _g_color && _g_color > _r_color){
    _r_color = 0;
    _g_color = _g_color / 2;
    _b_color = 255;
  }
  
  // Parametrize colors
  _r_color = _r_color * 1.0;
  _b_color = _b_color * 0.5;
  _g_color = _g_color * 0.75;

  // RETURN
  analogWrite(_r_pin, _r_color);
  analogWrite(_g_pin, _g_color);
  analogWrite(_b_pin, _b_color);
  return (_r_color, _g_color, _b_color);
  delay(250);

}

int colorSensor::detect_color() {
  
  // RED
  digitalWrite(_s2, LOW);
  digitalWrite(_s3, LOW);
  _pulse_width = pulseIn(_out, LOW);
  _r_color = _pulse_width / 400. - 1;
  _r_color = (255 - _r_color);

  // GREEN
  digitalWrite(_s2, HIGH);
  digitalWrite(_s3, HIGH);
  _pulse_width = pulseIn(_out, LOW);
  _g_color = _pulse_width / 400. - 1;
  _g_color = (255 - _g_color);

  // BLUE
  digitalWrite(_s2, LOW);
  digitalWrite(_s3, HIGH);
  _pulse_width = pulseIn(_out, LOW);
  _b_color = _pulse_width / 400. - 1;
  _b_color = (255 - _b_color);


  // RGB LED
  if(_r_color > _g_color && _g_color > _b_color){
    _r_color = 255;
    _g_color = _g_color / 2;
    _b_color = 0;
  } else if (_r_color > _b_color && _b_color > _g_color){
    _r_color = 255;
    _g_color = 0;
    _b_color = _b_color / 2;
  } else if (_g_color > _r_color && _r_color > _b_color){
    _r_color = _r_color / 2;
    _g_color = 255;
    _b_color = 0;
  } else if (_g_color > _b_color && _b_color > _r_color){
    _r_color = 0;
    _g_color = 255;
    _b_color = _b_color / 2;
  } else if (_b_color > _r_color && _r_color > _g_color){
    _r_color = _r_color / 2;
    _g_color = 0;
    _b_color = 255;
  } else if (_b_color > _g_color && _g_color > _r_color){
    _r_color = 0;
    _g_color = _g_color / 2;
    _b_color = 255;
  }
  
  // Parametrize colors
  _r_color = _r_color * 1.0;
  _b_color = _b_color * 0.5;
  _g_color = _g_color * 0.75;

  // RETURN
  return (_r_color, _g_color, _b_color);
  delay(250);

}


void colorSensor::turn_off() {
  
  // RETURN
  analogWrite(_r_pin, 0);
  analogWrite(_g_pin, 0);
  analogWrite(_b_pin, 0);

}