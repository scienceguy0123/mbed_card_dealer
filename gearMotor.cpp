#include "gearMotor.h"

PwmOut pwmout(p21);
Motor m(p21, p17, p18); // pwm, fwd, rev

///launch a card
///push a card out and also need to retract
/// if don't retract more than one card could be dealth
void Gear::throwACard(){
    m.speed(-1);
    ThisThread::sleep_for(200ms);
 
    m.speed(0.6);
    ThisThread::sleep_for(500ms);
    m.speed(0);
    ThisThread::sleep_for(500ms);
}
