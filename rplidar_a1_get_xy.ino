#include <RPLidar.h>
#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor (MOTOCTRL).
<<<<<<< HEAD
// Include the AccelStepper Library
#include <AccelStepper.h>
 
// Define Constants
 
// Define step constants
#define FULLSTEP 4
#define HALFSTEP 8
 
// Define Motor Pins (2 Motors used)
 
#define motorPin1  8     // Blue   - 28BYJ48 pin 1
#define motorPin2  9     // Pink   - 28BYJ48 pin 2
#define motorPin3  10    // Yellow - 28BYJ48 pin 3
#define motorPin4  11    // Orange - 28BYJ48 pin 4
                        
                        
#define motorPin5  22     // Blue   - 28BYJ48 pin 1
#define motorPin6  23     // Pink   - 28BYJ48 pin 2
#define motorPin7  24     // Yellow - 28BYJ48 pin 3
#define motorPin8  25     // Orange - 28BYJ48 pin 4
 
// Define two motor objects
// The sequence 1-3-2-4 is required for proper sequencing of 28BYJ48
AccelStepper stepper1(FULLSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(FULLSTEP, motorPin5, motorPin7, motorPin6, motorPin8);
 
=======
>>>>>>> bd1668086a8b7498dc639a769edb20fe3073755f

RPLidar lidar;

void setup() {
<<<<<<< HEAD
  Serial.begin(115200);
  Serial1.begin(115200);  // For RPLidar
  lidar.begin(Serial1);
  pinMode(RPLIDAR_MOTOR, OUTPUT);  // set pin modes
    // 1 revolution Motor 1 CW
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(50.0);
  stepper1.setSpeed(500);
  stepper1.moveTo(100000);  
  
  // 1 revolution Motor 2 CCW
  stepper2.setMaxSpeed(1000.0);
  stepper2.setAcceleration(50.0);
  stepper2.setSpeed(500);
  stepper2.moveTo(-100000); 
 
}

void loop() {
  stepper1.run();
  stepper2.run();
  
=======
  Serial.begin(230400);
  Serial1.begin(230400);  // For RPLidar
  lidar.begin(Serial1);
  pinMode(RPLIDAR_MOTOR, OUTPUT);  // set pin modes
}

void loop() {
>>>>>>> bd1668086a8b7498dc639a769edb20fe3073755f
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
<<<<<<< HEAD
}


 
=======
}
>>>>>>> bd1668086a8b7498dc639a769edb20fe3073755f
