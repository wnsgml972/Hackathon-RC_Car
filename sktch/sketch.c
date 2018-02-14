#include <SoftwareSerial.h>

#define BLU_TX_PORT 4
#define BLU_RX_PORT 12

#define R0 10000
#define T0 25 //room temperature
#define B 4200 //the coefficient of the thermistor
#define SERISR 10000 //seris resistor 10K


SoftwareSerial BTSerial(BLU_TX_PORT,BLU_RX_PORT);
String myString="";

int rightFront = 6; // RIGHT 6 앞 5 뒤 
int rightBack = 5;
int leftFront = 14; // LEFT 14 앞 15 뒤
int leftBack = 15;

int A = 9;
int C = 10;

void setup() {
  pinMode(rightFront, OUTPUT);
  pinMode(rightBack, OUTPUT);  
  pinMode(leftFront, OUTPUT);
  pinMode(leftBack, OUTPUT);
  //pinMode(A,OUTPUT);
  //pinMode(C,OUTPUT);
  
  
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  //digitalWrite(A,HIGH);
  //digitalWrite(C,HIGH);
  while(BTSerial.available())  //mySerial 값이 있으면
  {
    char myChar = (char)BTSerial.read();  //mySerial int형식의 값을 char형식으로 변환
    myString+=myChar;   //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);           //수신 문자열 끊김 방지
  }
  
  if(!myString.equals(""))  //myString 값이 있다면
  { 
      if(myString.equals("fo")) // 앞 
      {
        digitalWrite(rightFront, HIGH);
        digitalWrite(leftFront, HIGH);
        digitalWrite(rightBack, LOW);
        digitalWrite(leftBack, LOW);
      }else if(myString.equals("st")){
        digitalWrite(rightFront, LOW);
        digitalWrite(leftFront, LOW);
        digitalWrite(rightBack, LOW);
        digitalWrite(leftBack, LOW);
      }else if(myString.equals("ri")){
        digitalWrite(rightFront, LOW);
        digitalWrite(leftFront, HIGH);
        digitalWrite(rightBack, LOW);
        digitalWrite(leftBack, LOW);
      }else if(myString.equals("le")){
        digitalWrite(rightFront, HIGH);
        digitalWrite(leftFront, LOW);
        digitalWrite(rightBack, LOW);
        digitalWrite(leftBack, LOW);
      }else if(myString.equals("ba")){
        digitalWrite(rightFront, LOW);
        digitalWrite(leftFront, LOW);
        digitalWrite(rightBack, HIGH);
        digitalWrite(leftBack, HIGH);
      }else if(myString.equals("te")){
        float thermistorRValue;
        thermistorRValue = 1023.0 / analogRead(6) - 1;
        thermistorRValue = SERISR / thermistorRValue;
        
        float temperature;
        temperature = thermistorRValue / R0; // R/R0
        temperature = log(temperature);
        temperature = temperature / B;
        temperature = temperature + 1.0 / (T0 + 273.15); 
        temperature = 1.0 / temperature;  
        temperature -= 273.15 ;// kelvins to C
        Serial.println(temperature);
        BTSerial.println((int)temperature);
      }
      
    myString="";  //myString 변수값 초기화
  }  
}