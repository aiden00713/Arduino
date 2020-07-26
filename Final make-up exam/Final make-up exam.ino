#include <FlexiTimer2.h>
#define buttonPin1 A3

int seg[]={11,10,9,8,7,6,5};  //七段顯示器a-g段
int scan[]={13,12,3,2};  //控制端接角c1-c4
char TAB[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x67};
volatile char scan_line = 0;  //紀錄掃描線位置的變數(中斷用)
boolean buttonState1;
char num[]={'0','7','0','5','0','6','0','5'};
char numin[8];
int i,j,k=0,test=0;
int hours = 0, minutes = 10, seconds=30;

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  for(i=0;i<7;i++){
    pinMode(seg[i],OUTPUT);
  }
  for(i=0;i<4;i++){
    pinMode(scan[i],OUTPUT);
    digitalWrite(scan[i],HIGH);
  }
  
  pinMode(buttonPin1,INPUT);

  FlexiTimer2::set(5,1.0/1000,flash);
  FlexiTimer2::start();
}

void loop() {
  if(Serial.available()){ //判斷緩衝區有無資料
    for(i=0;i<8;i++){
      numin[i]= Serial.read();
    }
  }
  
  for(i=0;i<8;i++){
    if(num[i]==numin[i]){
      test++;
    }
  }
  
  if(test==8)
  {
    Serial.println("OK");
    delay(1000);
  }
  else
  {
    Serial.println("error");
    test = 0;
    delay(1000);
  }
  
  buttonState1 = digitalRead(buttonPin1); //讀取按鈕狀態
  
  if(buttonState1 == LOW){  //按下
    minutes++;
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
  scan_line=(scan_line+1)%4;
  k++;

  if(k%200==0){   //5*200 = 1000 (1s)
    seconds++;
    digitalWrite(4,HIGH);
    Serial.print(minutes);
    Serial.print("：");
    Serial.println(seconds);
    digitalWrite(4,LOW);
    if(seconds==60){
      minutes++;
      seconds=0;
      
      if(minutes==60){
        minutes=0;
        hours++;
      }
    }
  }

  switch(scan_line){
    case 0:
      output(TAB[minutes/10]);
      break;
    case 1:
      output(TAB[minutes%10]);
      break;
    case 2:
      output(TAB[seconds/10]);
      break;
    default:
      output(TAB[seconds%10]);
      break;
  }
  digitalWrite(scan[scan_line],LOW);
}

void output(byte dat){
  for(j=0;j<7;j++){
    if(dat%2==1){
      digitalWrite(seg[j],HIGH);
    }else{
      digitalWrite(seg[j],LOW);
    }
    dat = dat/2; //進行下一位元處理
  }
}
