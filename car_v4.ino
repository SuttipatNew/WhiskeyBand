#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);
#define LED1 11
int sw = 1, Status = 0;
String start = "";

void startCar()
{
  digitalWrite(LED1, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Start");
  delay(3000);
  lcd.clear();
}
void stopCar()
{
  digitalWrite(LED1, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Stop");
  delay(3000);
  lcd.clear();
}
void getDrunk()
{
  digitalWrite(LED1, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("You're get drunk");
  lcd.setCursor(0,1);
  lcd.print("Please call taxi");
  analogWrite(10, 100);
  delay(500);
  analogWrite(10, 0);
  delay(400);
  analogWrite(10,100);
  delay(500);
  analogWrite(10, 0);
  delay(3000);
  lcd.clear();
}

void setup() {
  lcd.begin(16, 2);
  pinMode(LED1, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
  Serial1.begin(115200);
}

void loop() {
  sw = digitalRead(2);
  if(sw == 0)
  { 
    if(Status == 1)
    {
      stopCar();
      Status = 0;
      delay(1000);
    }
    else
    {
      Serial1.println(20);
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("Connecting");
      delay(1000);
      while(!Serial1.available() && digitalRead(2) == 1){}
      if(digitalRead(2) == 1)
      {
        start = Serial1.readStringUntil('\n');
        Serial.println(start);
        if(start[0] == '1')
        {
          startCar();
          Status = 1;
        }
        else if(start[0] == '0')
        {
          getDrunk();
          Status = 0;
        }
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Canceled");
        delay(3000);
        lcd.clear();
      }
    }
  }
  Serial.println(Status);
  start = "";
  sw = 1;
}


