#include<Servo.h>
#include <SoftwareSerial.h>

long duration;
int distance;
int x = 0, y = 0, degree = 0;
int xf = 0, yf = 0;
int flag = 0;
int speed = 100;
Servo myservo;
SoftwareSerial BTSerial(12, 13);

int trig = 11;
int echo = 10; 

int rightside_motors_pin1 = 2;
int rightside_motors_pin2 = 3;
int leftside_motors_pin1 = 4;
int leftside_motors_pin2 = 7;
int enableA = 5;
int enableB = 6;
void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600);
  myservo.attach(9);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(rightside_motors_pin1, OUTPUT);
  pinMode(rightside_motors_pin2, OUTPUT);
  pinMode(leftside_motors_pin1, OUTPUT);
  pinMode(leftside_motors_pin2, OUTPUT);
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);

  //getting 3 readings from the sensor to give it time to calibrate
  for (int i = 0; i < 3; i++) {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    pulseIn(echo, HIGH);
    delay(10);
  }
  //gives us time to put it on the floor :)
  delay(1000);
}

void parseCoordinates(String data){
  int commaIndex = data.indexOf(',');
  if (commaIndex > 0) {
    String xStr = data.substring(0, commaIndex);
    String yStr = data.substring(commaIndex + 1);
    xf = xStr.toInt();
    yf = yStr.toInt();
    Serial.print("Received coordinates: ");
    Serial.print("xf = ");
    Serial.print(xf);
    Serial.print(", yf = ");
    Serial.println(yf);
  }
}

void strght(){
  digitalWrite(rightside_motors_pin1, HIGH);
  digitalWrite(rightside_motors_pin2, LOW);
  digitalWrite(leftside_motors_pin1, HIGH);
  digitalWrite(leftside_motors_pin2, LOW);
  analogWrite(enableA, speed);
  analogWrite(enableB, speed);

  if (degree == 0)
    {
      y = y + 5;
    }
    else if (degree == 90)
    {
      x = x + 5;
    }
    else if (degree == 180)
    {
      y = y - 5;
    }
    else if (degree == 270)
    {
      x = x - 5;
    }
    Serial.print("Distance: ");
    Serial.println(y);
    Serial.print(", Distance: ");
    Serial.println(x);

}

void stop(){
  digitalWrite(rightside_motors_pin1, LOW);
  digitalWrite(rightside_motors_pin2, LOW);
  digitalWrite(leftside_motors_pin1, LOW);
  digitalWrite(leftside_motors_pin2, LOW);
  analogWrite(enableA, 0);
  analogWrite(enableB, 0);
}

void left(){
  digitalWrite(rightside_motors_pin1, LOW);
  digitalWrite(rightside_motors_pin2, HIGH);
  digitalWrite(leftside_motors_pin1, HIGH);
  digitalWrite(leftside_motors_pin2, LOW);
  analogWrite(enableA, speed);
  analogWrite(enableB, speed);

  //keeping the degree between 0 and 270
  degree -= 90;
  if (degree < 0)
  {
    degree += 360; 
  }
  if (degree >= 360) 
  {
    degree -= 360;
  } 
}

void right(){
  digitalWrite(rightside_motors_pin1, HIGH);
  digitalWrite(rightside_motors_pin2, LOW);
  digitalWrite(leftside_motors_pin1, LOW);
  digitalWrite(leftside_motors_pin2, HIGH);
  analogWrite(enableA, speed);
  analogWrite(enableB, speed);

  //keeping the degree between 0 and 270
  degree += 90;
  if (degree >= 360)
  {
    degree -= 360; 
  }
  if (degree < 0) 
  {
    degree += 360;
  }
}

void update_distance(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * (0.034/2);
  delay(100);
}

void detect_obstacles(){
  if (flag == 1)
  {
    strght();
    delay(500);
    if (degree == 0)
    {
      y = y + 15;
    }
    else if (degree == 90)
    {
      x = x + 15;
    }
    else if (degree == 180)
    {
      y = y - 15;
    }
    else if (degree == 270)
    {
      x = x - 15;
    }
    stop();
    delay(200);
    myservo.write(-90);
    delay(200);
    update_distance();
    if (distance > 60){
      myservo.write(90);
      delay(100);
      right();
      delay(650);
      stop();
      delay(500);
      go_where();
    }
    else{
      myservo.write(90);
      delay(100);
      detect_obstacles();
    }
  }
  else if (flag == 2)
  {
    strght();
    delay(500);
    stop();
    delay(200);
    myservo.write(180);
    delay(200);
    update_distance();
    
    if (distance > 45){
      myservo.write(90);
      delay(100);
      left();
      delay(650);
      stop();
      delay(500);
      go_where();
    }
    else{
      myservo.write(90);
      delay(100);
      detect_obstacles();
    }
  }
}

void positive_y(){
  if (degree == 90)
  {
    left();
    delay(650);
    stop();
    delay(500);
  }
  else if (degree == 180)
  {
    right();
    delay(650);
    stop();
    delay(500);
    right();
    delay(650);
    stop();
    delay(500);
  }
  else if (degree == 270)
  {
    right();
    delay(650);
    stop();
    delay(500);            
  }
  update_distance();
  while((distance > 60) && (y != yf))
  {
    myservo.write(89);
    update_distance();
    strght();
  }
  if (y == yf){
    stop();
    delay(500);
  }
  else if (distance < 60){
    stop();
    delay(500);
    myservo.write(180);
    delay(200);
    update_distance();
    
    if (distance > 45){
      myservo.write(90);
      left();
      flag = 1;
      delay(650);
      detect_obstacles();
    }
    else{
      myservo.write(90);      
      right();
      flag = 2;
      delay(650);
      detect_obstacles();
    }
  }
}
void positive_x(){
  if (degree == 180)
  {
    left();
    delay(650);
    stop();
    delay(500);
  }
  else if (degree == 270)
  {
    right();
    delay(650);
    stop();
    delay(500);
    right();
    delay(650);
    stop();
    delay(500);
  }
  else if (degree == 0)
  {
    right();
    delay(650);
    stop();
    delay(500);            
  }
  update_distance();
  while((distance > 60) && (x != xf))
  {
    myservo.write(89);
    update_distance();
    strght();
  }
  if (x == xf){
    stop();
    distance = 200;
  }
  else if (distance < 40){
    stop();
    delay(500);
    myservo.write(180);
    delay(200);
    update_distance();
    
    if (distance > 60){
      myservo.write(90);
      left();
      flag = 1;
      delay(650);
      detect_obstacles();
    }
    else{
      myservo.write(90);      
      right();
      flag = 2;
      delay(520);
      detect_obstacles();
    }
  }
}
void negative_y(){
  if (degree == 270)
  {
    left();
    delay(650);
    stop();
    delay(500);
  }
  else if (degree == 0)
  {
    right();
    delay(650);
    stop();
    delay(500);
    right();
    delay(650);
    stop();
    delay(500);
  }
  else if (degree == 90)
  {
    right();
    delay(650);
    stop();
    delay(500);            
  }
  update_distance();
  while((distance > 40) && (y != yf))
  {
    myservo.write(89);
    update_distance();
    strght();
  }
  if (y == yf){
    stop();
    distance = 200;
  }
  else if (distance < 40){
    stop();
    delay(650);
    myservo.write(180);
    delay(200);
    update_distance();
    
    if (distance > 45){
      myservo.write(90);
      left();
      flag = 1;
      delay(650);
      detect_obstacles();
    }
    else{
      myservo.write(90);      
      right();
      flag = 2;
      delay(650);
      detect_obstacles();
    } 
  }
}
void negative_x(){
  if (degree == 0)
  {
    left();
    delay(650);
    stop();
    delay(500);
  }
  else if (degree == 90)
  {
    right();
    delay(650);
    stop();
    delay(500);
    right();
    delay(650);
    stop();
    delay(500);
  }
  else if (degree == 180)
  {
    right();
    delay(650);
    stop();
    delay(500);            
  }
  update_distance();
  while((distance > 60) && (x != xf))
  {
    myservo.write(89);
    update_distance();
    strght();
  }
  if (x == xf){
    stop();
    distance = 200;
  }
  else if (distance < 40){
    stop();
    delay(500);
    myservo.write(180);
    delay(200);
    update_distance();
    
    if (distance > 60){
      myservo.write(90);
      left();
      flag = 1;
      delay(650);
      detect_obstacles();
    }
    else{
      myservo.write(90);      
      right();
      flag = 2;
      delay(650);
      detect_obstacles();
    }
  }
}
// A function that decide where to go based on final coordinates
void go_where(){
  if (y != yf && yf > y)
  {
    positive_y();
  }
  else if (y != yf && yf < y)
  {
    negative_y();
  }  
  else if (x != xf && xf > x)
  {
    positive_x();
  }
  else if (x != xf && xf < x)
  {
    negative_x();
  }
  else if ((x == xf) && (y == yf)){
    stop();
    distance = 200;
  }
}

void loop() {
  if (BTSerial.available()) {
    String data = BTSerial.readStringUntil('\n');
    parseCoordinates(data);
  }
  if ((xf == x) && (yf == y)){
    stop();
  }
  else{
    update_distance();
    go_where();
  }
}