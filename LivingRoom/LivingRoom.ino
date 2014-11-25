/* LED Blink, Teensyduino Tutorial #1
   http://www.pjrc.com/teensy/tutorial.html
 
   This example code is in the public domain.
*/

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.0 has the LED on pin 13
const int ledPin = 13;
// the setup() method runs once, when the sketch starts

void setup() {
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
}

// the loop() methor runs over and over again,
// as long as the board has power

void loop() {
  digitalWrite(ledPin, HIGH);   // set the LED on
  
  if (digitalRead(7) == LOW) {
    digitalWrite(ledPin, LOW);    // set the LED off
  }
  
  if (digitalRead(8) == LOW) {
    digitalWrite(ledPin, LOW);    // set the LED off
  }
  
  
}

