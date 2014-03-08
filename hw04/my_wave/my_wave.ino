/*
  
 
 Author: Nathan Lintz 
 Arduino Synthesizer for Software Systems 2013
 
 */


const int ledPin = 5;       // select the pin for the LED
const int buttonPin1 = 2;
const int buttonPin2 = 3;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP);  

  pinMode(ledPin, OUTPUT);

  int pin;
  for (pin=6; pin<= 13; pin++)
  {
    pinMode(pin, OUTPUT);
  }
}

void writeByte(int x) {
  int pin;
  for (pin=13; pin>=6; pin--) {
    digitalWrite(pin, x&1);
    x >>= 1;
  }
}

int low = 36;
int high = 255;
int stride = 5;
int counter = low;

void loop() {
  int button1 = digitalRead(buttonPin1);
  if (button1) return;

  counter += stride;
  if (counter > high) {
    counter = low;
  }

  // write to the digital pins  
  writeByte(counter);
}

