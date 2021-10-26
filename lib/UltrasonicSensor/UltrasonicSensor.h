#ifndef UltrasonicSensor_h
#define UltrasonicSensor_h

#include <Arduino.h>


class ultrasonicSensor {
  
  private:
    byte _trig;
    byte _echo;
    float _duration;

  public:
    // Constructors
    float dist;
    ultrasonicSensor(byte trig, byte echo);

    // Methods
    float distance();    

};


#endif