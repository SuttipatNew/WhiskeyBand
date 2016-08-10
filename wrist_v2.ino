#include<LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);
int sw = 0;
String remote = "";
void setup() {
  pinMode(A2, INPUT);
  pinMode(2, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  Serial1.begin(115200);

}

void loop() {
  sw = digitalRead(2);
  if(Serial1.available())
  {
    remote = Serial1.readStringUntil('\n');
    Serial1.flush();
  }
  int remoteL = sizeof(remote)/sizeof(char);
  if(sw == 0 || (remoteL >= 2 && (remote[0] == '2' && remote[1] == '0')))
  {
    lcd.setCursor(0,0);
    lcd.print("Alcohol test");
    lcd.setCursor(0,1);
    delay(500);
    for(int i = 3; i >= 1; i--)
    {
      lcd.print(i);
      lcd.print(" ");
      delay(1000);
    }
    int alc = 0;
    for(int i = 0; i < 20; i++)
    {
      alc += analogRead(A1);
      delay(200);
    }
    alc /= 20;
    float alres = alc/1023.0*0.21;
    if(alres < 0)
    {
      alres *= -1;
    }
    lcd.clear();
    lcd.print("Alc: ");
    lcd.print(alres);
    lcd.print(" BAC");
    delay(3000);
    lcd.clear();
    lcd.print("Temp test");
    lcd.setCursor(0,1);
    delay(500);
    for(int i = 3; i >= 1; i--)
    {
      lcd.print(i);
      lcd.print(" ");
      delay(1000);
    }
    int temp = 0;
    for(int i = 0; i < 20; i++)
    {
      temp += (25*analogRead(A2) - 2050)/100;
      delay(300);
    }
    temp /= 20;
    lcd.clear();
    lcd.print("Temp: ");
    lcd.print(temp);
    delay(3000);
    char str[10];
    sprintf(str, "%d,%d", alc, temp);
    //Serial1.println(alc);
    //Serial1.println(temp);
    Serial1.println(str);
    //test
    Serial.println(str);
    //
    lcd.clear();
    lcd.print("Testing complete");
    delay(2000);
    lcd.clear();
  }
  remote = "";
}
