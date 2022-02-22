#include <Encoder.h>
int pwmPin1 = A4;
int pwmPin2 = A5;
int dirPin = A4;
int inputPin1 = A2;
int inputPin2 = A3;

Encoder motor(inputPin1, inputPin2);

int dirFlag = 0;
void setup() {
  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  pinMode(inputPin1, INPUT); 
  pinMode(inputPin2, INPUT);  
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

  int pos = motor.Read();
  Serial.print(pos);
  //delay(2000);

  /*
  if (dirFlag == 0) {
    dirFlag = 1;
  }
  else if (dirFlag == 1) {
    dirFlag = 0;
  }
  */
}
