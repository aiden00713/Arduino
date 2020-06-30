const byte LED[] = {11,10,9,8,7,6,5,4};  //儲存LED的接腳
int delaytime = 1000; //設定步驟延遲1秒
int i,no;
char ch;
const byte num = 8;  //設定迴圈計數器
void light01();
void light02();
void light03();
void light04();

void setup() {
  for(i=0;i<num;i++){
    pinMode(LED[i],OUTPUT); //設定pin腳輸出
  }
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){  //判斷緩衝區有無資料
    ch = Serial.read();  ////從串列緩衝區讀取一個字元
    if(ch=='1'){
      light01();
    }
    else if(ch=='2'){
      light02();
    }
    else if(ch=='A'){
      light03();
    }
    else if(ch=='B'){
      light04();
    }
    else if(ch=='C'){
      delaytime = Serial.parseInt();  //從串列緩衝區讀取有效整數資料
      Serial.print("延遲時間：");   //在監控視窗顯示訊息
      Serial.print(delaytime);
      Serial.println("ms");
    }
  }
}

void light01(){
  digitalWrite(LED[0],HIGH); //使用高態動作讓LED燈亮起
  delay(delaytime);  //延遲程式1秒
  digitalWrite(LED[0],LOW);  ////使用高態動作讓LED燈熄滅
}

void light02(){
  digitalWrite(LED[1],HIGH); //使用高態動作讓LED燈亮起
  delay(delaytime);  //延遲程式1秒
  digitalWrite(LED[1],LOW);  ////使用高態動作讓LED燈熄滅
}

void light03(){
  for(i=0;i<num;i++){
    digitalWrite(LED[i],HIGH); //使用高態動作讓LED燈亮起
    delay(delaytime);  //延遲程式1秒
    digitalWrite(LED[i],LOW);  ////使用高態動作讓LED燈熄滅
  }
}

void light04(){
  for(i=num-1;i>=0;i--){
    digitalWrite(LED[i],HIGH); //使用高態動作讓LED燈亮起
    delay(delaytime);  //延遲程式1秒
    digitalWrite(LED[i],LOW);  ////使用高態動作讓LED燈熄滅
  }
}
