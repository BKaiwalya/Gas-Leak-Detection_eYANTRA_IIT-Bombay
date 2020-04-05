void setup() {
  // put your setup code here, to run once:
pinMode(43,OUTPUT);//On board 45  // Common terminal anode
pinMode(42,OUTPUT);//On board 46  //red 
pinMode(41,OUTPUT);//On board 43  //green
pinMode(40,OUTPUT);//On board 44  //blue
pinMode(34,OUTPUT);//buzzer
digitalWrite(43,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(42,LOW);
delay(100);
buzzer(1000);
digitalWrite(41,LOW);
delay(100);
buzzer(1000);
digitalWrite(40,LOW);
delay(100);
buzzer(1000);

}
void buzzer(int x )
{
  digitalWrite(34,HIGH);
  delay(x);
}

