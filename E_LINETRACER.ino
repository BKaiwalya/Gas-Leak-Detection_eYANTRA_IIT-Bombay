#include <LiquidCrystal.h>
LiquidCrystal lcd(37, 35, 33, 32, 31, 30);
int x,t;
int sen_right=0,sen_left=0,sen_mid=0;
//int enCount = 0;
#define thres 150

void setup() 
{
  //InitEncoder();
  pinMode(36, OUTPUT);
  digitalWrite(36, LOW);
  lcd.begin(16, 2);
  
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(45, OUTPUT);
  lcd.setCursor(0,0);
}

void loop() 
{ 
  int x=getADC();
    //print(x);
    switch (t)
    {
    case 1: t = 1;
        //forward();
        digitalWrite(24,HIGH);
        digitalWrite(25,LOW);
        digitalWrite(23,HIGH);
        digitalWrite(22,LOW);

        analogWrite(46,130);
        analogWrite(45,50);//velocity(130,50);
        break;
        
    case 2: t = 2;
        //forward();
        
        digitalWrite(24,HIGH);
        digitalWrite(25,LOW);
        digitalWrite(23,HIGH);
        digitalWrite(22,LOW);
        
        analogWrite(46,150);
        analogWrite(45,150);//velocity(150,150);
        break;
        
    case 4: t = 4;
        //forward();
        digitalWrite(24,HIGH);
        digitalWrite(25,LOW);
        digitalWrite(23,HIGH);
        digitalWrite(22,LOW);
        
        analogWrite(46,50);
        analogWrite(45,130);//velocity(50,130);
        
        break;
    
   /* case 3: t = 3;
        while (x==2)
        {
          x = getADC();
          //print(x);
        digitalWrite(24,HIGH);
        digitalWrite(25,LOW);
        digitalWrite(23,HIGH);
        digitalWrite(22,LOW);
        
        analogWrite(46,140);
        analogWrite(45,50);
          //forward();
          //velocity(140,50);
        }
        break;
    case 6: t = 6;
        while (x==2)
        {
          x = getADC();
          //print(x);
          
        digitalWrite(24,HIGH);
        digitalWrite(25,LOW);
        digitalWrite(23,HIGH);
        digitalWrite(22,LOW);
        
        analogWrite(46,5);
        analogWrite(45,140);
          //forward();
          //velocity(50,140);
        }
        break;*/
    }
    
}

void print(int x)
{
  lcd.setCursor(0,0);
  lcd.print(x);
  delay(10);
}

int getADC()
{
  int a = analogRead(A1);//right
  int b = analogRead(A2);//centre
  int c = analogRead(A3);//left
  if(a < thres)
  {
    sen_right = 1;
  }
  else
  {
    sen_right=0;
  }
  
  if(b < thres)
  {
    sen_mid = 1;
  }
  else
  {
    sen_mid=0;
  }
  
  if(c < thres)
  {
    sen_left = 1;
  }
  else
  {
    sen_left=0;
  }
  x = sen_left*4 + sen_mid*2 + sen_right;
   //if ((x==0) /*|| (x==1) || (x==2) || (x==3) || (x==4) || (x==5) || (x==6)*/)
    //{
     t = x;
   // }
    print(x);
  return x;
}

