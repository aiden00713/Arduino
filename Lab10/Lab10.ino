#include <FlexiTimer2.h>
int seg[]={11,10,9,8,7,6,5};  //七段顯示器a-g段
int scan[]={13,12,3,2};  //控制端接角
int buttonPin = 4; //按鈕接角
char TAB[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x67};  //16進位編碼表0-9
volatile char scan_line = 0;  //紀錄掃描線位置的變數(中斷用)
int i,j,k=0,num=0;
int hours = 0, minutes = 0, seconds=0;
boolean buttonState;

void setup() {
  for(i=0;i<7;i++){
    pinMode(seg[i],OUTPUT);
  }
  for(i=0;i<4;i++){
    pinMode(scan[i],OUTPUT);
    digitalWrite(scan[i],HIGH);
  }
  FlexiTimer2::set(5,1.0/1000,flash);
  FlexiTimer2::start();
}

void loop() {
  buttonState = digitalRead(buttonPin); //讀取按鈕狀態
  if(buttonState == LOW){ //按下
    num+=1;
    delay(20); //彈跳延遲
    while(1){
      buttonState = digitalRead(buttonPin);
      if(buttonState == HIGH){ //放開
        break;
      }
    }
    delay(20); //彈跳延遲
  }
}

void flash(){
  digitalWrite(scan[scan_line],HIGH);  //七段顯示器初始
  scan_line=(scan_line+1)%4;
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
  }

  if(num%2==0){
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
    }
    else{
      switch(scan_line){
        case 0:
          output(TAB[hours/10]);
          break;
        case 1:
          output(TAB[hours%10]);
          break;
        case 2:
          output(TAB[minutes/10]);
          break;
        default:
          output(TAB[minutes%10]);
          break;
      }
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
