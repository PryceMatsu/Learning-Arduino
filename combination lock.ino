//Mimics a combination lock
//When all three buttons are pressed in the right sequence, LED toggles (ON/OFF)
//If pressed in sequence 1,1,1,1,1,2,3 (toggles LED) still as only last three numbers are considered

enum STATE {INIT, X, Y, Z} gState = INIT;
char buttonPressedX = 0;
char buttonPressedY = 0;
char buttonPressedZ = 0;
char prevStateX = 0;
char prevStateY = 0;
char prevStateZ = 0;

bool unlocked = false;


void tick(void) {
  
  // transitions
  switch (gState) {
    case INIT:
        if (buttonPressedX == 1 && prevStateX == 0) { 
          gState = X;
        }
    break;
    
    case X:
        if (buttonPressedY == 1 && prevStateY == 0) { 
              gState = Y;
               }
        else if(buttonPressedZ == 1 && prevStateZ == 0) {
              gState = INIT;
              }
    break;
    
    case Y:
        if(buttonPressedZ == 1 && prevStateZ == 0) {
            gState = Z;
        }
        else if((buttonPressedX == 1 && prevStateX == 0)||(buttonPressedY == 1 && prevStateY == 0)) {
          gState = INIT;
        }
    break;
    
    case Z:
        unlocked = !unlocked; //if case Z is reached, bool unlock sets to true meaning the combination is unlocked turning the LED on 
        gState = INIT;
        break;
  }
  // actions
    if (unlocked == true) {
      digitalWrite(2, HIGH);
    }
    else {
      digitalWrite(2, LOW);
    }
        
}

void setup() {
  pinMode(13, INPUT); //All three button inputs
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(2, OUTPUT);
  
  digitalWrite(2, LOW);

  Serial.begin(9600);
}

void loop()
{
  buttonPressedX = digitalRead(13);
  buttonPressedY = digitalRead(12);
  buttonPressedZ = digitalRead(11);
  tick();
  prevStateX = buttonPressedX;
  prevStateY = buttonPressedY;
  prevStateZ = buttonPressedZ;
  //delay(100);
}
