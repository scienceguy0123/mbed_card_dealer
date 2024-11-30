#include "mbed.h"
#include "Motor.h" ///imported motor library

///struct for gear dc motor
struct Gear{
    ///launch a card
    ///push a card out and also need to retract
    /// if don't retract more than one card could be dealth
    void throwACard();
};