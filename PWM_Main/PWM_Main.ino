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
float pwm_out = 0.0;



Encoder myEnc(inputPin1, inputPin2);

int dirFlag = 1;
void setup() {
  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  delay(3000);
}

void loop() {

  //Constants
  Kp = 0.2362;
  Ki = .01;
  Kd = 0.4157;
  Imax = 2;
  Dmax = 2;
  set_rpm = 60;
  set_pos = 180;
  Ts = 0.05;


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

  //rpm control pwm code
  //pwm = (int)(Kp * x_k - Kp * x_k1 + Ki * Ts * x_k1 + y_k1);
  
  //position control pwm code
  //pwm = (int)(208*x_k - 52.77*x_k1 - 3.004*x_k2 + 0.3004*y_k1);

  pwm  = (int)( (2*Imax*Dmax - Ts*(Ki*Dmax+Kd*Imax))*y_k1  -  (Ts*Ts*Ki*Kd+Imax*Dmax)*y_k2  +  ((Kp+Kd)*(Imax*Dmax))*x_k  -  (2*Imax*Dmax*(Kp+Kd)-Ts*(Imax*Dmax+Kd*Imax+Ki*Kd*Dmax+Ki*Imax*Dmax))*x_k1  +  ((Kp+Kd)*Imax*Dmax-Ts*(Imax*Dmax+Kd*Imax+Ki*Kd*Dmax+Ki*Imax*Dmax+Ts*Ts*Ki*Kd*(Imax + 1)))*x_k2  );
 
  x_k2 = x_k1;
  x_k1 = x_k; 
  y_k2 = y_k1; 
  y_k1 = y_k;

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
  else if (pwm < 0) {
    pwm_out = 0;
  }
  else {
    pwm_out = pwm;
  }

  
  Serial.print("pwm: ");
  Serial.println(pwm);
  analogWrite(dirPin, pwm_out);
  //Serial.print(rpm);
  Serial.print(pos);
  Serial.print(",");
  Serial.println(millis());
}
