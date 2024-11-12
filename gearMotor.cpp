#include "gearMotor.h"

PwmOut pwmout(p21);
Motor m(p21, p17, p18); // pwm, fwd, rev

void Gear::throwACard(){
    m.speed(-1);
    ThisThread::sleep_for(200ms);
    // m.speed(-0.8);
    // ThisThread::sleep_for(150ms);
    m.speed(0.6);
    ThisThread::sleep_for(500ms);
    m.speed(0);
    ThisThread::sleep_for(500ms);
}
