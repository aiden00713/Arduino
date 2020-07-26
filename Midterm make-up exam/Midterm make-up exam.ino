const int seg[]={11,10,9,8,7,6,5};  //儲存接角
int delaytime = 2000;
int i,j=0,k=7;  //設定迴圈計數器
int a,b,c;
const byte num = 8; 
char TAB[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x67}; //0~9

void setup() {
  for(i=0;i<num;i++){
    pinMode(seg[i],OUTPUT); //設定pin腳輸出
  }
  Serial.begin(9600);
  output(TAB[0]);
}

void loop(){
  if(Serial.available()){  //判斷緩衝區有無資料
    a = Serial.parseInt();  //從串列緩衝區讀取一個有效整數
    
    if(a>=0 && a<100){  //判斷數值是否在0~99的範圍
      b = a/10; //a的十位數給b
      c = a%10; //a的個位數給c

      //在監控視窗顯示訊息
      Serial.print("b=");
      Serial.println(b);
      Serial.print("c=");
      Serial.println(c);

      while(true){
        output(TAB[b]);
        delay(delaytime);
        output(TAB[c]);
        delay(delaytime);
        if(Serial.available()){
          break;
        }
      }
    }
    while(Serial.read()>=0);  //清空緩衝區
  } 
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
