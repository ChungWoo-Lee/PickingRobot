#include <RPLidar.h>
#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor (MOTOCTRL).

RPLidar lidar;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200); // For RPLidar
  lidar.begin(Serial1);
  pinMode(RPLIDAR_MOTOR, OUTPUT); // set pin modes
}

// float minDistance_front = 100000;
// float angle_front = 0;
// float frontAngleMin = 0; // 각도 바꿔야됨 
// float frontAngleMax = 10.0;

float minDistance_right = 100000;
float angle_right = 0;
float rightAngleMin = 260.0; // 각도 바꿔야됨 
float rightAngleMax = 270.0;

float minDistance_left = 100000;
float angle_left = 0;
float leftAngleMin = 180.0;
float leftAngleMax = 200.0;

void loop() {
  if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance;
    float angle = lidar.getCurrentPoint().angle; //0-360 deg

    if (lidar.getCurrentPoint().startBit) {
      // a new scan, display the previous data...
      printData("오른쪽", angle_right, minDistance_right);
      printData("왼쪽", angle_left, minDistance_left);
      // printData("앞쪽", angle_front, minDistance_front);

      minDistance_right = 100000;
      angle_right = 0;
      minDistance_left = 100000;
      angle_left = 0;
    } else {
      if (angle >= rightAngleMin && angle <= rightAngleMax && distance > 0 && distance < minDistance_right) {
        minDistance_right = distance;
        angle_right = angle;
      }
      if (angle >= leftAngleMin && angle <= leftAngleMax && distance > 0 && distance < minDistance_left) {
        minDistance_left = distance;
        angle_left = angle;
      }
      // if (angle >= frontAngleMin && angle <= frontAngleMax && distance > 0 && distance < minDistance_front) {
      //   minDistance_front = distance;
      //   angle_front = angle;
      // }
    }
  }
  else {
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
    //Try to detect RPLIDAR
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
      //Detected
      lidar.startScan();
      analogWrite(RPLIDAR_MOTOR, 255);
      delay(1000);
    }
  }
}

void printData(String range, float angle, float distance)
{
  Serial.print(range);
  Serial.print(" angle: ");
  Serial.print(angle);
  Serial.print(" dist: ");
  Serial.println(distance);
}
