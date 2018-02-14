#include <SoftwareSerial.h>

#define BLU_TX_PORT 4
#define BLU_RX_PORT 12

#define R0 10000
#define T0 25 //room temperature
#define B 4200 //the coefficient of the thermistor
#define SERISR 10000 //seris resistor 10K


SoftwareSerial BTSerial(BLU_TX_PORT,BLU_RX_PORT);
String myString="";

int rightFront = 6; // RIGHT 6 �� 5 �� 
int rightBack = 5;
int leftFront = 14; // LEFT 14 �� 15 ��
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
  while(BTSerial.available())  //mySerial ���� ������
  {
    char myChar = (char)BTSerial.read();  //mySerial int������ ���� char�������� ��ȯ
    myString+=myChar;   //���ŵǴ� ���ڿ��� myString�� ��� ���� (1����Ʈ�� ���۵Ǵ� ���� ��� ����)
    delay(5);           //���� ���ڿ� ���� ����
  }
  
  if(!myString.equals(""))  //myString ���� �ִٸ�
  { 
      if(myString.equals("fo")) // �� 
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
      
    myString="";  //myString ������ �ʱ�ȭ
  }  
}