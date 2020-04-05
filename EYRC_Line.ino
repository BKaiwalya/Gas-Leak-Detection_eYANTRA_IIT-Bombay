#include <EYRC_MOTION.h>
#include<LiquidCrystal.h>
#define LCD_RW 36
#define LEFT A3
#define MIDDLE A2
#define RIGHT A1
LiquidCrystal lcd(37,35,33,32,31,30);
EYRC_MOTION mov;
int left=0,right=0,middle=0;
int lf,mf,rf;

void setup() 
{
  LCD_Init();
  pinMode(LEFT,INPUT);
  pinMode(MIDDLE,INPUT);
  pinMode(RIGHT,INPUT);
  
}
void loop() 
{
  left = analogRead(LEFT);
  middle = analogRead(MIDDLE);
  right = analogRead(RIGHT);
  
 lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(left);

  lcd.setCursor(5,0);
  lcd.print(middle);
  
  lcd.setCursor(11,0);
  lcd.print(right); 
  //delay(50); 

  if(left>35)
    lf=1;
    else
    lf=0;
  if(middle>35)
    mf=1;
    else
    mf=0;
  if(right>35)
    rf=1;
    else
    rf=0;

    if(lf==1 && mf==0 && rf==0)
    {
    mov.left_sharp(170);
    delay(50);
    }
    else if(lf==0 && mf==0 && rf==1)
    {
    mov.right_sharp(190);
    delay(50);
    }
    else if(lf==0 && mf==1 && rf==0)
    mov.moveForward(170);
    else if(lf==0 && mf==1 && rf==1)
    {
      mov.brake();
      //mov.left_sharp(80);
      //mov.moveForward(110);
    }
    else if(lf==1 && mf==1 && rf==0)
    {
      //mov.brake();
      //delay(500);
      mov.left_sharp(170);
      delay(50);
      //mov.right_sharp(80);
      //mov.moveForward(110);
    }
    else if(lf==1 && mf==1 && rf==1)
    {
      mov.brake();
          }
    else if(lf==0 && mf==0 && rf==0)
    
    //mov.moveForward(150);
    
    mov.left_sharp(200);
    delay(50);
    
}
void LCD_Init()
{ 
 pinMode(LCD_RW,OUTPUT);
 digitalWrite(LCD_RW,LOW);
 lcd.begin(16,2);
}
