#include<Servo.h>
Servo motor;
int ch1=0;    
int ch2=0;
int ch3=0;
int ch4=0;
int ch5=0;
int ch6=0;
int trigPin = 48; 
int echoPin = 7;  
long sure;
long uzaklik;
const int Enable_A = 6; 
const int inputA1 = 53;
const int inputA2 = 52;
int a=2;
int b=3;
int c=4;
int d=5;
bool a1;
bool b1;
bool c1;
bool d1;
void setup() {
  Serial.begin(9600);
  pinMode (13,INPUT);
  pinMode (12,INPUT);
  pinMode (11,INPUT);
  pinMode (10,INPUT);
  pinMode (9,INPUT);
  pinMode (8,INPUT);
  pinMode(a,INPUT);
  pinMode(b,INPUT);
  pinMode(c,INPUT);
  pinMode(d,INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin,INPUT); 
  pinMode(Enable_A, OUTPUT);
  pinMode(inputA1, OUTPUT);
  pinMode(inputA2, OUTPUT);
  motor.attach(13);
}
void loop() {
  while(1){
    digitalWrite(trigPin, LOW); /* sensör pasif hale getirildi */
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH); /* Sensore ses dalgasının üretmesi için emir verildi */
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);  /* Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi */ 
    sure = pulseIn(echoPin, HIGH); /* ses dalgasının geri dönmesi için geçen sure ölçülüyor */
    uzaklik= sure /29.1/2; /* ölçülen sure uzaklığa çevriliyor */            
    if(uzaklik > 200)
      uzaklik = 200;
    Serial.print("Uzaklik ");  
    Serial.print(uzaklik); /* hesaplanan uzaklık bilgisayara aktarılıyor */
    Serial.println(" CM olarak olculmustur.");  
    delay(1);
    ch1= pulseIn(8,HIGH);
    Serial.print("ch1:     ");
    Serial.print(ch1);
    Serial.print("\t");
    delay(10);
    ch2 =pulseIn(9,HIGH);
    Serial.print("ch2:     ");
    Serial.print(ch2);
    Serial.print("\t");  
    delay(10);
    ch3 =pulseIn(10,HIGH);
    Serial.print("ch3:     ");
    Serial.print(ch3);
    Serial.print("\t");  
    delay(10);
    ch4 =pulseIn(11,HIGH);
    Serial.print("ch4:     ");
    Serial.print(ch4);
    Serial.print("\t");  
    delay(10);
    ch5 =pulseIn(12,HIGH);
    Serial.print("ch5:     ");
    Serial.print(ch5);
    Serial.println("\t");  
    delay(10);
    ch5 =pulseIn(12,HIGH);
    if(ch5<1200){
      ch1= pulseIn(8,HIGH);         //----------kumanda kanallarını okuyor----------//
      ch2 =pulseIn(9,HIGH);
      ch3 =pulseIn(10,HIGH);
      ch4 =pulseIn(11,HIGH);
    if(ch3>1750){                   //----------motor ileri doğru gider----------//
       if(uzaklik<20){
         digitalWrite(Enable_A, LOW);
        digitalWrite(inputA1, LOW);
        digitalWrite(inputA2, LOW);}
       else if(uzaklik>20){
        analogWrite(Enable_A, 255);
        digitalWrite(inputA1, HIGH);
        digitalWrite(inputA2, LOW);}}
    else if (ch3>1680&&ch3<1750){   //----------motor ileri doğru gider----------//
      if(uzaklik<20){
        digitalWrite(Enable_A, LOW);
        digitalWrite(inputA1, LOW);
        digitalWrite(inputA2, LOW);}
      else if(uzaklik>20){
        analogWrite(Enable_A, 180);
        digitalWrite(inputA1, HIGH);
        digitalWrite(inputA2, LOW);}}
    else if (ch3>1600&&ch3<1680){   //----------motor ileri doğru gider----------//
      if(uzaklik<20){
        digitalWrite(Enable_A, LOW);
        digitalWrite(inputA1, LOW);
        digitalWrite(inputA2, LOW);}
      else if(uzaklik>20){
        analogWrite(Enable_A, 100);
        digitalWrite(inputA1, HIGH);
        digitalWrite(inputA2, LOW);}}
    else if (ch3<1370&&ch3>1300){   //----------motor geriye doğru gider----------//
      analogWrite(Enable_A, 180);
      digitalWrite(inputA1, LOW);
      digitalWrite(inputA2, HIGH);}
    else if (ch3<1300&&ch3>1200){   //----------motor geriye doğru gider----------//
      analogWrite(Enable_A, 180);
      digitalWrite(inputA1, LOW);
      digitalWrite(inputA2, HIGH);}
    else if (ch3<1200){             //----------motor geriye doğru gider----------//
      analogWrite(Enable_A, 255);
      digitalWrite(inputA1, LOW);
      digitalWrite(inputA2, HIGH);}
    else{                           //----------motorları durdur-----------//
      digitalWrite(Enable_A, LOW);}
    if(ch1>1580){
      motor.write(50);}
    else if(ch1<1400){
      motor.write(130);}
    else{
      motor.write(90);}  
    }
  else if(ch5>1700){
    a1 = digitalRead(a);
    b1 = digitalRead(b);
    c1 = digitalRead(c);
    d1 = digitalRead(d);
    if(a1==1){                      //----------motor ileri doğru gider----------//
      motor.write(135);             //----------sağa döndür ön tekerleri----------//
      delay(1000);                  //----------ön tekerler döndükten sonra arka motorları aktif yap----------//
      analogWrite(Enable_A, 255);   
      digitalWrite(inputA1, HIGH);  
      digitalWrite(inputA2, LOW);}
    else if(b1==1){                 //----------motor geri doğru gider----------//
      motor.write(90);
      analogWrite(Enable_A, 255);
      digitalWrite(inputA1, LOW);
      digitalWrite(inputA2, HIGH);}
    else if(c1==1){                 //----------motor ileri doğru gider----------//
      motor.write(45);              //----------ön tekerleri sola döndür----------//
      delay(1000);                  //----------ön tekerler döndükten sonra arka motorları aktif yap----------//
      analogWrite(Enable_A, 255);
      digitalWrite(inputA1, HIGH);
      digitalWrite(inputA2, LOW);}
    else if(d1==1){                 //----------motor ileri doğru gider----------//
      motor.write(90);
      analogWrite(Enable_A, 255);
      digitalWrite(inputA1, HIGH);
      digitalWrite(inputA2, LOW);}
    else{
      digitalWrite(Enable_A, LOW);  //----------motorları durdur----------//
      motor.write(90);              //----------ön tekerleri düz yap----------// 
      }
    }
}
}
