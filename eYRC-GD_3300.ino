/*
 * Team Id:     eYRC-GD#3300
 * Author List: Atharv Sathe, Kaiwalya Belsare, Sarang Badgujar, Abhishek Wagh
 * Filename:    eyantra_win_25000_sure.ino
 * Theme:       Gas Leakage Detection
 * Functions:   void doEncoder_L()
 *              void doEncoder_R()
 *              void pins()
 *              int sense_line()
 *              void follow_line(int p)
 *              void angle_rotate(unsigned int Degrees)
 *              void linear_distance_mm(unsigned int DistanceInMM)
 *              void servo_init()
 *              void servo_1(unsigned char deg)
 *              void servo_2(unsigned char deg)
 *              void servo_3(unsigned char deg)
 *              int get_color()
 *              void go_forward_till(int x)
 *              void go_backward_till(int x)
 *              void go_back_till_line()
 *              void follow_line_till_junction()
 *              void turn_right_till_line()
 *              void turn_left_till_line()
 *              void omit_junction()
 *              void valve_color()
 *              void setup()
 *              void loop()
 * Variables:   bool drop=true, buzz=false;
                int i, j, z;
                int Count_L=0, Count_R=0, thres=35, color, line, angle=0;
                int sar=0;
                int leak[4], valve[4];
 */

#include <EYRC_MOTION.h>
#include <LiquidCrystal.h>

EYRC_MOTION myBot;
LiquidCrystal lcd(37, 35, 33, 32, 31, 30);

#define Encoder_L 2
#define Encoder_R 3

#define right_sensor A1
#define centre_sensor A2
#define left_sensor A3

#define s0 41
#define s1 38
#define s2 48
#define s3 49
#define out 47
#define enable 40

#define red 8//ph5
#define green 42//pl7
#define blue 43//pl6

#define buzzer 34

bool drop=true, buzz=false, pipe = true;
int i, j, z, c=0;
int Count_L=0, Count_R=0, thres=35, color, line, angle=0;
int sar=0;
int leak[4], valve[4];

/*
 * Function Name:   doEncoder_L
 * Input:           none
 * Output:          none
 * Logic:           increments a variable for left encoder
 * Example call:    attachInterrupt(0,doEncoder_L,FALLING);
 */
void doEncoder_L()
{
 Count_L ++;
}

/*
 * Function Name:   doEncoder_R
 * Input:           none
 * Output:          none
 * Logic:           increments a variable for right encoder
 * Example call:    attachInterrupt(0,doEncoder_R,FALLING);
 */
void doEncoder_R()
{
  Count_R++;
}

/*
 * Function Name:   pins
 * Input:           none
 * Output:          none
 * Logic:           sets pins as input or output 
 * Example call:    void pins();
 */
void pins()
{
  pinMode(Encoder_L,INPUT);
  pinMode(Encoder_R,INPUT);
  pinMode(right_sensor, INPUT);
  pinMode(centre_sensor, INPUT);
  pinMode(left_sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  digitalWrite(Encoder_L, HIGH);
  digitalWrite(Encoder_R, HIGH);
  digitalWrite(36, LOW);
  digitalWrite(43, HIGH);
  digitalWrite(red, HIGH);
  digitalWrite(blue, HIGH);
  digitalWrite(green, HIGH);
}

/*
 * Function Name:   sense_line
 * Input:           none
 * Output:          integer from 0 - 7
 * Logic:           detects which sensors are on white line.
 *                  returns binary weighted value for 3 sensors.
 * Example call:    int line = sense_line();
 */
int sense_line()
{
  int x, sen_right, sen_mid, sen_left;
  int a = analogRead(right_sensor);//right
  int b = analogRead(centre_sensor);//centre
  int c = analogRead(left_sensor);//left
  
  if(a > thres)
  {sen_right = 1;}
  else
  { sen_right=0;}
  
  if(b > thres)
  {sen_mid = 1;}
  else
  {sen_mid=0;}
  
  if(c > thres)
  {sen_left = 1;}
  else
  {sen_left=0;}
  
  x = sen_left*4 + sen_mid*2 + sen_right;
  return(x);
}

/*
 * Function Name:   follow_line
 * Input:           integer from 0 - 7
 * Output:          none
 * Logic:           drives motors from the input value.
 * Example call:    follow_line(3);
 */
void follow_line(int p)
{
  switch(p)
  {
    case 1:
    {
      myBot.right_sharp(200);
      delay(50);
      break;
    }
    case 2:
    {
      myBot.moveForward(250);
      delay(50);
      break;
    }
    case 3:
    {
      break;
    }
    case 4:
    {
      myBot.left_sharp(200);
      delay(50);
      break;
    }
    case 6:
    {
      break;
    }
    case 7:
    {
      break;  
    }
    default:
    myBot.moveForward(200);
    delay(50);
   }
}

/*
 * Function Name:   angle_rotate
 * Input:           degrees in integer
 * Output:          none
 * Logic:           robot rotates till input degrees taking feedback from encoders.
 * Example call:    angle_rotate(90);
 */
void angle_rotate(unsigned int Degrees)
{
  float ReqdShaftCount = 0;
  unsigned long int ReqdShaftCountInt = 0;

  ReqdShaftCount = (float) Degrees/ 4.27; // division by resolution to get shaft count
  ReqdShaftCountInt = (unsigned int) ReqdShaftCount;
  Count_L = 0;
  Count_R = 0;

  while (true)
  {
    delay(1);
    if((Count_L >= ReqdShaftCountInt) | (Count_R >= ReqdShaftCountInt))
    {break;}
  }
  myBot.brake(); //Stop robot
}

/*
 * Function Name:   linear_distance_mm
 * Input:           distance in mm in integer
 * Output:          none
 * Logic:           robot travels the specified disatnce taking feedback from encoders.
 * Example call:    linear_disatnce_mm(100);
 */
void linear_distance_mm(unsigned int DistanceInMM)
{
  float ReqdShaftCount = 0;
  unsigned long int ReqdShaftCountInt = 0;

  ReqdShaftCount = DistanceInMM / 5.838; // division by resolution to get shaft count
  ReqdShaftCountInt = (unsigned long int) ReqdShaftCount;
  Count_L = 0;
  
  while(1)
  {
    delay(1);
    if(Count_L > ReqdShaftCountInt)
    {break;}
  }
  myBot.brake(); //Stop robot
}

void led_switch(int y)
{
  switch(y)
  {
    case 1:
    {
      digitalWrite(red, !digitalRead(red));
      break;
    }
    case 2:
    {
      digitalWrite(blue, !digitalRead(blue));
      break;
    }
    case 3:
    {
      digitalWrite(green, !digitalRead(green));
      break;
    }
  }
}

/*
 * Function Name:   servo_init
 * Input:           none
 * Output:          none
 * Logic:           sets timers for servos.
 * Example call:    cli();
 *                  servo_init();
 *                  sei();
 */
void servo_init()
{
  DDRB  = DDRB | 0x20;  //making PORTB 5 pin output
  PORTB = PORTB | 0x20; //setting PORTB 5 pin to logic 1

  DDRB  = DDRB | 0x40;  //making PORTB 6 pin output
  PORTB = PORTB | 0x40; //setting PORTB 6 pin to logic 1

  DDRB  = DDRB | 0x80;  //making PORTB 7 pin output
  PORTB = PORTB | 0x80; //setting PORTB 7 pin to logic 1 

  TCCR1B = 0x00; 
  TCNT1H = 0xFC; 
  TCNT1L = 0x01; 
  OCR1AH = 0x03; 
  OCR1AL = 0xFF; 
  OCR1BH = 0x03; 
  OCR1BL = 0xFF; 
  OCR1CH = 0x03; 
  OCR1CL = 0xFF; 
  ICR1H  = 0x03; 
  ICR1L  = 0xFF;
  TCCR1A = 0xAB; 
  TCCR1C = 0x00;
  TCCR1B = 0x0C; 
}


/*
 * Function Name:   servo_1
 * Input:           degrees to be rotated in integer
 * Output:          none
 * Logic:           converts it to milliseconds and gives it to specific timer.
 * Example call:    servo_1(90);
 */
void servo_1(unsigned char deg)  //PORT B5
{
 float PositionPanServo = 0;
 PositionPanServo = ((float)deg / 1.86) + 35.0;
 OCR1AH = 0x00;
 OCR1AL = (unsigned char) PositionPanServo;
}

/*
 * Function Name:   servo_2
 * Input:           degrees to be rotated in integer
 * Output:          none
 * Logic:           converts it to milliseconds and gives it to specific timer.
 * Example call:    servo_2(90);
 */
void servo_2(unsigned char deg)  //PORT B6
{
 float PositionTiltServo = 0;
 PositionTiltServo = ((float)deg / 1.86) + 35.0;
 OCR1BH = 0x00;
 OCR1BL = (unsigned char) PositionTiltServo;
}

/*
 * Function Name:   servo_2
 * Input:           degrees to be rotated in integer
 * Output:          none
 * Logic:           converts it to milliseconds and gives it to specific timer.
 * Example call:    servo_2(90);
 */
void servo_3(unsigned char deg) //PORT B7
{
 float PositionServo = 0;
 PositionServo = ((float)deg / 1.86) + 35.0;
 OCR1CH = 0x00;
 OCR1CL = (unsigned char) PositionServo;
}

/*
 * Function Name:   get_color
 * Input:           none
 * Output:          innteger from 0 - 3
 * Logic:           takes readings from color sensor for 8 times. 
 *                  returns integer specified for each color.
 * Example call:    int color = get_color();
 */
int get_color()
{
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(enable,OUTPUT);
  pinMode(out,INPUT);

  digitalWrite(s0,HIGH);
  digitalWrite(s1,HIGH);
  digitalWrite(enable,LOW);

  int u = 0, cgreen=0, cred=0, cblue=0, cblack=0, x=70,blue1,green1,red1;
  for(u = 0; u < 8; u++)
  {
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    red1 = pulseIn(out, digitalRead(out));
  
    digitalWrite(s3, HIGH);
    blue1 = pulseIn(out, digitalRead(out));
  
  
    digitalWrite(s2, HIGH);
    green1 = pulseIn(out, digitalRead(out));

    if(blue1 > x, green1 > x, red1 > x)
    cblack++;
    else if(red1 < green1 && red1 < blue1)
    cred++;
    else if(blue1 < red1 && blue1 < green1)
    cblue++;
    else if(green1 < red1 && green1 < blue1)
    cgreen++;
  }
  if(cblack > cblue && cblack > cgreen)
  {return(0);
  //lcd.print("black");
  }
  else if(cred > cblack && cred > cblue && cred > cgreen)
  {return(1);
  //lcd.print("red");
  }
  else if(cblue >  cgreen && cblue > cblack && cblue > cred)
  {return(2);
  //lcd.print("blue");
  }
  else if(cgreen > cblue && cgreen > cblack && cgreen > cred)
  {return(3);
  //lcd.print("green");
  }
}

/*
 * Function Name:   go_forward_till
 * Input:           distance in mm as an integer
 * Output:          none
 * Logic:           robot moves forward with specified pwm calling linear_distance_mm.
 * Example call:    go_forward_till(50);
 */
void go_forward_till(int x)
{
  myBot.moveForward(250);
  linear_distance_mm(x);
}

/*
 * Function Name:   go_backward_till
 * Input:           distance in mm as an integer
 * Output:          none
 * Logic:           robot moves backward with specified pwm calling linear_distance_mm.
 * Example call:    go_backward_till(50);
 */
void go_backward_till(int x)
{
  myBot.moveBackward(250);
  linear_distance_mm(x);
}

/*
 * Function Name:   go_back_till_line
 * Input:           none
 * Output:          none
 * Logic:           robot moves backward till it detects a line and then stops.
 * Example call:    go_back_till_line();
 */
void go_back_till_line()
{
  line = sense_line();
  while(line != 7 && line !=6 && line != 3)
  {
    line = sense_line();
    myBot.moveBackward(250);
  }
  myBot.brake();
}

/*
 * Function Name:   follow_line_till_junction
 * Input:           none
 * Output:          none
 * Logic:           robot follows line till atleast two of the sensors are on the line.
 * Example call:    follow_line_till_junction();
 */
void follow_line_till_junction()
{
  line = sense_line();
  while(line != 7 && line !=6 && line != 3)
  {
    line = sense_line();
    follow_line(line);
  }
  myBot.brake();
}

/*
 * Function Name:   turn_right_till_line
 * Input:           none
 * Output:          none
 * Logic:           robot turns right till central sensor is on black line and then stops.
 * Example call:    turn_right_till_line();
 */
void turn_right_till_line()
{
  go_forward_till(95);
  myBot.right_sharp(250);
  angle_rotate(98);
}

/*
 * Function Name:   turn_left_till_line
 * Input:           none
 * Output:          none
 * Logic:           robot turns left till central sensor is on black line and then stops.
 * Example call:    turn_left_till_line();
 */
void turn_left_till_line()
{
  go_forward_till(95);
  myBot.left_sharp(250);
  angle_rotate(98);
}

/*
 * Function Name:   omit_junction
 * Input:           none
 * Output:          none
 * Logic:           robot omits the first junction it detects.
 * Example call:    omit_junction();
 */
void omit_junction()
{
  follow_line_till_junction();
  go_forward_till(70);
  follow_line_till_junction();
}

/*
 * Function Name:   valve_color
 * Input:           none
 * Output:          none
 * Logic:           locomotes to control valve from control valve junction.
 *                  detects color.
 *                  displays the respective coloron lcd.
 * Example call:    valve_color();
 */
void valve_color()
{
  go_forward_till(55);
  myBot.left_sharp(250);
  angle_rotate(50);
  go_forward_till(7);

  valve[i] = get_color();
  go_backward_till(7);
}

/*
 * Function Name:   go_back
 * Input:           none
 * Output:          none
 * Logic:           traverses to previous valve if the leakage matches with the just previous valve.
 * Example call:    go_back();
 */
void go_back()
{
  go_forward_till(95);
  myBot.left_sharp(250);
  angle_rotate(93);
  go_forward_till(100);

  follow_line_till_junction();

  go_forward_till(95);
  myBot.right_sharp(250);
  angle_rotate(95);
   
  follow_line_till_junction();

  go_forward_till(95);
  myBot.left_sharp(250);
  angle_rotate(135);
  go_backward_till(55);

  for (z = 0; z < 65; z++)
  {
  angle = angle+1;
  servo_1(angle);
  delay(1);
  }
  delay(1000);
   
  //led_switch(leak[i]);
  leak[i] = 0;
  
  go_forward_till(55);
  myBot.left_sharp(250);
  angle_rotate(60);
  follow_line_till_junction();
  go_forward_till(105);
  myBot.left_sharp(250);
  angle_rotate(100); 

  follow_line_till_junction();
  go_forward_till(50);
}

/*
 * Function Name:   setup
 * Input:           none
 * Output:          none
 * Logic:           code that needs to be run only once.
 * Example call:    void setup();
 */
void setup()
{
  pins();
  cli();
  servo_init();
  sei();

  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);

  servo_1(angle);

  attachInterrupt(0,doEncoder_L,FALLING);
  attachInterrupt(1,doEncoder_R,FALLING);
}

/*
 * Function Name:   loop
 * Input:           none
 * Output:          none
 * Logic:           code that needs to be executed repeatedly.
 * Example call:    void loop();
 */
void loop()
{
  go_forward_till(180);//It reaches till the pipeline junction.
  delay(100);

  for(i = 0; i < 4; i++)
  {
    if(pipe)
    {
      go_forward_till(700);//It reaches inside the pipeline.
      lcd.clear();
      lcd.setCursor(0, 0);
      leak[i] = get_color();
      led_switch(leak[i]);//Detects leak color.
      lcd.print(leak[i]);
  
      if(leak[i] != 0)//Buzzer rings if color isnt black.
      {
        digitalWrite(buzzer, HIGH);
        delay(1000);
        digitalWrite(buzzer, LOW);
        c++;//Increments variable to count number of leakages.
      }
  
      go_back_till_line();//Goes back till it encounters pipeline junction.
      if(leak[i] == valve[i-1] && leak[i] !=0)
      {
        go_back();//Traverses to previous control valve to drop the magnet.
      }

      turn_right_till_line();
      follow_line_till_junction();
    }
    turn_left_till_line();
    follow_line_till_junction();//Reaches control valve junction.

    valve_color();
    led_switch(valve[i]);//Deteccts and prints valve color.
    lcd.setCursor(0, 1);
    lcd.print(valve[i]);
    for(j = 0; j <= i; j++)
    {
      if(valve[i] == leak[j] && valve[i] != 0)//matches valve color with previously detected leak color.
      {
        drop = false;
        valve[i] = 0;
        leak[j] = 0;
        myBot.left_sharp(250);
        angle_rotate(190);
        go_backward_till(95);
        for(z = 0; z < 65; z++)//Drops magnets in the control valve
        {
          angle = angle+1;
          servo_1(angle);
          delay(1);
        }
        delay(1000);
      }
    }
    if(drop)//Procedure of the bot if the colors dont match and no magnet is needed to be dropped.
    {
      myBot.right_sharp(250);
      angle_rotate(50);
      go_backward_till(55);
      turn_right_till_line();
    }
    else//Procedure of the bot to go to the valve junction after dropping the magnet.
    {
      go_forward_till(45);
      myBot.left_sharp(250);
      angle_rotate(50);
      drop = true;
    }
    
    follow_line_till_junction();
    turn_left_till_line();
    follow_line_till_junction();

    if(i == 3)//For last loop 
    {
      for(j = 0; j < 4; j++)
      {
        if(leak[j] == 0)
        {
          sar++;
        }
      }
      if(sar == 4)//Decides whether all leakages have been switched off.
      {buzz = true;}

      if(buzz)//If all leakages are switched off, bot returns to start/stop zone.
      {
        turn_right_till_line();
        follow_line_till_junction();
        go_forward_till(95);
        digitalWrite(buzzer, HIGH);//Buzzer rings indicating the end of the run.
        delay(6000);
        digitalWrite(buzzer, LOW);
        while(1);
      }
      goto second_round;//If all leakages are not switched off, it goes for second round around the arena.
    }

    if(i == 2 && c == 3)//All leakages are in the first three pipelines, bot doesnt traverse in fourth pipeline.
    {
      omit_junction();
      pipe = false;
      goto omit_turn;
    }
    
    go_forward_till(95);//Detects pipeline junction and turns towards the pipeline
    myBot.left_sharp(250);
    angle_rotate(98);
    omit_turn:;
  }
  second_round:
  myBot.brake();
  omit_junction();
  
  follow_line_till_junction();
  turn_left_till_line();
  follow_line_till_junction();
  myBot.right_sharp(250);
  angle_rotate(150);
  go_backward_till(95);
  for(z = 0; z < 65; z++)
   {
     angle = angle+1;
     servo_1(angle);
     delay(1);
   }
   delay(1000);
   myBot.right_sharp(250);
   angle_rotate(45);
   leak[0] = 0;

   if(leak[1] == 0 && leak[2] == 0)
   {
     valve1:
     follow_line_till_junction();
     turn_right_till_line();
     follow_line_till_junction();
     turn_left_till_line();
     go_forward_till(95);
     digitalWrite(buzzer, HIGH);
     delay(6000);
     digitalWrite(buzzer, LOW);
     while(1);
   }
   else
   {
    turn_left_till_line();
    follow_line_till_junction();
    turn_left_till_line();
    omit_junction();
    turn_left_till_line();
    follow_line_till_junction();
    if(leak[1] != 0)
    {
        myBot.right_sharp(250);
        angle_rotate(150);
        go_backward_till(95);
        for(z = 0; z < 65; z++)
         {
           angle = angle+1;
           servo_1(angle);
           delay(1);
         }
         delay(1000);
         myBot.right_sharp(250);
         angle_rotate(45);
         leak[1] = 0;

         if(leak[2] == 0)
         {
           valve2:
           turn_right_till_line();
           follow_line_till_junction();
           turn_left_till_line();
           goto valve1;
         }
         else
         {
           turn_left_till_line();
           follow_line_till_junction();
           turn_left_till_line();
           omit_junction();
           turn_left_till_line();
           follow_line_till_junction();
           
           myBot.right_sharp(250);
           angle_rotate(150);
           go_backward_till(95);
           for(z = 0; z < 65; z++)
            {
              angle = angle+1;
              servo_1(angle);
              delay(1);
            }
            delay(1000);
            myBot.right_sharp(250);
            angle_rotate(45);
            leak[2] = 0;

            follow_line_till_junction();
            turn_right_till_line();
            omit_junction();
            turn_right_till_line();
            follow_line_till_junction();
            turn_left_till_line();
            goto valve2;
           
         }
     } 

   }
  
}

