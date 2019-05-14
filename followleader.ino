// connect motor controller pins to Arduino digital pins
// motor one

#include <Wire.h>
#define uchar unsigned char
uchar t;
//void send_data(short a1,short b1,short c1,short d1,short e1,short f1);
uchar data[16];

int enA = 3;
int in1 = 9;
int in2 = 10;
// motor two
int enB = 4;
int in3 = 12;
int in4 = 11;

const int trigPin = 7;
const int echoPin = 6;

const int boundary = 60;

void setup()
{
  // set all the motor control pins to outputs
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  t = 0;
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void getdata(){
  Wire.requestFrom(9, 16);    // request 16 bytes from slave device #9

  while (Wire.available())   // slave may send less than requested
  {
    data[t] = Wire.read(); // receive a byte as character
    if (t < 15)
      t++;
    else
      t = 0;
  }

}

void drive(int a, int b){
  if(a < 0){
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else{
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  if(b < 0){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else{
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }

  analogWrite(enA, abs(b));
  analogWrite(enB, abs(a));

}

void follow(int duration){

  duration = min(duration, 160);
  duration = max(duration, 80);

  double d = (double)duration - 80;
  d /= 80;

  if(data[14] < boundary || data[12] < boundary || data[10] < boundary || data[8] < boundary || data[6] < boundary || data[4] < boundary ){
    drive((int)(60 * d), (int)(90 * d));
    Serial.print("Left");
  }
  else{
    Serial.print("Forward");
    drive((int)(130*d), (int)(80*d));
  }

  if(data[14] < boundary && data[12] < boundary && data[10] < boundary  && data[8] < boundary && data[6] < boundary && data[4] < boundary && data[2] < boundary){
    Serial.print("Stopped");
    drive(0,0);
  }
}

long duration;
int distance;

void loop()
{

  getdata();
  for(int i = 0; i < 15; i += 2){
    Serial.print(data[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  //distance= duration*0.034/2;

  // Prints the distance on the Serial Monitor
  //Serial.print("Duration: ");
  Serial.println(duration);

  follow(duration);


}
