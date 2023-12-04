#include <RPLidar.h>
#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor (MOTOCTRL).

RPLidar lidar;

void setup() {
  Serial.begin(230400);
  Serial1.begin(230400);  // For RPLidar
  lidar.begin(Serial1);
  pinMode(RPLIDAR_MOTOR, OUTPUT);  // set pin modes
}

void loop() {
  if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance;
    float angle = lidar.getCurrentPoint().angle;  // 0-360 deg

    // Calculate (x, y) coordinates
    float angleRadians = angle * PI / 180.0;
    float x = distance * cos(angleRadians);
    float y = distance * sin(angleRadians);

    // Print all data
    printData(x, y);
  }
  else {
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
    // Try to detect RPLIDAR
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       // Detected
       lidar.startScan();
       analogWrite(RPLIDAR_MOTOR, 255);
       delay(1000);
    }
  }
}

void printData(float x, float y)
{
  Serial.print("Data ");
  Serial.print(String(x));
  Serial.print(" ");
  Serial.println(String(y));
}