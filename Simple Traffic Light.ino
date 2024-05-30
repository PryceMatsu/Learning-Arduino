//Simple Traffic Light
//Begins initially with red LED on
//When button is pressed state transitions to green LED and remains there for 10 seconds
//The state then transitions to yellow LED for 5 seconds before transitioning back to red

#include "Timer.h"

enum STATE {RED, GREEN, YELLOW} gState = RED;
char buttonPressed = 0;
unsigned long greenTimer = 10000;
unsigned long yellowTimer = 5000;

void tick(void) {
  // transitions
  switch (gState) {
    case RED:
        if (buttonPressed == 1) { 
          gState = GREEN;
          TimerSet(greenTimer);
        }
    break;

    case GREEN:
     gState = YELLOW;
     TimerSet(yellowTimer);
    
    break;

    case YELLOW:
    gState = RED;
    TimerSet(1);
    break;
  }

  // actions
  switch (gState) {
    case RED:
        digitalWrite (2, HIGH);
        digitalWrite (3, LOW);
        digitalWrite (4, LOW);
        break;

    case GREEN:
        digitalWrite (2, LOW);
        digitalWrite (3, LOW);
        digitalWrite (4, HIGH);
    break;

    case YELLOW:
        digitalWrite (2, LOW);
        digitalWrite (3, HIGH);
        digitalWrite (4, LOW);
    break;
  }
}

void setup() {
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  TimerSet(100);
  TimerOn();

  Serial.begin(9600);
}

void loop()
{
  buttonPressed = digitalRead(13);
  tick();
  while(!TimerFlag) {}
  TimerFlag = 0;
}
