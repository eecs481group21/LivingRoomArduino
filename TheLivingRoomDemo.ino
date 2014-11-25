//#include <Keyboard.h>

int inPinSignal = 2;
int inPinKeyboard = 3;
int outPinSignal = 13;
int outPinKeyboard = 12;

int stateSignal = HIGH;      // the current state of the output pin
int readingSignal;           // the current reading from the input pin
int previousSignal = LOW;    // the previous reading from the input pin

int stateKeyboard = HIGH;
int readingKeyboard;
int previousKeyboard = LOW;

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
time_t timeSignal = 0;         // the last time the output pin was toggled
time_t timeKeyboard = 0;

long debounce = 200;   // the debounce time, increase if the output flickers

void setup()
{
  pinMode(inPinSignal, INPUT);
  pinMode(outPinSignal, OUTPUT);
}

void loop()
{
  readingSignal = digitalRead(inPinSignal);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (readingSignal == HIGH) {
      digitalWrite(outPinSignal, LOW);
  }
  else {
      digitalWrite(outPinSignal, HIGH);
      if (stateKeyboard == HIGH) {
          Serial.print('a');
      }
  }

  previousSignal = readingSignal;
  
  readingKeyboard = digitalRead(inPinKeyboard);
  
  if (readingKeyboard == HIGH && previousKeyboard == LOW && millis() - timeKeyboard > debounce) {
    if (stateKeyboard == HIGH)
      stateKeyboard = LOW;
    else
      stateKeyboard = HIGH;

    timeKeyboard = millis();    
  }

  digitalWrite(outPinKeyboard, stateKeyboard);

  previousKeyboard = readingKeyboard;
}
