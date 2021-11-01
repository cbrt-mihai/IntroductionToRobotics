const int carGreenPin = 13;
const int carYellowPin = 12;
const int carRedPin = 8;

const int buzzerPin = 6;

const int humGreenPin = 4;
const int humRedPin = 3;

const int buttonPin = 2;

// -------

#define SEC_10 10000
#define SEC_5 5000
#define SEC_3 3000
#define SLOW_GREEN 500
#define FAST_GREEN 250

// -------

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

bool buttonState = LOW;
bool ledState = LOW;
bool reading = LOW;
bool previousReading = LOW;
bool previousButtonState = HIGH;

// -------

bool humGreenState = HIGH;

int state = 1;
unsigned long countup = 0;
unsigned long interval = 0;

bool done = false;
bool reset = true;
bool buttonPressed = false;

// -------

void setup() {
  // put your setup code here, to run once:
  pinMode(carGreenPin, OUTPUT);
  pinMode(carYellowPin, OUTPUT);
  pinMode(carRedPin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  pinMode(humGreenPin, OUTPUT);
  pinMode(humRedPin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Entering state 1");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(state == 1) {
    //Serial.println("Entered state 1");
    digitalWrite(carGreenPin, HIGH);
    digitalWrite(carRedPin, LOW);
    digitalWrite(carYellowPin, LOW);
    digitalWrite(humGreenPin, LOW); 
    digitalWrite(humRedPin, HIGH);
    
    reading = !digitalRead(buttonPin);

    if(reading != previousReading){
      lastDebounceTime = millis();
    }
  
    if(millis()-lastDebounceTime > debounceDelay) {
      if(reading != buttonState) {
        buttonState = reading;
        if(buttonState == HIGH) {
          ledState = !ledState;

          lastDebounceTime = 0;

          Serial.println("Button pressed");
          buttonPressed = true;
          countup = millis();
        }
      }
    }

    if(millis() - countup > SEC_10 && buttonPressed) {
      digitalWrite(carGreenPin, LOW);
      digitalWrite(carRedPin, LOW);
      digitalWrite(carYellowPin, LOW);
      digitalWrite(humGreenPin, LOW); 
      digitalWrite(humRedPin, LOW);
      state = 2;
      countup = 0;
      buttonPressed = false;
      Serial.println("Exiting state 1");
    }

    previousReading = reading;
  }
  else if(state == 2) {
    //Serial.println("Entered state 2");
    digitalWrite(carGreenPin, LOW);
    digitalWrite(carRedPin, LOW);
    digitalWrite(carYellowPin, HIGH);
    digitalWrite(humGreenPin, LOW); 
    digitalWrite(humRedPin, HIGH);

    if(!done) {
      countup = millis();
      done = true;
    }

    if(millis() - countup > SEC_3) {
      digitalWrite(carGreenPin, LOW);
      digitalWrite(carRedPin, LOW);
      digitalWrite(carYellowPin, LOW);
      digitalWrite(humGreenPin, LOW); 
      digitalWrite(humRedPin, LOW);
      state = 3;
      done = false;
      countup = 0;
      Serial.println("Exiting state 2");
    }
  }
  else if(state == 3) {
    //Serial.println("Entered state 3");
    digitalWrite(carGreenPin, LOW);
    digitalWrite(carRedPin, HIGH);
    digitalWrite(carYellowPin, LOW);
    digitalWrite(humGreenPin, HIGH); 
    digitalWrite(humRedPin, LOW);

    if(!done) {
      countup = millis();
      done = true;
    }

    if(reset) {
      interval = millis();
      reset = false;
    }

    if(millis() - interval > SLOW_GREEN) {
      tone(buzzerPin, 90, 200);
      reset = true;
    }

    if(millis() - countup > SEC_10) {
      digitalWrite(carGreenPin, LOW);
      digitalWrite(carRedPin, LOW);
      digitalWrite(carYellowPin, LOW);
      digitalWrite(humGreenPin, LOW); 
      digitalWrite(humRedPin, LOW);
      state = 4;
      done = false;
      interval = 0;
      countup = 0;
      Serial.println("Exiting state 3");
    }
  }
  else if(state == 4) {
    //Serial.println("Entered state 4");
    if(!done) {
      digitalWrite(carGreenPin, LOW);
      digitalWrite(carRedPin, HIGH);
      digitalWrite(carYellowPin, LOW);
      digitalWrite(humGreenPin, HIGH); 
      digitalWrite(humRedPin, LOW);
      
      countup = millis();
      done = true;
    }

    if(reset) {
      interval = millis();
      reset = false;
    }

    if(millis() - interval > FAST_GREEN) {
      tone(buzzerPin, 94, 100);
      digitalWrite(humGreenPin, !humGreenState);
      humGreenState = !humGreenState;
      reset = true;
    }

    if(millis() - countup > SEC_5) {
      digitalWrite(carGreenPin, LOW);
      digitalWrite(carRedPin, LOW);
      digitalWrite(carYellowPin, LOW);
      digitalWrite(humGreenPin, LOW); 
      digitalWrite(humRedPin, LOW);
      state = 1;
      done = false;
      countup = 0;
      lightInterval = 0;
      interval = 0;
      Serial.println("Exiting state 4");
    }
  }
}
