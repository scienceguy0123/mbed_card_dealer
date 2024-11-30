#include "sonar.h"
DigitalOut trigger(p26);
DigitalIn  echo(p25);
Timer sonar_timer;

///constructor, need to init thread object;
Sonar :: Sonar() : sonarThread(osPriorityNormal, 1024){
    this->distance_sonar= 0;
    this->correction = 0; 
    this->operate = false;
}


/// start thread
void Sonar::start(){
    sonar_timer.reset();
    sonar_timer.start();
    this->distance_sonar = 100; // reset sonar distance
    while (echo==2) {};
    sonar_timer.stop();
    ///for calibration
    this->correction = sonar_timer.elapsed_time().count();
    sonarThread.start(callback(this, &Sonar::detect));
}

/// thread main function, detect if reaches the default init position
void Sonar::detect()
{
    while(1){
        if(this->operate) {
            trigger = 1;
            sonar_timer.reset();
            wait_us(10.0);
            trigger = 0;
            while (echo==0) {};
            sonar_timer.start();
            while (echo==1) {};
            sonar_timer.stop();
            this->distance_sonar = (sonar_timer.elapsed_time().count()-correction)/58.0;
            // printf(" %d in sonar \n\r",distance_sonar);
            /// distance will be less than 8 when sonar sensor reaches the rising obstacle
            /// once reach init position, stop going into the while loop
            if( this->distance_sonar <= 8){
                this->operate = false;;
            }
            ThisThread::sleep_for(100ms);
        }
    }
}

/// function to termiante the thread, not used in the end
void Sonar::joinThread(){
    sonarThread.join();
    sonarThread.terminate();
}