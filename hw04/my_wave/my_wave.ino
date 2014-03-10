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
  attachInterrupt(0, playSound, FALLING);

  pinMode(ledPin, OUTPUT);

  int pin;
  for (pin=6; pin<= 13; pin++)
  {
    pinMode(pin, OUTPUT);
  }
}

void bitTable(int table[], int x)
{
  int i;
  for (i=0; i<8; i++){
    table[i] = (x & (1 << i)) ? 1 : 0;
  }
}

int getPortD(int table[])
{
  int i;
  int total = 0;
  total += table[7] << 6;
  total += table[6] << 7;
  total+= (1 << buttonPin1);
  return total;
}

int getPortB(int bitTable[])
{
  int i;
  int total = 0;
  total += bitTable[0] << 5;
  total += bitTable[1] << 4;
  total += bitTable[2] << 3;
  total += bitTable[3] << 2;
  total += bitTable[4] << 1;
  total += bitTable[5];
  return total;
}

void writeByte(int x) {
  
  int table[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  bitTable(table, x);
  int d = getPortD(table);
  int b = getPortB(table);
  PORTD = d;
  PORTB = b;
}

int low = 36;
int high = 255;
int stride = 5;
int counter = low;
int play = true;

void loop() {
//  int button1 = digitalRead(buttonPin1);
//  if (button1) return;

  counter += stride;
  if (counter > high) {
    counter = low;
  }
  
  if play
    writeByte(counter);
}

void playSound()
{
  static unsigned long last_millis = 0;
  unsigned long m = millis();
  if (m - last_millis > 200) { //Debounce the Interrupt
    Serial.println("trigger sound");
    play = !play;
    last_millis = m;
  }
}

