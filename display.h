#ifndef DISPLAY_H
#define DISPLAY_H

#include "Adafruit_SSD1306.h"/// imported libraryt for the display
#include "mbed.h"
#include <vector>
#include <string>
#include "global.h"
#include "Mode.h"


///For I2C comunication init
class I2CPreInit : public I2C
{
public:
    I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl)
    {
        frequency(400000);
        start();
    };
};

///Display struct
struct Display{
    /// Thread object
    Thread displayThread;

    ///constructor, init thread objject
    Display();

    /// Start thread
    void start();

    ///main function for display
    ///contents displayed is depended on system's current mode
    void displayMain();

    ///When next button is pressed, increment displayOptionIndex
    ///then content on display will change
    void nextOption();

    ///When pervious button is pressed, decrement displayOptionIndex
    ///then content on display will change
    void previousOption();

    ///When select button is pressed, determine which mode goes next
    int selectOption();

    /// When back button is pressed, go back to mode selection mode
    void backToPrevious();
   
    //array of options in mode selection stage
    std::vector<std::string> ModeSelectionOptions = {"Manual", "Auto"};

    //array of options in player selection stage
    std::vector<std::string> PlayersNumOptions = {"2", "3", "4"};

    //array of card number options in 2 player mode
    std::vector<std::string> twoPlayersCardNumOption = {"1", "2", "3", "4", "5", "6", "7", "8", "9", 
        "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27"};
    
    //array of card number options in 3 player mode
    std::vector<std::string> threePlayersCardNumOption ={
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", 
        "17", "18"
    };

    //array of card number options in 4 player mode
    std::vector<std::string> fourPlayersCardNumOption ={
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14"
    };


};


#endif