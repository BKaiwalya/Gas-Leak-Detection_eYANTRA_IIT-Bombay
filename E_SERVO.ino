#include <Servo.h>
Servo e_servo1;
Servo e_servo2;
Servo e_servo3;

void setup() {
  
e_servo1.attach(11);//OC1A
e_servo2.attach(12);//OC1B
e_servo3.attach(13);//OC1C,OC0A  
}

void loop() 
{
//Servo 1  
for (pos = 0; pos <= 180; pos += 1)
   { 
    e_servo1.write(pos);              
    delay(15);                       
   }
  for (pos = 180; pos >= 0; pos -= 1) 
  { 
    e_servo1.write(pos);              
    delay(15);                       
  }

  //Servo 2  
for (pos = 0; pos <= 180; pos += 1)
   { 
    e_servo2.write(pos);              
    delay(15);                       
   }
  for (pos = 180; pos >= 0; pos -= 1) 
  { 
    e_servo2.write(pos);              
    delay(15);                       
  }

  //Servo 3  
for (pos = 0; pos <= 180; pos += 1)
   { 
    e_servo3.write(pos);              
    delay(15);                       
   }
  for (pos = 180; pos >= 0; pos -= 1) 
  { 
    e_servo3.write(pos);              
    delay(15);                       
  }
}
