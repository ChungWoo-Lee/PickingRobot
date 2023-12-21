#include <RPLidar.h>
#define RPLIDAR_MOTOR 3  // The PWM pin for control the speed of RPLIDAR's motor (MOTOCTRL).

RPLidar lidar;


int Dir1Pin_A = 4;
int Dir2Pin_A = 5;
int Dir1Pin_B = 6;
int Dir2Pin_B = 7;
int ena = 12;
int enb = 13;

float errorMargin = 5.0;

// float minDistance_front = 100000;
// float angle_front = 0;
// float frontAngleMin = 0; // 각도 바꿔야됨
// float frontAngleMax = 10.0;

float minDistance_left = 100000;
float angle_left = 0;
float leftAngleMin = 269.0;
float leftAngleMax = 271.0;

float initialDistance_left = -1;
float initialfront = -1;
unsigned long startTime = 0;

void printData(String range, float angle, float distance) {
  Serial.print(range);
  Serial.print(" angle: ");
  Serial.print(angle);
  Serial.print(" dist: ");
  Serial.println(distance);
}

void modi_left() {
  digitalWrite(Dir1Pin_A, HIGH);
  digitalWrite(Dir2Pin_A, LOW);
  digitalWrite(Dir1Pin_B, HIGH);
  digitalWrite(Dir2Pin_B, LOW);
  analogWrite(ena, 100);
  analogWrite(enb, 80);
}
void modi_right() {
  digitalWrite(Dir1Pin_A, HIGH);
  digitalWrite(Dir2Pin_A, LOW);
  digitalWrite(Dir1Pin_B, HIGH);
  digitalWrite(Dir2Pin_B, LOW);
  analogWrite(ena, 80);
  analogWrite(enb, 180);
}
void goStraight() {
  digitalWrite(Dir1Pin_A, HIGH);
  digitalWrite(Dir2Pin_A, LOW);
  digitalWrite(Dir1Pin_B, HIGH);
  digitalWrite(Dir2Pin_B, LOW);
  analogWrite(ena, 100);
  analogWrite(enb, 100);
}

void R_Uturn() {
  digitalWrite(Dir1Pin_A, HIGH);
  digitalWrite(Dir2Pin_A, LOW);
  digitalWrite(Dir1Pin_B, HIGH);
  digitalWrite(Dir2Pin_B, LOW);
  analogWrite(ena, 50);
  analogWrite(enb, 200);
}

void L_Uturn() {
  digitalWrite(Dir1Pin_A, HIGH);
  digitalWrite(Dir2Pin_A, LOW);
  digitalWrite(Dir1Pin_B, HIGH);
  digitalWrite(Dir2Pin_B, LOW);
  analogWrite(ena, 20);
  analogWrite(enb, 200);
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);  // For RPLidar
  lidar.begin(Serial1);
  pinMode(RPLIDAR_MOTOR, OUTPUT);  // set pin modes

  pinMode(Dir1Pin_A, OUTPUT);
  pinMode(Dir2Pin_A, OUTPUT);
  pinMode(Dir1Pin_B, OUTPUT);
  pinMode(Dir2Pin_B, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
}

void loop() {
  if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance;
    float angle = lidar.getCurrentPoint().angle;  //0-360 deg

    if (lidar.getCurrentPoint().startBit) {
      
      minDistance_left = 100000;
      angle_left = 0;
    } else {
      if (angle >= leftAngleMin && angle <= leftAngleMax && distance > 0) {
        if (initialDistance_left == -1) {
          initialDistance_left = distance;
        } else if (distance >= initialDistance_left - errorMargin && distance <= initialDistance_left + errorMargin) {
          goStraight();
          
        } else if (distance < initialDistance_left - errorMargin) {
          modi_right();
          
        } else if (distance > initialDistance_left + errorMargin) {
          modi_left();
         
        }
        angle_left = angle;
      }
      
      
    }
  } else {
    analogWrite(RPLIDAR_MOTOR, 0);
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
      lidar.startScan();
      analogWrite(RPLIDAR_MOTOR, 255);
      delay(1000);
    }
  }
}