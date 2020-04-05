#ifndef EYRC_MOTION_H_INCLUDED
#define EYRC_MOTION_H_INCLUDED

#include "Arduino.h"
class EYRC_MOTION
{
    public:
EYRC_MOTION();
void moveForward(int PWM);
void moveBackward(int PWM);
void left_slow(int PWM);
void left_sharp(int PWM);
void right_slow(int PWM);
void right_sharp(int PWM);
void brake();
};

#endif // EYRC_MOTION_H_INCLUDED
