#include <usb_keyboard.h>

int inPin = 12;        // the number of the input pin
int inPinTwo = 11;     // the number of the second input pin
int outPin = 13;       // the number of the output pin

int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

void setup()
{
  pinMode(inPin, INPUT_PULLUP);
  pinMode(inPinTwo, INPUT_PULLUP);
  pinMode(outPin, OUTPUT);
}

void loop()
{
  reading = digitalRead(inPin);
  
  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();    
  }

  digitalWrite(outPin, state);

  previous = reading;
  
  if(digitalRead(inPinTwo) == LOW && state == HIGH){
    usb_keyboard_press(KEY_A, 0);
    while(digitalRead(inPinTwo) == LOW){
      delay(900);
       //chill in here while the button is pressed    
    }
  }
}

