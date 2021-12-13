#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 0);
  Serial.begin(9600);
  Serial.println("Arduino start!");
}
String label = "";
char buffer[33];
void lcd_clear(){
  lcd.setCursor(0,0);
  for(int i = 0 ; i < 16;i++)
    lcd.print(" ");
  lcd.setCursor(0,1);
    for(int i = 0 ; i < 16;i++)
    lcd.print(" ");
   
}
void loop() {
  int index = 0;
  bool haveData = false;
  while(Serial.available() > 0){
    haveData = true;
    buffer[index] = Serial.read();
    index++;
    if(index >=32) continue;
  }
  if(haveData){
    label = buffer;
    label.trim();
    Serial.println(label);
    lcd.clear();
    for(int i = 0; i < 16; i++ ){
      if(String(buffer[i])== "")continue;
      lcd.print(buffer[i]);
    }
    lcd.setCursor(0,1);
    for(int i = 16; i < 32; i ++ ){
      if(String(buffer[i])== "")break;
      lcd.print(buffer[i]);
    }
  }
  else{
    for(int i = 0;i<33;i++){
      buffer[i] = 0x00;
    }
  }
  delay(500);
}
