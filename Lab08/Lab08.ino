#include <LiquidCrystal.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

//LiquidCrystal led(RS,Enable,D4,D5,D6,D7) RW接地
LiquidCrystal lcd(12,11,7,6,5,4);

DHT dht(DHTPIN, DHTTYPE);

byte up = 0 , down = 1;
byte sp0[8] = {B01111, B11110, B11100, B11100, B11100, B11110, B01111, B00000};
byte sp1[8] = {B11110, B01111, B00111, B00111, B00111, B01111, B11110, B00000};

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  Serial.println("DHT11 run!");
  dht.begin();
  
  lcd.createChar(0,sp0);
  lcd.createChar(1,sp1);
}

void loop() {
  tandh();
  elf();
}

void tandh(){
  lcd.home();  //游標回到0,0左上角
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  int t = dht.readTemperature();
  lcd.print("H:");
  lcd.print(h);
  lcd.print("%");
  lcd.print(" T:");
  lcd.print(t);
  lcd.print((char) 0xDF);
  lcd.print("C");
}

void elf(){
  //左至右
  for(int i=0;i<20;i++){
    lcd.setCursor(i,1); //游標移到i,1
    lcd.print((char)up);
    delay(500);
    lcd.setCursor(i-1,1); //游標移到前一位
    lcd.print("  ");  //清空
  }

  //右至左
  for(int i=19;i>=0;i--){
    lcd.setCursor(i+1,1); //游標移到前一位
    lcd.print("  ");  //清空
    lcd.setCursor(i,1); //游標移到i,1
    lcd.print((char)down);
    delay(500);
  }
}
