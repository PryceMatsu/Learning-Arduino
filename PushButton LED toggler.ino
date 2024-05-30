//LED is off initially, once button is pushed LED lights up and stays on -> button pushed again, LED turns off.

enum STATE {INIT, NEXT_STATE} gState = INIT;
char buttonPressed = 0;
char prevState = 0;

void tick(void) {
  
  // transitions
  switch (gState) {
    case INIT:
      if (buttonPressed == 1 && prevState == 0) { //if the value of the initial state is 0(off) and a button is pressed(1), go to next state.
        gState = NEXT_STATE;
        }
      break;
    
    case NEXT_STATE:
      if (buttonPressed == 1 && prevState == 0) { //if no button is pressed (0) and then a button is pressed (1), go next state (off).
        gState = INIT;
        }
      break;
  }
  
  // actions
  switch (gState) {
    case INIT:
      digitalWrite (2, LOW);
      break;

    case NEXT_STATE:
      digitalWrite(2, HIGH);
      break;
  }
}

void setup() {
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
  
  digitalWrite(2, LOW);
}

void loop()
{
  buttonPressed = digitalRead(13);
  tick();
  prevState = buttonPressed;
  delay(100);
}
