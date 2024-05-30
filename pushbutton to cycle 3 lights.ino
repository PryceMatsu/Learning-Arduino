//Initially starts with red LED on, when button is pressed -> cycle to green LED (toggle on)
//when button is pressed -> cycle to yellow LED (toggle on), button pressed cycle to red and so on...

enum STATE {RED, GREEN, YELLOW} gState = RED;
char buttonPressed = 0;
char prevState = 0;

void tick(void) {
  
  // transitions
  switch (gState) {
    case RED:
        if (buttonPressed == 1 && prevState == 0) { 
          gState = GREEN;
        }
        break;
    
    case GREEN:
      if (buttonPressed == 1 && prevState == 0) {  
        gState = YELLOW;
        }
      break;
    
    case YELLOW:
      if(buttonPressed == 1 && prevState == 0) {
        gState = RED;
        }
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
  
  digitalWrite(2, HIGH);
  gState = RED;

  Serial.begin(9600);
}

void loop()
{
  buttonPressed = digitalRead(13);
  tick();
  prevState = buttonPressed;
  //delay(100);
}
