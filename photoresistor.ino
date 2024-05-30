//If the amount of light the photoresistor receives is < 20 for 5 or more seconds, LED is on. (Dark in room)
//If the amount of light the photoresistor receives is > 100, LED turns off. (light)
//If between 20 and 100 light stays in whichever state it was in.

#include "Timer.h"

enum STATE { OFF, TURNING_ON, ON} gState = OFF;
// photoVal <20 = dark ; 100 >  =light
int photoVal;
// how long we've been in the dark, checked every 100 milisecond.
unsigned long dark = 0;

void tick(void)
{
    // transitions
    switch (gState)
    {
    case OFF:
    case TURNING_ON:
        digitalWrite(9, LOW);
        break;
    case ON:
        digitalWrite(9, HIGH);
        break;
    }

    // actions
    switch (gState)
    {
    case OFF:
        // no light (value under 20, specific to my room)
        if (photoVal < 20) {   //if (!photoVal) would use with maps() if not for demo.
            gState = TURNING_ON;
        }
        break;

    case TURNING_ON:
        if (photoVal < 20)  //if (!photoVal) would use if not for demo.
        {
            ++dark; //++1 = 100ms, dark = 1 = 100ms
        }
        // if any light value is detected, kick back to "off"
        else
        {
            dark = 0;
            gState = OFF;
        }

        //dark = 5000ms = 5 seconds, turn on
        if (dark >= 50) { 
            dark = 0;
            gState = ON;
        }
        break;
    case ON:
        // instantly turn it off  
        if (photoVal > 100) { //if (photoVal > 1), for maps function
             gState = OFF;
        }
        break;
    }
}

void setup()
{
    pinMode(A0, INPUT);
    pinMode(9, OUTPUT);

    TimerSet(100);
    TimerOn();

    Serial.begin(9600);
}

void loop()
{
    //photoVal = map(analogRead(A0), 0, 1023, 0, 15); //could use maps function, to do this more generally. Dont know if that is allowed as the slides specified to use analogRead(pin).
    photoVal = analogRead(A0); //specific light values in my room just for demo
    tick();
  //Serial.println(photoVal);
    while (!TimerFlag) {}
    TimerFlag = 0;
}
