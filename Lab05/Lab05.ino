int seg[]={11,10,9,8,7,6,5};  //儲存七段顯示器接角
int buttonPin1 = 4; //按鈕1接角
int buttonPin2 = 3; //按鈕2接角
int i,j;  //迴圈計數器
char ch; //
int num=0;
boolean buttonState1,buttonState2;
//共陰七段顯示器16進位編碼表
char TAB[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71}; //0~9 A-b-C-d-E-F
void output(byte dat);
void input();
void button1();
void button2();
void test();

void setup() {
  for(i=0;i<7;i++){
    pinMode(seg[i],OUTPUT);
  }
  Serial.begin(9600);

  pinMode(buttonPin1,INPUT);
  pinMode(buttonPin2,INPUT);
  output(TAB[0]);
}

void loop() {
  test();
  input();
  button1();
  button2();
}

void output(byte dat){
  for(j=0;j<7;j++){
    if(dat%2==1){
      digitalWrite(seg[j],HIGH);
    }
    else{
      digitalWrite(seg[j],LOW);
    }
    dat = dat/2;  //進行下一位元處理
  }
}

void input(){
 if(Serial.available()){  //判斷緩衝區有無資料
    ch = Serial.read();  //從串列緩衝區讀取一個字元
    
    if(ch=='+'){
      num+=1;
      test();
      output(TAB[num]);
      Serial.write("+");   //在監控視窗顯示訊息
    }
    else if(ch=='-'){
      num-=1;
      test();
      output(TAB[num]);
      Serial.write("-");   //在監控視窗顯示訊息
    }
  } 
}

//判斷按鈕1是否按下(+)
void button1(){    
  buttonState1 = digitalRead(buttonPin1); //讀取按鈕狀態
  
  if(buttonState1 == LOW){  //按下
    num+=1;
    test();
    output(TAB[num]);
    
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

//判斷按鈕2是否按下(-)
void button2(){    
  buttonState2 = digitalRead(buttonPin2); //讀取按鈕狀態
  
  if(buttonState2 == LOW){  //按下
    num-=1;
    test();
    output(TAB[num]);
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

void test(){
  if(num == 16){
    num = 0;
  }
  else if(num == -1){
    num = 15;
  }
}
