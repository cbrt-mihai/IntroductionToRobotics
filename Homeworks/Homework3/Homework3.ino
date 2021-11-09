const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;

const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;

const int pinBuzz = 12;

#define NUM_READINGS 15

int senseLimit = 100;
int probePin = A5;
int val = 0;

int readings[NUM_READINGS];
int index = 0;
int total = 0;
int average = 0;

int updateTime = 40;

bool state = HIGH;

int digit = 0;

const int segSize = 8;
const int nrDigits = 10;

int segments[segSize] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP};

bool digitMatrix[nrDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT); 
  }

  for (int i = 0; i < NUM_READINGS; i++)
    readings[i] = 0;

  pinMode(probePin, INPUT);
  pinMode(pinBuzz, OUTPUT);
  
  Serial.begin(9600);
}

void displayNumber(byte digit, bool decimalPoint) {
  for(int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }

  digitalWrite(pinDP, decimalPoint);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(probePin);  // take a reading from the probe

  if(val >= 1){                // if the reading isn't zero, proceed
    val = constrain(val, 1, senseLimit);  // turn any reading higher than the senseLimit value into the senseLimit value
    val = map(val, 1, senseLimit, 1, 1023);  // remap the constrained value within a 1 to 1023 range

    total -= readings[index];               // subtract the last reading
    readings[index] = val; // read from the sensor
    total += readings[index];               // add the reading to the total
    index = (index + 1);                    // advance to the next index

    if (index >= NUM_READINGS)               // if we're at the end of the array...
      index = 0;                            // ...wrap around to the beginning

    average = total / NUM_READINGS;          // calculate the average

    if (average > 50){                // if the average is over 50 ...
      displayNumber(0, false);   // Show a 0
    }

    if (average > 150){               // and so on ...
      displayNumber(1, false);   // Show a 1

    }

    if (average > 250){
      displayNumber(2, false);   // Show a 2
 
    }

    if (average > 350){
      displayNumber(3, false);   // Show a 3
      tone(pinBuzz, 90, 30);
    }

    if (average > 450){
      displayNumber(4, false);   // Show a 4
      tone(pinBuzz, 90, 40);
    }

    if (average > 550){
      displayNumber(5, false);   // Show a 5
    }

    if (average > 650){
      displayNumber(6, false);   // Show a 6

    }

    if (average > 750){
      displayNumber(7, false);   // Show a 7
    }

    if (average > 850){
      displayNumber(8, false);   // Show a 8
    }

    if (average > 950){
      displayNumber(9, false);   // Show a 9
    }
    tone(pinBuzz, average, updateTime);
    Serial.println(average); // use output to aid in calibrating
    delay(updateTime);
  }
}
