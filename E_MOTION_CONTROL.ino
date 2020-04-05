#include <LiquidCrystal.h>
LiquidCrystal lcd(37, 35, 33, 32, 31, 30);

void setup() {
  // put your setup code here, to run once:
  pinMode(36, OUTPUT);
  digitalWrite(36, LOW);
  lcd.begin(16, 2);
  pinMode(24, OUTPUT);//right motor  PA2
  pinMode(25, OUTPUT);//right motor  PA3
  pinMode(23, OUTPUT);//left motor   PA1
  pinMode(22, OUTPUT);//right motor  PA0
  pinMode(46, OUTPUT);//OC5A
  pinMode(45, OUTPUT);//OC5B
  lcd.print("Square");
}

void loop() {
  // put your main code here, to run repeatedly:
e_forward();
delay(2000);
e_left();
delay(1300);
e_forward();
delay(2000);
e_left();
delay(1300);
e_forward();
delay(2000);
e_left();
delay(1300);
/*e_left();
delay(1500);
e_backward();
delay(2000);
e_left();*/
e_forward();
delay(2000);
e_stop();
}
void e_forward()
{
        digitalWrite(24,HIGH);
        digitalWrite(25,LOW);
        digitalWrite(23,HIGH);
        digitalWrite(22,LOW);
        
        analogWrite(46,255);
        analogWrite(45,255);//velocity(150,150);
  }
  void e_stop()
{
        digitalWrite(24,HIGH);
        digitalWrite(25,LOW);
        digitalWrite(23,HIGH);
        digitalWrite(22,LOW);
        
        analogWrite(46,0);
        analogWrite(45,0);//velocity(150,150);
  }

  void e_backward()
{
        digitalWrite(24,LOW);
        digitalWrite(25,HIGH);
        digitalWrite(23,LOW);
        digitalWrite(22,HIGH);
        
        analogWrite(46,255);
        analogWrite(45,255);//velocity(150,150);
  }
 void e_right()
 {
        digitalWrite(24,HIGH);//right motor PA2
        digitalWrite(25,LOW);//right motor  PA3
        digitalWrite(23,LOW);//left motor   PA1
        digitalWrite(22,HIGH);//right motor PA0
        
        analogWrite(46,200);//left motor pwm
        analogWrite(45,0);//right motor pwm
        //delay(500);
  }
  void e_left()
 {
        digitalWrite(24,LOW);//right motor PA2
        digitalWrite(25,HIGH);//right motor  PA3
        digitalWrite(23,HIGH);//left motor   PA1
        digitalWrite(22,LOW);//right motor PA0
        
        analogWrite(46,0);//left motor pwm
        analogWrite(45,200);//right motor pwm
        //delay(500);
  }
