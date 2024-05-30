//Utilizes a potentiometer to toggle lights.
//Use analog input to map and signal LEDs to light up as potentiometer is turned.

const int B[] = {2, 3, 4, 5};

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
    if (temp > 3) { digitalWrite(B[3],HIGH); }
    if (temp > 2) { digitalWrite(B[2],HIGH); }
    if (temp > 1) { digitalWrite(B[1],HIGH); }
    if (temp > 0) { digitalWrite(B[0],HIGH); }
}

/*unsigned char reverse(unsigned char temp) {
    unsigned char value = 0; //0x0000

    // check if bit 3 is set, set bit 0 if so (using XOR)
    if ((temp >> 3) & 0x01){ }
  //1101 -> 0001 & 0001 = 0001 (true) -> value = value(0000) ^ 0001 = 0001
    
    if ((temp >> 2) & 0x01){ value ^= (1 << 1);}
    
    if ((temp >> 1) & 0x01){ value ^= (1 << 2); }
 
    if (temp & 0x01){ value ^= (1 << 3); }

    return value;00000000000
}*/

void loop()
{
  int potentiometer = analogRead(A0); //Reads the value in the potentiometer
  int ledValue = 4 - map(potentiometer, 0, 1023, 0, 4); //flips the ledValue in the potentiometer so that it lights up when turned clockwise
  writeToB(ledValue);
  
  Serial.print("LED value: ");
  Serial.print(ledValue);
  Serial.print("\n");
  delay(200);
  resetB();
  
}
