#include "mbed.h"
#include "stepper.h"
#include "sonar.h"
#include "display.h"
#include "Mode.h"
#include "global.h"
#include "DebounceIn.h"

DebounceIn b1 (p14);
DebounceIn b2 (p15);
DebounceIn b3 (p8);
DebounceIn b4 (p16);

DigitalOut led1 (LED1);
DigitalOut led2 (LED2);
DigitalOut led3 (LED3);
DigitalOut led4 (LED4);

Stepper stepper;
Sonar sonar;
Display display;

Mode currentMode = ModeSelection;
int playerNum = 4; // default assume 4 players
int CardPerPile = 1; //default to 1;
int displayOptionIndex = 0;

void resetToStart(){
    currentMode = reset;
    sonar.operate = true;
    sonar.distance_sonar = 100;//reset distance
    stepper.direction = 1;
    // stepper.currentMode = stepper.manual;
    stepper.pause = false;
    while(sonar.distance_sonar > 8){
        printf(" %d inch in main \n\r",sonar.distance_sonar);
    }
    sonar.operate = false;
    stepper.pause = true;
}

int main() {
    b1.mode(PullUp);
    b2.mode(PullUp);
    b3.mode(PullUp);
    b4.mode(PullUp);
    
    sonar.start();
    stepper.start();
    display.start();
    while (1) {
        if(!b1.read()){
            // stepper.change_direction();
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
                // stepper.currentMode = stepper.manual;
                stepper.pause = false;
            }
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
                // stepper.currentMode = stepper.manual;
                stepper.pause = false;
            }

            
            
            // led1 = 0;
            // led2 = 1;
            // led3 = 0;

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
                // if (selection){
                //     if(currentMode == automaticPlayerSelection){
                //         playerNum = selection;
                //     }
                //     else if(currentMode == automatiocCardSelection){
                //         CardPerPile = selection;
                //     }
                // }
            }
            else if (currentMode == manual){
                stepper.gear.throwACard();
            }
            // led1 = 1;
            // led2 = 1;
            // led3 = 0;
            // resetToStart();
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
            // stepper.currentMode = stepper.automatic;
            // stepper.pause = false;
            // ThisThread::sleep_for(150ms);
        }
        else{
            // stepper.currentMode = stepper.rest;
            if(currentMode == manual){
                stepper.pause = true;
            }
            

            led1 = 0;
            led2 = 0;
            led3 = 1;
        }

    }
    
}