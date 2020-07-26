#include "DHT.h"
#include <FlexiTimer2.h>
#define NOTE_C4   262  //Do  第4八度
#define NOTE_D4   294  //Re
#define NOTE_E4   330  //Mi
#define DHTPIN 4
#define DHTTYPE DHT11
#define TrigPin A0
#define EchoPin A1
#define buttonPin1 A3
#define buttonPin2 A4
#define BuzzerPin A5
int seg[]={11,10,9,8,7,6,5};  //七段顯示器a-g段
int scan[]={13,12,3,2};  //控制端接角c1-c4
char TAB[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x67};
long duration;  //測量距障礙物的反射波時間
volatile char scan_line = 0;  //紀錄掃描線位置的變數(中斷用)
DHT dht(DHTPIN, DHTTYPE);
boolean buttonState1,buttonState2;
int i,j,k=0,l;
char data[4];
int hours = 14, minutes = 50, seconds=0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  pinMode(BuzzerPin,OUTPUT);
  
  for(i=0;i<7;i++){
    pinMode(seg[i],OUTPUT);
  }
  for(i=0;i<4;i++){
    pinMode(scan[i],OUTPUT);
    digitalWrite(scan[i],HIGH);
  }
  
  pinMode(buttonPin1,INPUT);
  pinMode(buttonPin2,INPUT);

  FlexiTimer2::set(5,1.0/1000,flash);
  FlexiTimer2::start();
}

void loop() {
  button1();
  button2();
}

void button1(){  //溫濕度感測
  buttonState1 = digitalRead(buttonPin1); //讀取按鈕狀態
  
  if(buttonState1 == LOW){  //按下
    int h = dht.readHumidity();
    int t = dht.readTemperature();
    Serial.print("T = ");
    Serial.print(t);
    Serial.print("度 ");
    Serial.print("H = ");
    Serial.print(h);
    Serial.println("%");

    data[0]=TAB[t/10];
    data[1]=TAB[t%10];
    data[2]=TAB[h/10];
    data[3]=TAB[h%10];
   

    for(l=0;l<4;l++){
      output(data[l]);
      digitalWrite(scan[l],HIGH);
      digitalWrite(scan[l],LOW);
    }

    
    tone(BuzzerPin,NOTE_C4,200);
    delay(500);
    tone(BuzzerPin,NOTE_D4,200);
    delay(500);
    tone(BuzzerPin,NOTE_E4,200);
    delay(500);
    
    delay(20);  //彈跳延遲
    while(1){
      buttonState1 = digitalRead(buttonPin1);
      if(buttonState1 == HIGH){  //放開
        break;
      }
    }
    delay(20);  //彈跳延遲
  }
}

void button2(){  //超音波感測
  buttonState2 = digitalRead(buttonPin2); //讀取按鈕狀態
  
  if(buttonState2 == LOW){  //按下
    test();
    tone(BuzzerPin,NOTE_C4,200);
    delay(1000);
    tone(BuzzerPin,NOTE_D4,200);
    delay(1000);
    tone(BuzzerPin,NOTE_E4,200);
    delay(1000);
    
    delay(20);  //彈跳延遲
    while(1){
      buttonState1 = digitalRead(buttonPin1);
      if(buttonState1 == HIGH){  //放開
        break;
      }
    }
    delay(20);  //彈跳延遲
  }
}

void flash(){
  digitalWrite(scan[scan_line],HIGH);  //七段顯示器初始
  k++;

  if(k%200==0){   //5*200 = 1000 (1s)
    seconds++;
    if(seconds==60){
      minutes++;
      seconds=0;
      
      if(minutes==60){
        minutes=0;
        hours++;
      }
    }
    Serial.print(hours);
    Serial.print("：");
    Serial.print(minutes);
    Serial.print("：");
    Serial.println(seconds);
  }
}

void test(){
  long cm;
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  duration = pulseIn(EchoPin,HIGH);
  cm = duration/58;
  Serial.print("Distance = ");
  Serial.print(cm);
  Serial.println("cm");
}

void output(byte dat){
  for(j=0;j<7;j++){
    if(dat%2==1){
      digitalWrite(seg[j],HIGH);
    }
    else{
      digitalWrite(seg[j],LOW);
    }
    dat = dat/2; //進行下一位元處理
  }
}
