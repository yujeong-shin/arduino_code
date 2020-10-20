#include <SoftwareSerial.h>
#include <Wire.h>
#include <math.h>
#define ILED 7
#define Vout A0
int IN1Pin = 12;
int IN2Pin = 13;
int ENPin = 9;
SoftwareSerial BTSerial(2, 3); // SoftwareSerial(TX, RX)
extern volatile unsigned long timer0_millis;
unsigned long cnt=5000;

void setup(){
  BTSerial.begin(9600); 
  Serial.begin(9600); 
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  pinMode(ILED,OUTPUT);
  pinMode(Vout,INPUT);
}

void loop(){
  if ( BTSerial.available() )
  {
      char ch = BTSerial.read();
      if(ch == '1')
      {
        Serial.println(ch);
        digitalWrite(ENPin, HIGH);
        digitalWrite(IN1Pin, HIGH);
        digitalWrite(IN2Pin, LOW);
      }
      else if(ch == '2')
      {
        Serial.println(ch);
        digitalWrite(ENPin, HIGH);
        digitalWrite(IN1Pin, LOW);
        digitalWrite(IN2Pin, HIGH);   
      }
      else if(ch=='3')
      {
        Serial.println(ch);
        digitalWrite(ENPin, HIGH);
        digitalWrite(IN1Pin, LOW);
        digitalWrite(IN2Pin, LOW);
      }
  }

  digitalWrite(ILED,LOW);
  delayMicroseconds(280);
  int adcvalue=analogRead(Vout);
  delayMicroseconds(40);
  digitalWrite(ILED,HIGH);
  delayMicroseconds(9680);
  float dustDensity=((0.172*(adcvalue*(5/1024.0))-0.0999)-580)/10;
  dustDensity = abs(dustDensity);
  
  String str = "";
  int gonggi = analogRead(A1);
  gonggi = gonggi * 24.45 / 44;
  
  str += gonggi;
  str += ',';
  str += dustDensity;

if(millis() > cnt)
{
  Serial.println(str);
  BTSerial.println(str);
  timer0_millis=0;
}
   
}
