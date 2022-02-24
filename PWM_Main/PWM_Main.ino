#include <Encoder.h>
int pwmPin1 = A4;
int pwmPin2 = A5;
int dirPin = A4;
int inputPin1 = A2;
int inputPin2 = A3;
float pos = 0.0;
float rpm = 0.0;
int ms = 0;

Encoder myEnc(inputPin1, inputPin2);

int dirFlag = 0;
void setup() {
  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  delay(3000);
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

  

  pos = myEnc.read() * (360)/(4.4*48);
  Serial.print("degrees: ");
  Serial.println(pos);

  ms = millis();
  while(ms<(ms+50)) {
//    ms = millis();
    Serial.println(ms);
    rpm = myEnc.read();
  }
  rpm = myEnc.read() * (360*1000*60)/(4.4*48*50);
  Serial.print("rpm: ");
  Serial.println(rpm);

  rpm = 0;
  ms = 0;
  
  if (pos < 720) {
    analogWrite(dirPin, 50);
  }
  else {
    analogWrite(dirPin, 0);
  }
  

  /*
  if (dirFlag == 0) {
    dirFlag = 1;
  }
  else if (dirFlag == 1) {
    dirFlag = 0;
  }
  */
}
