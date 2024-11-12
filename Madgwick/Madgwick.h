#ifndef Madgwick_H
#define Madgwick_H

#include "mbed.h"

class Madgwick {
protected:
public:

    Madgwick(float gain);
    void update_attitude(float gx, float gy, float gz, float ax, float ay, float az, float sampleFreq);
    float getRoll();
    float getPitch();
    float getYaw();
    
    
protected: 
private:
  float invSqrt(float x);
  float roll, pitch, yaw;
  float recipNorm;
  float s0, s1, s2, s3;
  float qDot1, qDot2, qDot3, qDot4;
  float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;
  volatile float beta;                                // 2 * proportional gain (Kp)
  volatile float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;  // quaternion of sensor frame relative to auxiliary frame

    
};
 
 #endif
 