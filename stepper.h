#ifndef STEPPER_H
#define STEPPER_H
#include "mbed.h"
#include "AccurateWaiter.h"
#include "global.h"
#include "gearMotor.h"

struct Stepper{
    int arr[8] = {0x1, 0x3, 0x2, 0x6, 0x4, 0xC, 0x8, 0x9};
    int current_step;
    int direction;
    Thread stepperThread;
    AccurateWaiter* accuWaiter;
    bool pause;
    int stepsForOnePlayer = 2750;
    Gear gear;

    // int playerNum = 4; // starts with 0, so actually 4 players
    // int CardPerPile;
    // typedef enum{
    //     rest,
    //     manual, //control by buttons
    //     automatic  // deealing card
    // }Mode;

    // Mode currentMode;

    Stepper();
    void stepperMain();
    void rotate();
    void rotateLeft();
    void rotateRight();
    void start();
    void change_direction();
    void dealing();
    void dealOnePlayer();
    void returnToFirstPlayer();
};

// void stepperThreadFunc();
#endif