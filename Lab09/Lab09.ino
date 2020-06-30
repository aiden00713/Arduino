const byte TrigPin = 6;
const byte EchoPin = 7;
const byte BuzzerPin = 8;

long duration;  //測量距障礙物的反射波時間
int num[4],t;
void setup() {
  Serial.begin(9600);
  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  pinMode(BuzzerPin,OUTPUT);
}

void loop() {
  numsort();
}

void numsort(){
  if(Serial.available()){ //判斷緩衝區有無資料
    for(int i=0;i<4;i++){
      num[i] = Serial.parseInt();
    }
  }
  //進行數字大到小排序
  for (int i=0;i<4;i++){
    for (int j=i;j<3;j++){
      if (num[j] < num[j+1]){
        t = num[j];
        num[j] = num[j+1]; 
        num[j+1] = t;
      }
    }
  }

  for (int i=0;i<4;i++){
    Serial.println(num[i]);
  }
  test();
}

void test(){
  long cm;
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  duration = pulseIn(EchoPin,HIGH);
  cm = duration/58;
  Serial.print("Distance = ");
  Serial.print(cm);
  Serial.println("cm");

  if(cm<=num[3]){
    tone(BuzzerPin,400);
  }
  else if(cm<=num[2]){
    tone(BuzzerPin,400,50);
    delay(100);
  }
  else if(cm<=num[1]){
    tone(BuzzerPin,400,100);
    delay(300);
  }
  else if(cm<=num[0]){
    tone(BuzzerPin,400,100);
    delay(500);
  }
  else{
    tone(BuzzerPin,400,400);
    delay(1500);
  }
}
