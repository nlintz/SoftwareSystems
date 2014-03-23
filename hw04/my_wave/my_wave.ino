/*

 Author: Nathan Lintz 
 Arduino Synthesizer for Software Systems 2013

 */

// Buttons used for inputs to synthesizer
const int buttonPin1 = 3;
const int buttonPin2 = 2;

// Constants used to generate sawtooth waves
const int low = 36;
const int high = 255;
const int stride = 5;

/*
Setup code - Initializes pins and interrupts

*/
void setup() {
  cli(); // Clear Interrupts
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0  = 0;
  OCR0A = 20;
  TCCR0A |= (1 << WGM01);
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  TIMSK0 |= (1 << OCIE0A);

  attachInterrupt(1, playSound, FALLING);
  attachInterrupt(0, changeSound, FALLING);

  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP);  

  int pin;
  for (pin=6; pin<= 13; pin++)
  {
    pinMode(pin, OUTPUT);
  }
  sei();

}

/* 
Takes an integer and generates the binary representation of it in an array

int table[] - array that the user passes to fill with binary digits
int x - the decimal number the user wants to put into the array
*/
void bitTable(int table[], int x)
{
  int i;
  for (i=0; i<8; i++){
    table[i] = (x & (1 << i)) ? 1 : 0;
  }
}

/*
Incremenets the stride and returns the integer representing the current amplitude of the sawtooth wave

*/
int getByte()
{
  static int waveIndex = low;
  waveIndex += stride;
  if (waveIndex > high)
  {
    waveIndex = low;
  }
  return waveIndex;
}

/*
Returns the value that should be written to portD, this function flips the binary since our R2R ladder's bits are flipped

PortD is the port which corresponds to pins 1-7

int table[] - the binary table that the user wants to write to portD

*/
int getPortD(int table[])
{
  int i;
  int total = 0;
  total += table[7] << 6;
  total += table[6] << 7;
  total+= (1 << buttonPin1); // We don't want to accidentally overwrite the input buttons
  total+= (1 << buttonPin2); // We don't want to accidentally overwrite the input button
  return total;
}

/*
Returns the value that should be written to portB, this function flips the binary since our R2R ladder's bits are flipped

PortB is the port which corresponds to pins 8-13

int table[] - the binary table that the user wants to write to portD

*/
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

/* Writes an integer to portD and portB one byte at a time

int x - integer to be written to the ports

*/
void writeByte(int x) {
  int table[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  bitTable(table, x);
  int d = getPortD(table);
  int b = getPortB(table);
  PORTD = d;
  PORTB = b;
}

/*
No loop needed...swag
*/
void loop() {
}

/*
ISR for when the user presses the play button, sets the play flag to true if they are holding it
*/
volatile int play = false; // Boolean which sets whether or not the arduino should be playing
void playSound()
{
  play = true;
  detachInterrupt(1); // Reassign the interrupt from falling to rising so it only triggers when the user is holding the button
  attachInterrupt(1, stopSound, RISING);
}

/*
If the user is not pressing the playSound button, this method detaches the interrupts and resets it to listen for FALLING edges again
*/
void stopSound()
{
  play = false;
  detachInterrupt(1);
  attachInterrupt(1, playSound, FALLING);
}


/*
ISR for when the user presses the change sound button
The OCR0A is a register which controls the period of the timer for Timer0
*/
void changeSound()
{
  static int rising = 1;
  if (rising)
  {
    OCR0A += 10;
  } else
  {
    OCR0A -=  10;
  }

  if ((OCR0A >= 100) || (OCR0A <= 20))
  {
    rising = !rising;
  }
  detachInterrupt(0);
  attachInterrupt(0, soundChanged, RISING);
}

/* 
If the user is not pressing the changeSound button, this method detaches the interrupts and resets it to listen for FALLING edges again
*/
void soundChanged()
{
  detachInterrupt(0);
  attachInterrupt(0, changeSound, FALLING);
}

/*
ISR for internal timer which plays the triangle wave. If the play flag is set to true, the next byte of the triangle wave is played
*/
ISR(TIMER0_COMPA_vect){
  if (play)
  {
    writeByte(getByte());
  }
}


  
