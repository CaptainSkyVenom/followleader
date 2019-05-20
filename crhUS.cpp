#include "Arduino.h"
#include "crhUS.h"


crhUS::crhUS(int trigPin, int echoPin){
  // setup right motor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  tP = trigPin;
  eP = echoPin;
}

int crhUS::ping(){
  digitalWrite(tP, LOW);
  delayMicroseconds(2);
  digitalWrite(tP, HIGH);
  delayMicroseconds(10);
  digitalWrite(tP, LOW);
  return pulseIn(eP, HIGH);
}
