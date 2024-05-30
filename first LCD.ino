//Display a string of characters or message for LCD to display

#include <LiquidCrystal.h>

const int rs = 9, en = 8, d4 = 5, d5 = 4, d6 =  3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
unsigned char x = 0;
String message;
int counter = 0;


void setup() {
  
  lcd.begin(16, 2);
  lcd.clear();
  
  Serial.begin(9600);
}


void loop() {
  if (counter < 2) {
    if (counter == 0) {
      Serial.println("Enter a message for the LCD to display: ");
      lcd.setCursor(0, 0);
    }
    else {
      //Serial.println("Enter a message for the LCD to display: ");
      lcd.setCursor(0, 1);
    }
    
    while (Serial.available() == 0) {}
    //readString keeps leaving weird newline characters at the end?
    message = Serial.readString(); //The way to fix this I think is to put the option "No Line Ending" in the console or readStringUntil("\n"); but i dont know if that's allowed.
    lcd.print(message);
    ++counter;
  }
