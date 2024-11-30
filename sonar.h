#ifndef SONAR_H
#define SONAR_H
#include "mbed.h"

///struct for sonar sensor
struct Sonar{
    ///thread object
    Thread sonarThread;

    ///current distance
    int distance_sonar;

    ///correction for calibration
    int correction;
    
    ///currently operating?
    ///close when not used to save on resources
    bool operate = false;
    
    ///constructor, need to init thread object
    Sonar();

    /// start thread
    void start();

    /// thread main function, detect if reaches the default init position
    void detect();

    /// function to termiante the thread, not used in the end
    void joinThread();

};


#endif