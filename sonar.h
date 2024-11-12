#ifndef SONAR_H
#define SONAR_H
#include "mbed.h"

struct Sonar{
    Thread sonarThread;
    int distance_sonar;
    int correction;
    
    bool operate = false;
    
    Sonar();

    void start();

    void detect();

    void joinThread();

};


#endif