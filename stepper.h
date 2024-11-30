#ifndef STEPPER_H
#define STEPPER_H
#include "mbed.h"
#include "AccurateWaiter.h" // better timer in thread
#include "global.h"
#include "gearMotor.h"

///struct for stepper motor
struct Stepper{
    /// From internet, will move counter clockwise if send val to the bus from left to right
    // and move clockwise if  send val to the bus from right to left
    int arr[8] = {0x1, 0x3, 0x2, 0x6, 0x4, 0xC, 0x8, 0x9};
    /// current index on the array above
    int current_step;
    //clockwise or counter closkwise
    int direction;
    ///thread object
    Thread stepperThread;

    // better timer in thread, provide microsend support needed for stepper motor
    AccurateWaiter* accuWaiter;  
    
    /// rotating?
    bool pause;
    
    int stepsForOnePlayer = 2750;

    ///gear motor object
    Gear gear;

    ///constructor, init thread
    Stepper();
    ///main function for thread
    void stepperMain();

    /// rotate either left or right dependes on direction variable
    void rotate();
    
    void rotateLeft();
    void rotateRight();
    
    /// start thread
    void start();
    ///flip direction
    void change_direction();

    ///Workflow for automatic dealing mode
    void dealing();
    ///rotate enough distance and throw a card with dc morot
    void dealOnePlayer();
    ///return to first player's postion
    void returnToFirstPlayer();
};


#endif