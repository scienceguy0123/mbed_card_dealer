#include "mbed.h"
#include "ahrs.h"
#include "ICM20948.h"
#include "Madgwick.h"
#include <iostream>
#include <string>
#include <cstdio>  // For sprintf
#include <algorithm>  // For std::max

struct IMU {
  
    long yaw;
    IMU();
    void start();
    void get_yaw();

    Thread imuThread;

};