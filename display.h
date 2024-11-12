#ifndef DISPLAY_H
#define DISPLAY_H

#include "Adafruit_SSD1306.h"
#include "mbed.h"
#include <vector>
#include <string>
#include "global.h"
#include "Mode.h"

class I2CPreInit : public I2C
{
public:
    I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl)
    {
        frequency(400000);
        start();
    };
};


struct Display{
    Thread displayThread;
    
    // int optionIndex;
    
    Display();

    void start();
    void displayMain();
    void nextOption();
    void previousOption();
    int selectOption();
    void backToPrevious();
    // enum displayStage  {
    //     ModeSelection,
    //     PlayerNumSelection,
    //     CardNumSelection
    // };

    // displayStage currentStage;

    std::vector<std::string> ModeSelectionOptions = {"Manual", "Auto"};
    std::vector<std::string> PlayersNumOptions = {"2", "3", "4"};

    std::vector<std::string> twoPlayersCardNumOption = {"1", "2", "3", "4", "5", "6", "7", "8", "9", 
        "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27"};
    
    std::vector<std::string> threePlayersCardNumOption ={
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", 
        "17", "18"
    };

    std::vector<std::string> fourPlayersCardNumOption ={
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14"
    };


};


#endif