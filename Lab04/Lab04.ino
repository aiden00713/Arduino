int seg[]={11,10,9,8,7,6,5};  //儲存接角
int i,j;  //迴圈計數器
char ch; //
int num;
//共陰七段顯示器16進位編碼表
char TAB[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71}; //0~9 A-b-C-d-E-F
void output(byte dat);
void input();

void setup() {
  for(i=0;i<7;i++){
    pinMode(seg[i],OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  input();
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
    
    if(ch>='0' && ch<='9'){
      num = ch-'0';
      output(TAB[num]);
      Serial.print("顯示：");   //在監控視窗顯示訊息
      Serial.print(ch);
    }
    else if(ch>='A' && ch<='F'){
      num = ch-'A'+10;
      output(TAB[num]);
      Serial.print("顯示：");   //在監控視窗顯示訊息
      Serial.print(ch);
    }
    else if(ch>='a' && ch<='f'){
      num = ch-'a'+10;
      output(TAB[num]);
      Serial.print("顯示：");   //在監控視窗顯示訊息
      Serial.print(ch);
    }
  } 
}
