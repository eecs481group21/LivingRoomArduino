#include <usb_keyboard.h>

int inPin = 12;        // the number of the input pin
int outPin = 13;       // the number of the output pin


int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

// analog inputs and constants
int inPinThree = A9;
int inPinTwo = A8;
int analogValue;
const int analogDelay = 10; // time between each analog read
const int numReads = 5;  // number of analog reads to calculate average from
const int minAnalogVal = 900; // any analog reading above minAnalogVal is considered HIGH



void setup()
{
  pinMode(inPin, INPUT_PULLUP);
  pinMode(outPin, OUTPUT);
  analogReference(DEFAULT);
}

void loop()
{
  reading = digitalRead(inPin);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == HIGH && previous == LOW && millis() - time > debounce) 
  {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();    
  }

  digitalWrite(outPin, state);

  previous = reading;

  // inPinThree: Analog //////////////////////////////////////
  for (int i = 0; i < numReads; i++ )
  {
    analogValue += analogRead(inPinThree);
    delay(analogDelay);
  }
  analogValue = analogValue/numReads;

  if(analogValue > minAnalogVal && state == HIGH)
  {
    usb_keyboard_press(KEY_A, 0);

    while(analogValue > minAnalogVal)
    {
      analogValue = 0;
      for (int i = 0; i < numReads; i++ )
      {
        analogValue += analogRead(inPinThree);
        delay(analogDelay);
      }
      analogValue = analogValue/numReads;
    }
  }
}

  // inPinTwo: Analog //////////////////////////////////////
  for (int i = 0; i < numReads; i++ )
  {
    analogValue += analogRead(inPinTwo);
    delay(analogDelay);
  }
  analogValue = analogValue/numReads;

  if(analogValue > minAnalogVal && state == HIGH)
  {
    usb_keyboard_press(KEY_B, 0);

    while(analogValue > minAnalogVal)
    {
      analogValue = 0;
      for (int i = 0; i < numReads; i++ )
      {
        analogValue += analogRead(inPinTwo);
        delay(analogDelay);
      }
      analogValue = analogValue/numReads;
    }
  }
}


