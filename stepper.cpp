#include "stepper.h"
#include <type_traits>
BusOut motor_out(p9, p10, p11, p12);




 Stepper::Stepper(): stepperThread(osPriorityHigh, 1024){ ///priority high moptor has better performance
    this->current_step = 0;
    this->direction = 0;
    this->accuWaiter = new AccurateWaiter();
    this->pause = true;
}



void Stepper::start(){
    stepperThread.start(
        callback(this, &Stepper::stepperMain));
}

void Stepper::stepperMain(){
    while(1){
        if(!this->pause){
            if(currentMode == manual){
                rotate();
            }
            else if(currentMode == automatic){
                dealing();
            }
            else if(currentMode == reset){
                rotate();
            }
            else{
                // since we are giving this thread high priority, we need to let it wait a while
                // when it has nothing to do, otherwise other threads with lower priority will \
                //never have chance to run
                accuWaiter->wait_for(100ms); 
            }
        }
        else{
           // since we are giving this thread high priority, we need to let it wait a while
           // when it has nothing to do, otherwise other threads with lower priority will \
           //never have chance to run
            accuWaiter->wait_for(500ms); 
        
        }
    }
}

void Stepper::rotateLeft(){
    this->direction = 1;
    motor_out = this->arr[current_step];
    this->current_step ++;
    if(this->current_step > 7){
        this->current_step = 0;
    }
    accuWaiter->wait_for(1200us);
}

void Stepper::rotateRight(){
    this->direction = 0;
    motor_out = this->arr[current_step];
    this->current_step --;
    if(this->current_step < 0){
        this->current_step = 7;
    }
    accuWaiter->wait_for(1200us);
}

void Stepper::rotate(){   
    if(this->direction){
        rotateLeft();
    }
    else{
        rotateRight();
    }
};

void Stepper::dealOnePlayer(){
    for(int i = 0 ; i < this->stepsForOnePlayer; i++){
        rotateRight();
    }
    gear.throwACard();
    // accuWaiter->wait_for(1000ms); // timne for dealing card 
}

void Stepper::returnToFirstPlayer(){
    for(int i = 0 ; i < playerNum; i++){
        for(int j = 0; j < this->stepsForOnePlayer; j++ ){
            rotateLeft();
        }
    }
    
    accuWaiter->wait_for(1000ms); // timne for dealing card 
}

/// Always deal from left to right
void Stepper::dealing(){
    
    for(int i = 0 ; i < CardPerPile; i++){
        for(int j = 0 ; j < playerNum ; j ++){
            if(this->pause){
                currentMode = ModeSelection;
                displayOptionIndex = 0;
                return;
            }
            else{
                dealOnePlayer();

            }
        }
        returnToFirstPlayer();
    }
   
    this-> pause = true;
    // this -> currentMode = rest;
    currentMode = ModeSelection;
    displayOptionIndex = 0;
}
  

void Stepper::change_direction(){
    this->direction = !this->direction;
}
