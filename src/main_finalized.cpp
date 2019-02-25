#include <Arduino.h>
#include <Servo.h>
#include <BH1750FVI.h> // Sensor Library
#include <Wire.h> // I2C Library
#include "include/cRangeFinder.h"

// Functions
void twoDirectionSense();
void stop();
void Forward();
void Backward();
void rotateLeft();
void rotateRight();
void rotateLeft_s();
void rotateRight_s();
void rotate180();
void obstacleSense(int angle);
void senseLight();

//Pin numbers
int echoPin = 7;  //ECHO Pin for Ultrasonic Sensor
int triggerPin = 6; //TIRG Pin for Ultrasonic Sensor
int pinI1=5;  //IN1
int pinI2=4;  //IN2
int pinI3=3;  //IN3
int pinI4=2;  //IN4

//Global variable
float front_dist, left_dist, right_dist;
int left_speed=200, right_speed=200, front_angle=90, left_angle=170, right_angle=10;
int obstacle_range = 30, check_range = 20;
int moveFlag = 1;
int count = 0;
unsigned int maxlight = 100;
unsigned int light_min_level = 0, light_max_level = 30, light_no_difference = 2;
uint16_t left_lux, right_lux;
Servo myservo;  // create servo object to control a servo
PingUltrasonic ultra_sensor(triggerPin, echoPin);
cRangeFinder range_finder;
BH1750FVI LightSensor1;
BH1750FVI LightSensor2;


int angle180_time_5V = 730, angle90_time_5V = 365;
// int angle180_time_5V = 700, angle90_time_5V = 365;

void setup()
{
  Serial.begin(9600);
  pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  myservo.attach(9,  500, 2400); // Output Pin of Servo Motor
  LightSensor1.begin();
  LightSensor2.begin();
  LightSensor1.SetAddress(Device_Address_H);//Address 0x5C
  LightSensor2.SetAddress(Device_Address_L);//Address 0x5C
  LightSensor1.SetMode(Continuous_H_resolution_Mode);
  LightSensor2.SetMode(Continuous_H_resolution_Mode);
}

void loop()
{
  myservo.write(front_angle); //Initial position of Servo Motor
  senseLight();
  //Already at the light spot
  if(left_lux >= light_max_level || right_lux >= light_max_level) {
    moveFlag = 0;
    if(left_lux <= maxlight && right_lux <= maxlight){
      Serial.println("Already at the light spot");
      stop();
    }
    else if(right_lux > maxlight && right_lux >= left_lux) {
      rotateRight_s();
      Forward();
      delay(100);
      stop();
    }
    else if(left_lux > maxlight && left_lux >= right_lux) {
      rotateLeft_s();
      Forward();
      delay(100);
      stop();
    }
  }
  else {
    moveFlag = 1;
  }

  if(moveFlag == 1) {
    obstacleSense(front_angle);
    if(front_dist<=obstacle_range){
      stop();
      Serial.println("Have obstacle");

      obstacleSense(right_angle);
      if(right_dist >= 0 && right_dist > check_range && right_dist != 490) {
        Serial.println("Rotate right to avoid obstacle");
        rotateRight();
      }
      //Obstacle found in front
      // else if(right_dist >=0 && right_dist <=obstacle_range && right_dist != 490) {
      else if( right_dist <= obstacle_range && right_dist != 490) {
        obstacleSense(left_angle);
        if(left_dist >=0 && left_dist > check_range) {
          Serial.println("Rotate left to avoid obstacle");
          rotateLeft();
        }
      }
      if (front_dist <= obstacle_range && right_dist <= obstacle_range && left_dist <= obstacle_range)  {
        Serial.println("Rotate 180 to avoid 3 obstacles");
        rotate180();
      }
    }
    //end obstacle sense part

    //light sense if no obstacle
    else {
      if(left_lux >= light_min_level || right_lux >= light_min_level) {
        Serial.println("A stronger light spot is spoted");
        //Left light spot is significant greater
        if(left_lux >= light_min_level && left_lux > right_lux) {
          if((left_lux - right_lux) > light_no_difference){
            Serial.println("Left Linght Stronger");
            rotateLeft_s();
          }
        }
        //Right light spot is significant greater
        else if(right_lux >= light_min_level && right_lux > left_lux) {
          if((right_lux - left_lux) > light_no_difference){
            Serial.println("Right Linght Stronger");
            rotateRight_s();
          }
        }
        //Left and Right
        Serial.println("Weak Light, Forward");
        Forward();
      }
    }
    //end light sense part
  }
}

void obstacleSense(int angle) {
  myservo.write(angle); //Initial position of Servo Motor
  Serial.print("Sevo move to: ");
  Serial.println(angle);
  delay(1000);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); // Pulse for 10μ s to trigger ultrasonic detection
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  int distance = pulseIn(echoPin, HIGH); // Read receiver pulse time
  distance= distance/58; // Transform pulse time to distance
  Serial.print("        obstacleSense(): ");
  if(angle == front_angle) {
    front_dist= distance;
    Serial.print(front_dist);
  }
  else if(angle == right_angle) {
    right_dist= distance;
    Serial.print(front_dist);
  }
  else if(angle == left_angle) {
    left_dist= distance;
    Serial.print(front_dist);
  }
  Serial.println(" cm");
  delay(100);
}

void stop() {
  digitalWrite(pinI4,HIGH);
  digitalWrite(pinI3,HIGH);
  digitalWrite(pinI1,HIGH);
  digitalWrite(pinI2,HIGH);
  Serial.println("Stoping");
}

void Forward() {
  digitalWrite(pinI4,HIGH); //3 <- 4
  digitalWrite(pinI3,LOW);
  digitalWrite(pinI1,HIGH); //2 <- 1
  digitalWrite(pinI2,LOW);
  Serial.println("Forwarding");
}

void Backward() {
  digitalWrite(pinI4,LOW); //3 -> 4
  digitalWrite(pinI3,HIGH);
  digitalWrite(pinI1,LOW); //2 -> 1
  digitalWrite(pinI2,HIGH);
  Serial.println("Backwarding");
}

void rotateLeft() {
  digitalWrite(pinI4,LOW); //3 <- 4
  digitalWrite(pinI3,HIGH);
  digitalWrite(pinI1,HIGH); //1 -> 2
  digitalWrite(pinI2,LOW);
  Serial.println("Rotate left ing in function");
  delay(angle90_time_5V);
  stop();
}

void rotateLeft_s() {
  digitalWrite(pinI4,LOW); //3 <- 4
  digitalWrite(pinI3,HIGH);
  digitalWrite(pinI1,HIGH); //1 -> 2
  digitalWrite(pinI2,LOW);
  Serial.println("Rotate left ing in function");
  delay(angle90_time_5V/2);
  stop();
}

void rotateRight() {
  digitalWrite(pinI4,HIGH); //3 <- 4
  digitalWrite(pinI3,LOW);
  digitalWrite(pinI1,LOW); //1 <- 2
  digitalWrite(pinI2,HIGH);
  Serial.println("Rotate right ing");
  delay(angle90_time_5V);
  stop();
}

void rotateRight_s() {
  digitalWrite(pinI4,HIGH); //3 <- 4
  digitalWrite(pinI3,LOW);
  digitalWrite(pinI1,LOW); //1 <- 2
  digitalWrite(pinI2,HIGH);
  Serial.println("Rotate right ing");
  delay(angle90_time_5V/2);
  stop();
}

void rotate180() {
  digitalWrite(pinI4,HIGH); //3 <- 4
  digitalWrite(pinI3,LOW);
  digitalWrite(pinI1,LOW); //1 <- 2
  digitalWrite(pinI2,HIGH);
  Serial.println("Rotate 180 ing");
  delay(angle180_time_5V);
  stop();
}

void senseLight() {
  left_lux = LightSensor1.GetLightIntensity();// Get Lux value
  Serial.print("Left light: ");
  Serial.print(left_lux);
  Serial.println(" lux");
  right_lux = LightSensor2.GetLightIntensity();// Get Lux value
  Serial.print("Right light: ");
  Serial.print(right_lux);
  Serial.println(" lux");
}
