//LED is off initially
//When button is pressed LED begins to flash (slow) until button is pressed again
//When button is pressed LED begins to flash (fast)
//When pressed again -> LED off
//requires timer library/header, linked in the repository as a .h file

#include "Timer.h"

enum STATE {INIT, FLASH, FLASH_FAST} gState = INIT;
char buttonPressed = 0;
char prevState = 0;

void tick(void) {
  
  // transitions
  switch (gState) {
    case INIT:
     if (buttonPressed == 1 && prevState == 0) { //if the value of the initial state is 0(off) and a button is pressed(1), go to next state.
       gState = FLASH;
     }
    break;
    
    case FLASH:
     if (buttonPressed == 1 && prevState == 0) { //if no button is pressed (0) and then a button is pressed (1), go next state (off).
      gState = FLASH_FAST;
    }
    break;

    case FLASH_FAST:
     if (buttonPressed == 1 && prevState == 0) {
      gState = INIT;
      }
    break;
  }
      
  
  // actions
  switch (gState) {
    case INIT:
        digitalWrite (2, LOW);
    break;

    case FLASH:
        if (digitalRead(2) == 0) {
            digitalWrite(2, HIGH);
            TimerSet(500);
        }
        else {
          digitalWrite(2, LOW);
          TimerSet(500);
        }
    break;
    case FLASH_FAST:
        if (digitalRead(2) == 0) {
            digitalWrite(2, HIGH);
            TimerSet(200);
        }
        else {
          digitalWrite(2, LOW);
          TimerSet(200);
        }
    break;
  }
}

void setup() {
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
  
  TimerSet(500);
  TimerOn();
  
  digitalWrite(2, LOW);
  
}

void loop()
{
  buttonPressed = digitalRead(13);
  tick();
  prevState = buttonPressed;
  while(!TimerFlag){}
  TimerFlag = 0;  

}
