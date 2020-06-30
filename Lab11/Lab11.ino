#define BuzzerPin 13
#define led1 2
#define led2 3
#define buttonPin1 A5
#define buttonPin2 A4
#define buttonPin3 A3
int seg[]={11,10,9,8,7,6,5}; //儲存接角
boolean buttonState1,buttonState2,buttonState3;
int delaytime1 = 500; //設定延遲時間0.5秒
int num,i,j;
int mode = -1;
void setup() {
  for(i=0;i<7;i++){
    pinMode(seg[i],OUTPUT);
  }
  pinMode(buttonPin1,INPUT);
  pinMode(buttonPin2,INPUT);
  pinMode(buttonPin3,INPUT);
  pinMode(BuzzerPin,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
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

void loop() {
  button1();
  button2();
  button3();
}

//判斷按鈕1是否按下
void button1(){    
  buttonState1 = digitalRead(buttonPin1); //讀取按鈕狀態
  
  if(buttonState1 == LOW){  //按下
    output(0x71);
    digitalWrite(led1,HIGH);
    delay(delaytime1);
    digitalWrite(led1,LOW);
    tone(BuzzerPin,500,300);
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

//判斷按鈕2是否按下
void button2(){    
  buttonState2 = digitalRead(buttonPin2); //讀取按鈕狀態
  
  if(buttonState2 == LOW){  //按下
    output(0x6D);
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    delay(delaytime1);
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    tone(BuzzerPin,500,1000);
    
    delay(20);  //彈跳延遲
    while(1){
      buttonState2 = digitalRead(buttonPin2);
      if(buttonState2 == HIGH){  //放開
        break;
      }
    }
    delay(20);  //彈跳延遲
  }
}

//判斷按鈕3是否按下
void button3(){    
  buttonState3 = digitalRead(buttonPin3); //讀取按鈕狀態
  
  if(buttonState3 == LOW){  //按下
    output(0x7C);
    digitalWrite(led2,HIGH);
    delay(delaytime1);
    digitalWrite(led2,LOW);
    
    tone(BuzzerPin,500,300);
    delay(500);
    tone(BuzzerPin,500,300);
    
    delay(20);  //彈跳延遲
    while(1){
      buttonState3 = digitalRead(buttonPin3);
      if(buttonState3 == HIGH){  //放開
        break;
      }
    }
    delay(20);  //彈跳延遲
  }
}
