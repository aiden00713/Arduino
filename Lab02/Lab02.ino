const byte LED[] = {11,10,9,8,7,6,5,4};  //儲存LED的接腳
int delaytime1 = 500;  //設定延遲時間0.5秒
int delaytime2 = 2000; //設定各步驟延遲2秒
int i,j,k;
const byte num = 8;  //設定迴圈計數器

void setup() {
  for(i=0;i<num;i++){
    pinMode(LED[i],OUTPUT); //設定pin腳輸出
  }
}

void loop() {
  light01();  //執行01
  delay(delaytime2);  //延遲程式2秒
  light02();  //執行02
  delay(delaytime2);  //延遲程式2秒
  light03();  //執行03
  delay(delaytime2);  //延遲程式2秒
  light04();  //執行04
  delay(delaytime2);  //延遲程式2秒
  light05();  //執行05
  delay(delaytime2);  //延遲程式2秒
  light06();
}

void light01(){
  for(i=0;i<num;i++){
    digitalWrite(LED[i],HIGH); //使用高態動作讓LED燈亮起
    delay(delaytime1);  //延遲程式0.5秒
    digitalWrite(LED[i],LOW);  ////使用高態動作讓LED燈熄滅
  }
}

void light02(){
  for(i=num-1;i>=0;i--){
    digitalWrite(LED[i],HIGH); //使用高態動作讓LED燈亮起
    delay(delaytime1);  //延遲程式0.5秒
    digitalWrite(LED[i],LOW);  ////使用高態動作讓LED燈熄滅
  }
}

void light03(){
  for(i=0;i<num;i++){
    digitalWrite(LED[i],HIGH); //使用高態動作讓LED燈亮起
    delay(delaytime1);  //延遲程式0.5秒
  }
  for(i=0;i<num;i++){
    digitalWrite(LED[i],LOW); //使用高態動作讓LED燈熄滅
  }
}

void light04(){
  for(i=num-1;i>=0;i--){
    digitalWrite(LED[i],HIGH); //使用高態動作讓LED燈亮起
    delay(delaytime1);  //延遲程式0.5秒
  }
  for(i=0;i<num;i++){
    digitalWrite(LED[i],LOW); //使用高態動作讓LED燈熄滅
  }
}

void light05(){
  for(i=0;i<num/2;i++){
    j=num-i-1;

    digitalWrite(LED[i],HIGH); //使用高態動作讓LED燈亮起
    digitalWrite(LED[j],HIGH); //使用高態動作讓LED燈亮起
    delay(delaytime1);  //延遲程式0.5秒
    digitalWrite(LED[i],LOW); //使用高態動作讓LED燈熄滅
    digitalWrite(LED[j],LOW); //使用高態動作讓LED燈熄滅
    delay(delaytime1);  //延遲程式0.5秒
  }
    digitalWrite(LED[i],LOW); //使用高態動作讓LED燈熄滅
    digitalWrite(LED[j],LOW); //使用高態動作讓LED燈熄滅
    delay(delaytime1);  //延遲程式0.5秒
  for(i=4;i<num;i++){
    j=num-i-1;

    digitalWrite(LED[j],HIGH); //使用高態動作讓LED燈亮起
    digitalWrite(LED[i],HIGH); //使用高態動作讓LED燈亮起
    delay(delaytime1);  //延遲程式0.5秒
    digitalWrite(LED[j],LOW); //使用高態動作讓LED燈熄滅
    digitalWrite(LED[i],LOW); //使用高態動作讓LED燈熄滅
    delay(delaytime1);  //延遲程式0.5秒
  }
    digitalWrite(LED[i],LOW); //使用高態動作讓LED燈熄滅
    digitalWrite(LED[j],LOW); //使用高態動作讓LED燈熄滅
    delay(delaytime1);  //延遲程式0.5秒
}

void light06(){
  for(i=0;i<num/2;i++){
    j=num-i-1;
    digitalWrite(LED[i],HIGH); //使用高態動作讓LED燈亮起
    digitalWrite(LED[j],HIGH); //使用高態動作讓LED燈亮起
    delay(delaytime1);  //延遲程式0.5秒
  }
  
  for(k=0;k<num;k++){
    digitalWrite(LED[k],LOW); //使用高態動作讓LED燈熄滅
  }
  delay(delaytime1);  //延遲程式0.5秒
  
  for(i=4;i<num;i++){
    j=num-i-1;

    digitalWrite(LED[i],HIGH); //使用高態動作讓LED燈亮起
    digitalWrite(LED[j],HIGH); //使用高態動作讓LED燈亮起
    delay(delaytime1);  //延遲程式0.5秒
  }

  for(k=0;k<num;k++){
    digitalWrite(LED[k],LOW); //使用高態動作讓LED燈熄滅
  }
  delay(delaytime1);  //延遲程式0.5秒
}
