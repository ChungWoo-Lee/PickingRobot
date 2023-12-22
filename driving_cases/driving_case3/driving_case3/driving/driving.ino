#include <RPLidar.h>
#include <AccelStepper.h>
#define FULLSTEP 4
#define HALFSTEP 8
#define RPLIDAR_MOTOR 3  // The PWM pin for control the speed of RPLIDAR's motor (MOTOCTRL).
RPLidar lidar;
// Define Motor Pins (2 Motors used)

#define motorPin1 8   // Blue   - 28BYJ48 pin 1
#define motorPin2 9   // Pink   - 28BYJ48 pin 2
#define motorPin3 10  // Yellow - 28BYJ48 pin 3
#define motorPin4 11  // Orange - 28BYJ48 pin 4


#define motorPin5 22  // Blue   - 28BYJ48 pin 1
#define motorPin6 23  // Pink   - 28BYJ48 pin 2
#define motorPin7 24  // Yellow - 28BYJ48 pin 3
#define motorPin8 25  // Orange - 28BYJ48 pin 4

// Define two motor objects
// The sequence 1-3-2-4 is required for proper sequencing of 28BYJ48
AccelStepper stepper1(FULLSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(FULLSTEP, motorPin5, motorPin7, motorPin6, motorPin8);



void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);  // For RPLidar
  lidar.begin(Serial1);
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(50.0);
  stepper1.setSpeed(500);
  stepper1.moveTo(10000);

  // 1 revolution Motor 2 CCW
  stepper2.setMaxSpeed(1000.0);
  stepper2.setAcceleration(50.0);
  stepper2.setSpeed(500);
  stepper2.moveTo(-10000);


  pinMode(RPLIDAR_MOTOR, OUTPUT);  // set pin modes
}
float minDistance = 100000;
float angleAtMinDist = 0;

void left(long step) {
  stepper1.stop();
  stepper2.moveTo(stepper2.currentPosition() + step);
}

void right(long step) {
  stepper2.stop();
  stepper1.moveTo(stepper1.currentPosition() - step);
}
void printData(float angle, float distance) {
  Serial.print("dist: ");
  Serial.print(distance);
  Serial.print("    angle: ");
  Serial.println(angle);
}




void loop() {
  // unsigned long timeNow = millis();

  // if (startScanning && timeNow - timeStart < 5000) {
  //   if (IS_OK(lidar.waitPoint())) {
  //     //perform data processing here...
  //     float distance = lidar.getCurrentPoint().distance;
  //     float angle = lidar.getCurrentPoint().angle;  // 0-360 deg

  //     if (lidar.getCurrentPoint().startBit) {
  //       // a new scan, display the previous data...
  //       printData(angleAtMinDist, minDistance);
  //       minDistance = 100000;
  //       angleAtMinDist = 0;
  //     } else {
  //       if (distance > 0 && distance < minDistance) {
  //         minDistance = distance;
  //         angleAtMinDist = angle;
  //       }
  //     }
  //   } else {
  //     analogWrite(RPLIDAR_MOTOR, 0);  //stop the rplidar motor
  //     // Try to detect RPLIDAR
  //     rplidar_response_device_info_t info;
  //     if (IS_OK(lidar.getDeviceInfo(info, 100))) {
  //       // Detected
  //       lidar.startScan();
  //       analogWrite(RPLIDAR_MOTOR, 255);
  //       delay(1000);
  //     }
  //   }
  // } else {
  stepper1.moveTo(stepper1.currentPosition() + 6000);
  stepper2.moveTo(stepper2.currentPosition() - 6000);
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
    Serial.println("while 6000스텝수 문 도는 중");
  }
  stepper1.moveTo(stepper1.currentPosition() + 6000);
  stepper2.moveTo(stepper2.currentPosition() - 6000);
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
    // Serial.println("while 12000스텝수 문 도는 중");
  }
  right(2300);
  while (stepper1.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
    // Serial.println("while r2 문 도는 중");
  }


  stepper1.moveTo(stepper1.currentPosition() + 2400);
  stepper2.moveTo(stepper2.currentPosition() - 2400);
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
    // Serial.println("while 2400 스텝수 문 도는 중");
  }
  right(2300);
  while (stepper1.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
    // Serial.println("while r2 문 도는 중");
  }
  stepper1.moveTo(stepper1.currentPosition() + 3000);
  stepper2.moveTo(stepper2.currentPosition() - 3000);
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
    // Serial.println("while 12000스텝수 문 도는 중");
  }
  stepper1.moveTo(stepper1.currentPosition() + 3000);
  stepper2.moveTo(stepper2.currentPosition() - 3000);
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
    Serial.println("while 3000스텝수 문 도는 중");
  }
  left(2300);
  while (stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
    // Serial.println("while l1 문 도는 중");
  }
  stepper1.moveTo(stepper1.currentPosition() + 2400);
  stepper2.moveTo(stepper2.currentPosition() - 2400);
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
    // Serial.println("while 2400 스텝수 문 도는 중");
  }
  left(2300);
  
  for (int i = 0; i < 2; i++) {
    Serial.println(String(i + 1) + "번째 for문 도는 중");

    // Step 1
    stepper1.moveTo(stepper1.currentPosition() + 6000);
    stepper2.moveTo(stepper2.currentPosition() - 6000);
    while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while 12000스텝수 문 도는 중");
    }
    right(2300);
    while (stepper1.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while r2 문 도는 중");
    }


    stepper1.moveTo(stepper1.currentPosition() + 2400);
    stepper2.moveTo(stepper2.currentPosition() - 2400);
    while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while 2400 스텝수 문 도는 중");
    }
    right(2300);
    while (stepper1.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while r2 문 도는 중");
    }
    stepper1.moveTo(stepper1.currentPosition() + 6000);
    stepper2.moveTo(stepper2.currentPosition() - 6000);
    while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while 12000스텝수 문 도는 중");
    }
    left(2300);
    while (stepper2.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while l1 문 도는 중");
    }
    stepper1.moveTo(stepper1.currentPosition() + 2400);
    stepper2.moveTo(stepper2.currentPosition() - 2400);
    while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while 2400 스텝수 문 도는 중");
    }
    left(2300);
  }

  for (int i = 0; i < 3; i++) {
    Serial.println(String(i + 1) + "번째 for2문 도는 중");

    // Step 1
    stepper1.moveTo(stepper1.currentPosition() + 6000);
    stepper2.moveTo(stepper2.currentPosition() - 6000);
    while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while 12000스텝수 문 도는 중");
    }
    stepper1.moveTo(stepper1.currentPosition() + 6000);
    stepper2.moveTo(stepper2.currentPosition() - 6000);
    while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while 12000스텝수 문 도는 중");
    }
    right(2300);
    while (stepper1.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while r2 문 도는 중");
    }


    stepper1.moveTo(stepper1.currentPosition() + 2400);
    stepper2.moveTo(stepper2.currentPosition() - 2400);
    while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while 2400 스텝수 문 도는 중");
    }
    right(2300);
    while (stepper1.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while r2 문 도는 중");
    }
    stepper1.moveTo(stepper1.currentPosition() + 6000);
    stepper2.moveTo(stepper2.currentPosition() - 6000);
    while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while 12000스텝수 문 도는 중");
    }
    stepper1.moveTo(stepper1.currentPosition() + 6000);
    stepper2.moveTo(stepper2.currentPosition() - 6000);
    while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while 12000스텝수 문 도는 중");
    }
    left(2300);
    while (stepper2.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while l1 문 도는 중");
    }
    stepper1.moveTo(stepper1.currentPosition() + 2400);
    stepper2.moveTo(stepper2.currentPosition() - 2400);
    while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
      stepper1.run();
      stepper2.run();
      // Serial.println("while 2400 스텝수 문 도는 중");
    }
    left(2300);
  }
}-