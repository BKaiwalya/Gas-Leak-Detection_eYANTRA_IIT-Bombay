#include <SharpIR.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(37, 35, 33, 32, 31, 30);

#define ir 11
#define model 1080
// ir: the pin where your sensor is attached
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y
//                                            (working distance range according to the datasheets)

SharpIR SharpIR(ir, model);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(36, OUTPUT);
  digitalWrite(36, LOW);
  lcd.begin(16, 2);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(11,OUTPUT);
  lcd.setCursor(0,0);

}

void loop() {
  delay(2000);   

  unsigned long pepe1=millis();  // takes the time before the loop on the library begins

  int dis=SharpIR.distance();  // this returns the distance to the object you're measuring


  Serial.print("Mean distance: ");  // returns it to the serial monitor
  Serial.println(dis);
  lcd.setCursor(0,0);
  lcd.print(dis);
  
  /*unsigned long pepe2=millis()-pepe1;  // the following gives you the time taken to get the measurement
  Serial.print("Time taken (ms): ");
  Serial.println(pepe2);*/  
if (dis < 26)
{
        digitalWrite(24,HIGH);
        digitalWrite(25,LOW);
        digitalWrite(23,HIGH);
        digitalWrite(22,LOW);
        
        analogWrite(46,0);
        analogWrite(45,0);//FireBird STOP 
}
else
{
        digitalWrite(24,HIGH);
        digitalWrite(25,LOW);
        digitalWrite(23,HIGH);
        digitalWrite(22,LOW);
        
        analogWrite(46,150);
        analogWrite(45,150);//FireBird FORWARD
  }
}
