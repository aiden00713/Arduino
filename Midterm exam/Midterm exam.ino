const byte LED[] = {11,10,9,8,7,6,5,4};  //儲存LED的接腳
int delaytime;
int i,j=0,k=7;  //設定迴圈計數器
int a,b,c;
const byte num = 8; 

void setup() {
  for(i=0;i<num;i++){
    pinMode(LED[i],OUTPUT); //設定pin腳輸出
  }
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()){  //判斷緩衝區有無資料
    a = Serial.parseInt();  //從串列緩衝區讀取一個有效整數
    
    if(a>=0 && a<100){  //判斷數值是否在0~99的範圍
      b = a/10; //a的十位數給b
      c = a%10; //a的個位數給c

      //在監控視窗顯示訊息
      Serial.print("a=");
      Serial.println(a);
      Serial.print("b=");
      Serial.println(b);
      Serial.print("c=");
      Serial.println(c);

      if(c<5){
        delaytime = c*200;
        light01();
      }
      else if(c>=5){
        delaytime = c*100;
        light02();
      }
    }
    while(Serial.read()>=0);  //清空緩衝區
  } 
}

void light01(){
  j=0,k=7;
  for(i=0;i<num/2;i++){  //執行上半部
    digitalWrite(LED[j],HIGH);
    Serial.print("亮");
    Serial.println(j+1);
    delay(delaytime);
    digitalWrite(LED[j],LOW);
    j+=2;
  }
  for(i=4;i<num;i++){  //執行下半部
    digitalWrite(LED[k],HIGH);
    Serial.print("亮");
    Serial.println(k+1);
    delay(delaytime);
    digitalWrite(LED[k],LOW);
    k-=2;
  }
  Serial.println("OK");
}

void light02(){
  j=0,k=7;
  for(i=0;i<num/2;i++){  //執行上半部
    digitalWrite(LED[k],HIGH);
    Serial.print("亮");
    Serial.println(k+1);
    delay(delaytime);
    digitalWrite(LED[k],LOW);
    k-=2;
  }
  for(i=4;i<num;i++){  //執行下半部
    digitalWrite(LED[j],HIGH);
    Serial.print("亮");
    Serial.println(j+1);
    delay(delaytime);
    digitalWrite(LED[j],LOW);
    j+=2;
  }
  Serial.println("OK");
}
