const int dataPin = 12; // DS
const int latchPin = 11; // Storage Clock Pin
const int clockPin = 10; // Shift Register Clock Pin

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int pinX = A0;
const int pinY = A1;
const int pinSW = A2; 

#define BLINK_DELAY 750

int state = 0;
int digitCursor = 0;

int minThreshold = 100;
int maxThreshold = 900;

bool swState = LOW;
bool previousSWState = LOW;
bool joyMove = false;

bool resetBlink = true;
int blinkState = 1;

unsigned long interval = 0;

const int segmentDigits[] = {
  segD1, segD2, segD3, segD4
};


int digits[] = {
  8, 6, 4, 2
};

const int segmentsCount = 4;

int digitArray2[2][16] = {
  {
    B11111100, // 0
    B01100000, // 1
    B11011010, // 2
    B11110010, // 3
    B01100110, // 4
    B10110110, // 5
    B10111110, // 6
    B11100000, // 7
    B11111110, // 8
    B11110110, // 9
    B11101110, // A
    B00111110, // b
    B10011100, // C
    B01111010, // d
    B10011110, // E
    B10001110  // F
  },
  {
    B11111101, // 0
    B01100001, // 1
    B11011011, // 2
    B11110011, // 3
    B01100111, // 4
    B10110111, // 5
    B10111111, // 6
    B11100001, // 7
    B11111111, // 8
    B11110111, // 9
    B11101111, // A
    B00111111, // b
    B10011101, // C
    B01111011, // d
    B10011111, // E
    B10001111  // F
  } 
};

int digitArray[16] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};


void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  for (int i = 0; i < segmentsCount; i++) {
    pinMode(segmentDigits[i], OUTPUT);
    digitalWrite(segmentDigits[i], LOW); // to turn on
  }

  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinSW, INPUT_PULLUP);

  Serial.begin(9600);
  debug();
}

void loop() {
  int valueX = analogRead(pinX);
  int valueY = analogRead(pinY);
  bool valueSW = !digitalRead(pinSW);
  String initialString = "";

  if (state == 0) { // selecting the  display
    if(valueX <= minThreshold && joyMove == false) {
      debug();
      digitCursor++;
      joyMove = true;

      if(digitCursor > 3) {
        digitCursor = 0;
      }
    }

    if(valueX >= maxThreshold && joyMove == false) {
      debug();
      digitCursor--;
      joyMove = true;

      if(digitCursor < 0) {
        digitCursor = 3;
      }
    }

    if(minThreshold <= valueX && valueX <= maxThreshold) {
      joyMove = false;
       if(previousSWState != valueSW && valueSW == HIGH) {
        debug();
        state = 1 - state;
       }
    }
  }
  else { // selecting the digit
    if(valueY <= minThreshold && joyMove == false) {
      debug();
      digits[digitCursor]--;
      joyMove = true;

      if(digits[digitCursor] < 0) {
        digits[digitCursor] = 9;
      }
    }

    if(valueY >= maxThreshold && joyMove == false) {
      debug();
      digits[digitCursor]++;
      joyMove = true;

      if(digits[digitCursor] > 9) {
        digits[digitCursor] = 0;
      }
    }

    if(minThreshold <= valueY && valueY <= maxThreshold) {
      joyMove = false;

      if(previousSWState != valueSW && valueSW == HIGH) {
        debug();
        state = 1 - state;
        for (int i = 0; i < 4; i++) {
          initialString.concat(digits[i]);
        }
      }
    }
  
    
  }
  
  previousSWState = valueSW;  
 
  writeNumber();
}

void debug() {
  Serial.print(" state: ");
  Serial.print(state);
  Serial.println();
  Serial.print(" digits: ");
  Serial.print(digits[0]);
  Serial.print(digits[1]);
  Serial.print(digits[2]);
  Serial.print(digits[3]);
  Serial.println();
  Serial.print(" cursor: ");
  Serial.print(digitCursor);
  Serial.println();
}

void writeNumber() {
  int lastDigit;
  int displayDigit = 3;

  while(displayDigit >= 0) {
    lastDigit = String(digits[displayDigit]).toInt();

    
    
    if (state == 0 && displayDigit == digitCursor) {
      if (resetBlink) {
        resetBlink = false;
        interval = millis();
      }

      if(millis() - interval > BLINK_DELAY) {
        blinkState = 1 - blinkState;
        resetBlink = true;
      }
    }
    if (displayDigit != digitCursor) {
      blinkState = 0;
    }
    
    if (state == 1 && displayDigit == digitCursor) {
      blinkState = 1;
    }

    if (state == 1 && displayDigit != digitCursor) {
      blinkState = 0;
    }

    showDigit(displayDigit);
    writeReg(digitArray2[blinkState][lastDigit]);
    
    
    displayDigit--;
    delay(5);
  }
}

void showDigit(int digitNumber) {
  for (int i = 0; i < segmentsCount; i++) {
    digitalWrite(segmentDigits[i], HIGH);
  }

  digitalWrite(segmentDigits[digitNumber], LOW);
}

void writeReg(int digit) {
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, MSBFIRST, digit);  

  digitalWrite(latchPin, HIGH);
}
