//When initialized middle LED starts on
//Utilize the Joystick to cycle through LEDs
//has directionality
//clicking the joystick toggles LED on/off

#include "Timer.h"

const int ledPin[] = {7, 6, 5, 4, 3};
int currentState = 2; // Start with the middle LED on
bool ledIsOn = true;
int prevButtonState = HIGH;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(ledPin[i], OUTPUT);
    }
  pinMode(2, INPUT_PULLUP); 
  digitalWrite(ledPin[currentState], HIGH); 
  TimerSet(500); 
  TimerOn(); 

  Serial.begin(9600);
}

void resetledPin() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin[i], LOW);
    }
}

void tick(void) {
  enum STATES { NONE, LEFT, RIGHT, BUTTON_PRESS } gState = NONE;
  int buttonState = digitalRead(2);
  int xAxisPos = analogRead(A0);

  // Transitions switch case
  switch (gState) {
    case NONE:
      if (buttonState == LOW && prevButtonState == HIGH) {
        gState = BUTTON_PRESS;
        }
      else if (xAxisPos < 250) {
        gState = LEFT;
        }
      else if (xAxisPos > 900) {
        gState = RIGHT;
        }
      break;
    case LEFT:
      break;

    case RIGHT:
      break;

    case BUTTON_PRESS:
      gState = NONE;
      break;
      }

  prevButtonState = buttonState;

  // Actions
  switch (gState) {
    case NONE:
    break;

    case LEFT:
      if (currentState > 0) {
        currentState--;
        }
      break;

    case RIGHT:
      if (currentState < 4) {
        currentState++;
        }
      break;

    case BUTTON_PRESS:
      ledIsOn = !ledIsOn; // Toggle the LED state
      break;
    }

  resetledPin(); // Reset LED pins before setting the new state

  if (ledIsOn) {
    digitalWrite(ledPin[currentState], HIGH);
    }
}

void loop() {
  while(!TimerFlag) {}
  TimerFlag = 0;
  tick();
}
