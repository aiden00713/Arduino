int seg[]={11,10,9,8,7,6,5};
int scan[]={13,12,3,2};
int delaytime=5;
int i=0,j=0,num=0;
//16進位編碼表
char TAB[] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71}; //0~9 A-b-C-d-E-F
char data[] = {0x06,0x5B,0x4F,0x66};
char ch;

void setup() {
  for(i=0;i<7;i++){
    pinMode(seg[i],OUTPUT);
  }
  for(i=0;i<4;i++){
    pinMode(scan[i],OUTPUT);
  }
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()){  //判斷緩衝區有無資料
    ch = Serial.read();  //從串列緩衝區讀取一個字元

    for(i=0;i<4;i++){
      data[i] = data[i+1];  //0-1 1-2 2-3
    }
    
    if(ch>='0' && ch<='9'){  //輸入字元0~9
      num = ch-'0';
      data[3] = TAB[num];
      Serial.print("顯示：");   //在監控視窗顯示訊息
      Serial.print(ch);
    }
    if(ch>='A' && ch<='F'){  //輸入字元A~F
      num = ch-'A'+10;
      data[3] = TAB[num];
      Serial.print("顯示：");   //在監控視窗顯示訊息
      Serial.print(ch);
    }
    if(ch>='a' && ch<='f'){  //輸入字元a~f
      num = ch-'a'+10;
      data[3] = TAB[num];
      Serial.print("顯示：");   //在監控視窗顯示訊息
      Serial.print(ch);
    }
  }
  
  for(j=0;j<4;j++){
    output(data[j]);
    digitalWrite(scan[j],LOW);
    delay(delaytime);
    digitalWrite(scan[j],HIGH);
  }
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
