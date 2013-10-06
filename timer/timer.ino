#include <LiquidCrystal.h>

const int X_Pin = 1;  // arduino pin for x 
const int Y_Pin = 2;  // arduino pin for y 
const int Z_Pin = 3;  // arduino pin for z 
int X_start;
int Y_start;
int Z_start;
LiquidCrystal lcd(12,11,5,4,3,2);
int minutes = 1;
const int buttonPin = 6;     // the number of the pushbutton pin
int buttonState = 0;
const int buzzerPin = 7;

void setup()
{ 
  Serial.begin(9600);
  X_start = analogRead(X_Pin);
  Y_start = analogRead(Y_Pin);
  Z_start = analogRead(Z_Pin);
  pinMode(buzzerPin, OUTPUT);
  lcd.begin(16, 2);
  
  lcd.clear();

  lcd.print("Time remaining: ");
  lcd.setCursor(1,1);
  lcd.print(minutes);
  lcd.setCursor(2,1);
  lcd.print(":");
  lcd.setCursor(3,1);
  lcd.print("00");
  //delay(1000);
  pinMode(buttonPin, INPUT);
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == LOW){
    
    minutes--;
    for (int m = minutes ; m >= 0; m--)
    {
      lcd.setCursor(1,1);
      lcd.print(m);
        
      for ( int s1 = 5 ;  s1 >= 0 ; s1--)
      {
        lcd.setCursor(3,1);
        lcd.print(s1);
        
        for ( int s2 = 9; s2 >= 0; s2--)
        {
          lcd.setCursor(4,1);
          lcd.print(s2);
          delay(1000);
        }
     
       
       }
     
    }
    lcd.clear();
    lcd.print("Time is up!!");
    tone(buzzerPin, 600, 1000);
    delay(10);
    while (1) {
      if (readdAccelerometer() == 0) {
        Serial.print("Change detected! ");
        break;
      }
      tone(buzzerPin, 600, 1000);
      delay(10);
    }
    exit(0);
  }
}

int readdAccelerometer() {
    int x = analogRead(X_Pin);      // read analog pin for x raw     
    int y = analogRead(Y_Pin);      // read analog pin for y raw 
    int z = analogRead(Z_Pin);      // read analog pin for z raw   
    if ((abs(X_start - x) > 200) || (abs(Y_start - y) > 200) || (abs(Z_start - z) > 200)) {
      return 1;
    } else {
      return 0;
   }
}
