#include "imu.h"


#define accel_div   1
#define accel_lp    0
#define accel_lp_en    1
#define accel_fs    1
#define gyro_div   1
#define gyro_lp    0
#define gyro_lp_en    1
#define gyro_fs    1

#define accel_conf (accel_lp_en | (accel_fs << 1) | (accel_lp << 3))
#define gyro_conf (gyro_lp_en | (gyro_fs << 1) | (gyro_lp << 3))

#define ahrs_beta 0.1f

using namespace std::chrono;    //needed to do time in us

static BufferedSerial pc(USBTX, USBRX);
ICM20948 icm(p28, p27);   //(SDA, SCL)
Madgwick   AHRS(ahrs_beta);
Timer t;

float normalize(unsigned int x, float min, float max){
    return (x - min) / (max - min);
}



IMU :: IMU() : imuThread(osPriorityNormal, 1024){
    icm.init(accel_conf, accel_div, gyro_conf, gyro_div);

}
void IMU::start(){
    icm.init(accel_conf, accel_div, gyro_conf, gyro_div);
    t.start();
    imuThread.start(callback(this, &IMU::get_yaw));
}



void IMU::get_yaw()
{

    while(1){
        icm.getAccGyro();
        float time = static_cast<float>(duration_cast<microseconds>(t.elapsed_time()).count()) / 1000000.0f;
        AHRS.update_attitude(icm.getGX(), icm.getGY(), icm.getGZ(), icm.getAX(), icm.getAY(), icm.getAZ(), time);

        t.reset();

        long _yaw = static_cast<long>(AHRS.getYaw() * 100.0f + 32767.0f) ;
        // float _yaw = AHRS.getYaw() ;        
        char msg[54];

        this->yaw = _yaw;

        // long _yaw = static_cast<long>(AHRS.getYaw() * 100.0f + 32767.0f) ;
        // float _yaw = AHRS.getYaw() ;

         printf("yaw: %ld\r\n", _yaw);
        // printf("yaw: %f\r\n", _yaw);
    }
  
}