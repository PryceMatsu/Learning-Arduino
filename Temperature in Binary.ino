//LED toggler (temperature input)
//toggles LEDs according to temperature inputted in binary

const int B[] = {2, 3, 4, 5};
int a = 0x00;
int a0, a1, a2, a3;
int A;

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

int convertToCelsius(int temp) {
  return (temp - 32.0) * 5.0/9.0;
}


void loop()
{
  Serial.print("Enter a temperature in fahrenheit to be converted to celsius:\n");
  while(Serial.available() == 0){}
  A = Serial.parseInt();

  while (Serial.available() != 0) {
    char x = Serial.read();
  }

  int celsius = convertToCelsius(A);
  Serial.println(celsius);
  writeToB(celsius); //This will display the value of a in binary on the LEDs

  while (Serial.available() == 0) { //makes it so you dont have to use the Delay() function
  }

  resetB();
}
