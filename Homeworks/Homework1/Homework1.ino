const int ledPinRed = 11;
const int ledPinGreen = 10;
const int ledPinBlue = 9;

const int potPinRed = A0;
const int potPinGreen = A1;
const int potPinBlue = A2;

int potValueRed = 0;
int potValueGreen = 0;
int potValueBlue = 0;

int brightnessRed = 0;
int brightnessGreen = 0;
int brightnessBlue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);

  pinMode(potPinRed, INPUT);
  pinMode(potPinGreen, INPUT);
  pinMode(potPinBlue, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   potValueRed = analogRead(potPinRed);
   potValueGreen = analogRead(potPinGreen);
   potValueBlue = analogRead(potPinBlue);

   brightnessRed = map(potValueRed, 0, 1023, 0, 255);
   brightnessGreen = map(potValueGreen, 0, 1023, 0, 255);
   brightnessBlue = map(potValueBlue, 0, 1023, 0, 255);

   analogWrite(ledPinRed, brightnessRed);
   analogWrite(ledPinGreen, brightnessGreen);
   analogWrite(ledPinBlue, brightnessBlue);
}
