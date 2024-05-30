//Joystick has directionality and wraps around the LCD
//When clicked inputs a character at the position on the LCD the joystick was clicked

#include "Timer.h"
#include <LiquidCrystal.h>

const int rs = 9, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int yCursor = 0;
int xCursor = 0;
int count = 0; //character count
int prevbuttonState; 

void setup() {
  //initialize LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0); //set the cursor to the top left corner.

  prevbuttonState = digitalRead(6);
  pinMode(6, INPUT_PULLUP); //Joystic button input

  TimerSet(200); 
  TimerOn(); 

  Serial.begin(9600);
}

void tick(void) {
  int xValue = analogRead(A0);
  int yValue = analogRead(A1);
  int button = digitalRead(6);
  int prevButtonState = 1;
  enum STATES { INIT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, BUTTON_PRESS, WRAP, CLEAR } gState = INIT;

  Serial.print("State: ");
  Serial.println(gState);

  //transitions (switch case was not working for me some transitions were preventing others from starting and I couldnt figure out which one)
  if (prevbuttonState == HIGH && button == LOW) {
          if (count >= 5) { //5 or more characters clear
              gState = CLEAR;
          }
          else {
              if (xCursor >= 15) {
                  gState = WRAP;
              }
              else {
                  gState = (button == LOW) ? BUTTON_PRESS : INIT; //if conditional button==LOW , then BUTTON_PRESS if true, otherwise INIT if false.
              }
          } 
      }
  else if (xValue < 250) {
        gState = MOVE_LEFT;
        }
  else if (xValue > 900) {
        gState = MOVE_RIGHT;
        }
  else if (yValue < 250) {
    gState = MOVE_UP;
    }
  else if (yValue > 900) {
    gState = MOVE_DOWN;
    }
//actions
  switch(gState) {
    case MOVE_LEFT:
      if (xCursor > 0) {
        --xCursor;
      }
      break;
    case MOVE_RIGHT:
      if (xCursor < 15) {
        ++xCursor;
      }
      break;
    case MOVE_UP:
      if (yCursor > 0) {
        --yCursor;
      }
      break;
    case MOVE_DOWN:
      if (yCursor < 1) {
        yCursor++;
      }
      break;
    case BUTTON_PRESS:
      lcd.print("L");
      ++count;
      if (xCursor < 15) { //xCursor is incrmeented if not at end of line
        ++xCursor;
      }
      break;
    case WRAP:
    //if on the first line move to the second, vice versa
      if (yCursor == 0) {
        yCursor = 1;
      }
      else {
        yCursor = 0;
      }
      xCursor = 0;
      break;

    case CLEAR:
      lcd.clear();
      xCursor = 0;
      yCursor = 0;
      count = 0;
      break;
  }
    lcd.setCursor(xCursor, yCursor);
    prevbuttonState = button;
}

void loop() {
  while (!TimerFlag) {}
  TimerFlag = 0;
  tick();

  int xValue = analogRead(A0);
  int yValue = analogRead(A1);
  int button = digitalRead(6);

  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print("Y: ");
  Serial.print(yValue);
  Serial.print(" Button: ");
  Serial.print(button);
  TimerSet(500);
  TimerOn();
}
