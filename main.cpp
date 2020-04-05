#include "Arduino.h"
#include "EYRC_MOTION.h"

#define Motor_La 22
#define Motor_Lb 23
#define Motor_Ra 25
#define Motor_Rb 24
#define Motor_PWM_L 46
#define Motor_PWM_R 45
#define PWM 128
#define LCD_RW 36

EYRC_MOTION::EYRC_MOTION()
{
     pinMode(Motor_La,OUTPUT);
 pinMode(Motor_Lb,OUTPUT);
 pinMode(Motor_Ra,OUTPUT);
 pinMode(Motor_Rb,OUTPUT);
 pinMode(Motor_PWM_L,OUTPUT);
 pinMode(Motor_PWM_R,OUTPUT);
}
void EYRC_MOTION::moveForward(int pwm)
{
    digitalWrite(Motor_La,LOW);
  digitalWrite(Motor_Lb,HIGH);
  analogWrite(Motor_PWM_L,pwm);

  digitalWrite(Motor_Ra,LOW);
  digitalWrite(Motor_Rb,HIGH);
  analogWrite(Motor_PWM_R,pwm);
}
void EYRC_MOTION::moveBackward(int pwm)
{
    digitalWrite(Motor_La,HIGH);
  digitalWrite(Motor_Lb,LOW);
  analogWrite(Motor_PWM_L,pwm);

  digitalWrite(Motor_Ra,HIGH);
  digitalWrite(Motor_Rb,LOW);
  analogWrite(Motor_PWM_R,pwm);
}
void EYRC_MOTION::left_slow(int pwm)
{
    digitalWrite(Motor_La,HIGH);
  digitalWrite(Motor_Lb,HIGH);
  analogWrite(Motor_PWM_L,pwm);

  digitalWrite(Motor_Ra,LOW);
  digitalWrite(Motor_Rb,HIGH);
  analogWrite(Motor_PWM_R,pwm);
}
void EYRC_MOTION::left_sharp(int pwm)
{
    digitalWrite(Motor_La,HIGH);
  digitalWrite(Motor_Lb,LOW);
  analogWrite(Motor_PWM_L,pwm);

  digitalWrite(Motor_Ra,LOW);
  digitalWrite(Motor_Rb,HIGH);
  analogWrite(Motor_PWM_R,pwm);
}
void EYRC_MOTION::right_slow(int pwm)
{
    digitalWrite(Motor_La,LOW);
  digitalWrite(Motor_Lb,HIGH);
  analogWrite(Motor_PWM_L,pwm);

  digitalWrite(Motor_Ra,HIGH);
  digitalWrite(Motor_Rb,HIGH);
  analogWrite(Motor_PWM_R,pwm);
}
void EYRC_MOTION::right_sharp(int pwm)
{
    digitalWrite(Motor_La,LOW);
  digitalWrite(Motor_Lb,HIGH);
  analogWrite(Motor_PWM_L,pwm);

  digitalWrite(Motor_Ra,HIGH);
  digitalWrite(Motor_Rb,LOW);
  analogWrite(Motor_PWM_R,pwm);
}
void EYRC_MOTION::brake()
{
    digitalWrite(Motor_La,HIGH);
  digitalWrite(Motor_Lb,HIGH);
  analogWrite(Motor_PWM_L,255);

  digitalWrite(Motor_Ra,HIGH);
  digitalWrite(Motor_Rb,HIGH);
  analogWrite(Motor_PWM_R,255);
}
