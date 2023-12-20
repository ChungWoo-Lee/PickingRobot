#include <RPLidar.h>
#define RPLIDAR_MOTOR 3 

RPLidar lidar;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  lidar.begin(Serial1);
  pinMode(RPLIDAR_MOTOR, OUTPUT);
}

float Distance_obs = 100000;
float angle_obs = 0;
float CheckAngleMin = 0.0;
float CheckAngleMax = 90.0;
float distance_a = 0;
float distance_b = 0;

void loop() {
  if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance;
    float angle = lidar.getCurrentPoint().angle;
    float radian = 0;
    float x = 0;
    float y = 0;

    

    if (lidar.getCurrentPoint().startBit) {
      radian = angle * M_PI / 180;
      x = distance * cos(radian);
      y = distance * sin(radian);

      if (angle == 0) {
      y_cor = distance;
    } 
    if (angle == 90) {
      x_cor = distance;   
    } else {      
      if (0 = <x && x_cor >= x-100 && 0>= y && y_cor >= y-100){
        DistanceX_obs=x
        DistanceY_obs=y
      }

      if (x_cor / 2 < DistanceX_obs && DistanceX_obs < x_cor && y_cor / 2 < DistanceY_obs && DistanceY_obs < y_cor) {
      case = 1;
      printData("case1", x, y);
    } else if (0 < x && x < x_cor / 2 && y_cor / 2 < y && y < y_cor) {
      case = 2;
      printData("case2", x, y);
    } else if (0 < x && x < x_cor / 2 && 0 < y && y < y_cor / 2) {
      case = 3;
      printData("case3", x, y);
    } else if (x_cor / 2 < x && x < x_cor && 0 < y && y < y_cor / 2) {
      case = 4;
      printData("case4", x, y);
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

void printData(String range, float x_data, float y_data)
{
  Serial.print(range);
  Serial.print(" x: ");
  Serial.print(x_data);
  Serial.print(" y: ");
  Serial.println(y_data);
}
