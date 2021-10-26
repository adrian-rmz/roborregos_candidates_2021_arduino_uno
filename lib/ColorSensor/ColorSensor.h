#ifndef ColorSensor_h
#define ColorSensor_h

#include <Arduino.h>

class colorSensor {
  
  private:
    byte _s2;
    byte _s3;
    byte _out;

    byte _r_pin;
    byte _g_pin;
    byte _b_pin;

    int _r_color;
    int _g_color;
    int _b_color;

    unsigned int _pulse_width;

  public:
    // Constructors
    colorSensor(byte s2, byte s3, byte out, byte r_pin, byte g_pin, byte b_pin, unsigned int pulse_width);

    //Methods
    void detect_and_show();

};


#endif


