
int pwmPin1 = A4;
int pwmPin2 = A5;
int dirPin = A4;
int inputPin = A3;
int dirFlag = 0;
void setup() {
  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  pinMode(inputPin, INPUT);   
}

void loop() {
  if (dirFlag == 0) {
    analogWrite(pwmPin1, 0);
    dirPin = A5;
  }
  else {
    analogWrite(pwmPin2, 0);
    dirPin = A4;
  }

  analogWrite(dirPin, 128);
}
