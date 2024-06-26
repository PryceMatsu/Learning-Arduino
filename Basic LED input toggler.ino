//Arduino LED toggler (based on temperature input)

const int B[] = {2, 3, 4, 5};
int a = 0x00;
int a0, a1, a2, a3;

void setup()
{
  pinMode(B[0], OUTPUT);
  pinMode(B[1], OUTPUT);
  pinMode(B[2], OUTPUT);
  pinMode(B[3], OUTPUT);
  Serial.begin(9600);
}

void resetB()
{
  digitalWrite(B[3],LOW);
  digitalWrite(B[2],LOW);
  digitalWrite(B[1],LOW);
  digitalWrite(B[0],LOW);
}

void writeToB(unsigned char temp)
{
 
  if ((temp>>3) & 0x01){digitalWrite(B[3],HIGH);}
  if ((temp>>2) & 0x01){digitalWrite(B[2],HIGH);}
  if ((temp>>1) & 0x01){digitalWrite(B[1],HIGH);}
  if (temp & 0x01){digitalWrite(B[0],HIGH);}
}


void loop()
{
  Serial.print("Enter a temperature in fahrenheit:\n");
  while(Serial.available() == 0){}
  a = Serial.parseInt();

  while (Serial.available() != 0) { //fixes the double input issue from the Serial.print prompt and input.
    char x = Serial.read();
  }
  
  writeToB(a); //This will display the value of a in binary on the LEDs
  Serial.println(a);
  resetB();
  //delay(200);
  
  if (a > 95) {
    digitalWrite (B[2], HIGH);
    digitalWrite (B[1], LOW);
    digitalWrite (B[0], LOW);
  }
  else if (a <= 95 && a >= 65) {
    digitalWrite (B[2], LOW);
    digitalWrite (B[1], HIGH);
    digitalWrite (B[0], LOW);
  }
  else {
    digitalWrite (B[2], LOW);
    digitalWrite (B[1], LOW);
    digitalWrite (B[0], HIGH);
  }
}
