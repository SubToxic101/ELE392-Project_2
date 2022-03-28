#include <Encoder.h>
int pwmPin1 = A4;
int pwmPin2 = A5;
int dirPin = A4;
int inputPin1 = A2;
int inputPin2 = A3;
float rpm = 0.0;
float pos = 0.0;
float rpm_counter = 0.0;
float rpm_start = 0.0;
float set_rpm = 0.0;
float set_pos = 0.0;
int ms = 0;
int ms_end = 0;
float Kp = 0.0;
float Ki = 0.0;
float Kd = 0.0;
float Imax = 0.0;
float Dmax = 0.0;
float Ts = 0.0;
float y_k = 0.0;
float y_k1 = 0.0;
float y_k2 = 0.0;
float x_k = 0.0;
float x_k1 = 0.0;
float x_k2 = 0.0;
float pwm = 0.0;
float pwm1 = 0.0;
int pwm_count = 0;
float pwm_out = 0.0;
float fix_error = 0.0;
float fix_error1 = 0.0;
int fix_error_count = 0;
int testset = 0.0;



Encoder myEnc(inputPin1, inputPin2);

int dirFlag = 1;
void setup() {
  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  delay(3000);
}

void loop() {

  //Assorted Constants
  Kp = 0.2362;
  Ki = .02983;
  Kd = 0.4157;
  Imax = 2;
  Dmax = 2;
  set_rpm = 60;
  Ts = 0.05;

  //Real-Time input handling
  if (Serial.available() > 0) {
    testset = Serial.parseInt();
    Serial.println(testset);
    set_pos = testset;
  }

  //RPM + position calculation section
  rpm = 0;
  rpm_start = myEnc.read();
  ms = millis();
  ms_end = ms + 50;
  while (ms < ms_end) {
    //Serial.println("while called");
    rpm_counter = myEnc.read();
    ms = millis();
  }
  rpm = (rpm_counter - rpm_start) * (1000 * 60) / (4.4 * 48 * 50);
  pos = myEnc.read() * (360)/(4.4*48);

  //PID control equation section
  //rpm setpoint
  //x_k = set_rpm - rpm;
  //position setpoint
  x_k = set_pos - pos;
  //Error-fixer input
  fix_error = set_pos - pos;

  //rpm control pwm equation
  //pwm = (int)(Kp * x_k - Kp * x_k1 + Ki * Ts * x_k1 + y_k1);
  
  //position control pwm equation
  pwm = (int)(0.652*x_k - 1.188*x_k1 + 0.5478*x_k2 + 1.762*y_k1 - 0.7668*y_k2);
  x_k2 = x_k1;
  x_k1 = x_k; 
  y_k2 = y_k1; 
  y_k1 = pwm;

  //determine direction of pwm to set dirFlag
  if (pwm < 0) {
    dirFlag = 0;
    pwm = abs(pwm);
  }
  else if (pwm > 0) {
    dirFlag = 1;
    pwm = abs(pwm);
  }

  //set correct pin output based on dirFlag
  if (dirFlag == 0) {
    analogWrite(pwmPin1, 0);
    dirPin = A5;
  }
  else {
    analogWrite(pwmPin2, 0);
    dirPin = A4;
  }

  //cap the pwm output
  if (pwm > 255) {
    pwm_out = 255;
  }
  else if (pwm < 30) {
    pwm_out = 0;
  }
  else {
    pwm_out = pwm;
  }
  
  Serial.print("pwm: ");
  Serial.println(pwm);
  analogWrite(dirPin, pwm_out);

  //Error-Fixer section
  if (abs(fix_error) > 3) {
    if (fix_error1 == fix_error) {
      fix_error_count++;
    }
  }
  fix_error1 = fix_error;

  if (fix_error_count > 3) {
     if (abs(fix_error) > 40) {
        analogWrite(dirPin, 100);
     }
     else{
     analogWrite(dirPin, 50);
     }
     fix_error_count = 0;
  }
  
  Serial.print(pos);
  Serial.print(",");
  Serial.println(millis());
}
