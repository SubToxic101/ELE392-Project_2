#include <Encoder.h>
int pwmPin1 = A4;
int pwmPin2 = A5;
int dirPin = A4;
int inputPin1 = A2;
int inputPin2 = A3;
float pos = 0.0;
float rpm = 0.0;
float rpm_counter = 0.0;
float rpm_start = 0.0;
int ms = 0;
int ms_end = 0;

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
  //Serial.print("degrees: ");
  //Serial.println(pos);

  rpm = 0;
  rpm_start = myEnc.read();
  ms = millis();
  ms_end = ms+50;
  while(ms<ms_end) {
    rpm_counter = myEnc.read();
    ms = millis();
    
    /*Serial.print("rpmcounter: ");
    Serial.println(rpm_counter);
    Serial.print("ms: ");
    Serial.println(ms);
    */
  }
  rpm = (rpm_counter-rpm_start) * (1000*60)/(4.4*48*50);
  //Serial.print("rpm: ");
  //Serial.println(rpm);
  
  if (pos < 720) {
    analogWrite(dirPin, 255);
  }
  else {
    analogWrite(dirPin, 0);
  }

  Serial.print(rpm);
  Serial.print(",");
  Serial.println(millis());
  
  
  

  /*
  if (dirFlag == 0) {
    dirFlag = 1;
  }
  else if (dirFlag == 1) {
    dirFlag = 0;
  }
  */
}
