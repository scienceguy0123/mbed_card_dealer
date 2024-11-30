#include "mbed.h"
#include "stepper.h"
#include "sonar.h"
#include "display.h"
#include "Mode.h"
#include "global.h"
#include "DebounceIn.h" // debounce library

DebounceIn b1 (p14);
DebounceIn b2 (p15);
DebounceIn b3 (p8);
DebounceIn b4 (p16);

DigitalOut led1 (LED1);
DigitalOut led2 (LED2);
DigitalOut led3 (LED3);
DigitalOut led4 (LED4);

/// Stepper motor thread object
Stepper stepper;
/// Sonar sensor thread object
Sonar sonar;
/// Display thread object
Display display;

Mode currentMode = ModeSelection; // Mode will determine buttons' behavior
int playerNum = 4; // default assume 4 players
int CardPerPile = 1; //default to 1;
int displayOptionIndex = 0;

/// This function helps the system return to the default starting position
void resetToStart(){
    currentMode = reset;
    sonar.operate = true;
    sonar.distance_sonar = 100;//reset distance
    stepper.direction = 1;
    stepper.pause = false;
    while(sonar.distance_sonar > 8){
        printf(" %d inch in main \n\r",sonar.distance_sonar);
    }
    sonar.operate = false;
    stepper.pause = true;
}

///main function
int main() {
    b1.mode(PullUp);
    b2.mode(PullUp);
    b3.mode(PullUp);
    b4.mode(PullUp);
    
    sonar.start();
    stepper.start();
    display.start();
    while (1) {
        //Mode will determine buttons' behaviors
        if(!b1.read()){
            if(
                currentMode == ModeSelection 
                || currentMode == automaticPlayerSelection 
                || currentMode == automatiocCardSelection 
            ){
                display.nextOption();
                led1 = 0;
                led2 = 1;
                led3 = 0;
            }
            else if(currentMode == manual){
                stepper.direction = 0;
                stepper.pause = false;
            }
            /// debounce purpose
            ThisThread::sleep_for(200ms);
        }

        else if(!b2.read()){
            if(
                currentMode == ModeSelection
                || currentMode == automaticPlayerSelection 
                || currentMode == automatiocCardSelection 
            ){
                display.previousOption();
                led1 = 0;
                led2 = 1;
                led3 = 0;

            }

            else if(currentMode == manual){
                stepper.direction = 1;
                stepper.pause = false;
            }
            /// debounce purpose
            ThisThread::sleep_for(200ms);
        }
        else if(!b3.read()){
            if(currentMode == ModeSelection
                || currentMode == automaticPlayerSelection 
                || currentMode == automatiocCardSelection 
            ){
                if(currentMode == automatiocCardSelection){
                    resetToStart();
                }
                int selection = display.selectOption();
                stepper.pause=false;
            }
            else if (currentMode == manual){
                stepper.gear.throwACard();
            }
            /// debounce purpose
            ThisThread::sleep_for(200ms);
            
           
        }
        else if(!b4.read()){
            if(currentMode == manual 
            || currentMode == automatic
            || currentMode == automaticPlayerSelection
            || currentMode == automatiocCardSelection
            ){
                display.backToPrevious ();
                stepper.pause=true;
            }
        }
        else{
            
            if(currentMode == manual){
                stepper.pause = true;
            }
            //debug purpose
            led1 = 0;
            led2 = 0;
            led3 = 1;
        }

    }
    
}