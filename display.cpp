#include "display.h"
#include "global.h"

///init I2C communication
I2CPreInit gI2C(p28,p27);
/// init display object
Adafruit_SSD1306_I2c gOled2(gI2C,p30);

///constructor, init thread objject
Display :: Display() : displayThread(osPriorityNormal, 1024){
}

/// Start thread
void Display::start(){
    gOled2.clearDisplay();
    displayThread.start(callback(this, &Display::displayMain));
}

///main function for display
///contents displayed is depended on system's current mode
void Display::displayMain(){
    while(1){
        if(currentMode == ModeSelection){
            gOled2.clearDisplay();
            gOled2.printf("Mode Select: %s \r", ModeSelectionOptions[displayOptionIndex].c_str());

            gOled2.display();
            /// Display do not need to refresh constantly
            ThisThread::sleep_for(200ms);
        }

        else if(currentMode == manual){
            gOled2.clearDisplay();
            gOled2.printf("Manual Mode \r");
            gOled2.display();
            /// Display do not need to refresh constantly
            ThisThread::sleep_for(700ms);
        }

        else if (currentMode == automaticPlayerSelection){
            gOled2.clearDisplay();
            gOled2.printf("Player Num: %s\r", PlayersNumOptions[displayOptionIndex].c_str());
            gOled2.display();
            /// Display do not need to refresh constantly
            ThisThread::sleep_for(200ms);
        }

        else if (currentMode == automatiocCardSelection){
            gOled2.clearDisplay();

            if(playerNum == 2){
                gOled2.printf("Card / pile: %s\r", twoPlayersCardNumOption[displayOptionIndex].c_str());
            }

            else if (playerNum == 3){
                gOled2.printf("Card / pile: %s\r", threePlayersCardNumOption[displayOptionIndex].c_str());

            }

            else if (playerNum == 4){
                gOled2.printf("Card / pile: %s\r", fourPlayersCardNumOption[displayOptionIndex].c_str());

            }

            gOled2.display();
            /// Display do not need to refresh constantly
            ThisThread::sleep_for(200ms);
        }

        else if (currentMode == automatic){
            gOled2.clearDisplay();
            gOled2.printf("Auto Mode p:%d c:%d\r", playerNum, CardPerPile);

            gOled2.display();
            /// Display do not need to refresh constantly
            ThisThread::sleep_for(700ms);
        }   
    }
}

///When next button is pressed, increment displayOptionIndex
///then content on display will change
void Display::nextOption(){
    displayOptionIndex += 1;
    
    ///if exceed the length of array, back to start
    if(currentMode == ModeSelection && displayOptionIndex > ModeSelectionOptions.size() - 1){
        displayOptionIndex = 0;
    }
    else if(currentMode == automaticPlayerSelection && displayOptionIndex > PlayersNumOptions.size() - 1){
        displayOptionIndex = 0;
    }
    else if(currentMode == automatiocCardSelection){
        if(playerNum == 2 && displayOptionIndex > twoPlayersCardNumOption.size() - 1){
            displayOptionIndex = 0;
        }
        else if (playerNum == 3 && displayOptionIndex > threePlayersCardNumOption.size() - 1){
            displayOptionIndex = 0;
        }
        else if(playerNum == 4 && displayOptionIndex > fourPlayersCardNumOption.size() - 1){
            displayOptionIndex = 0;
        }
    }
}

///When pervious button is pressed, decrement displayOptionIndex
///then content on display will change
void Display::previousOption(){
    displayOptionIndex -= 1;

    ///if less than the start of array, go to the end of array
    if(currentMode == ModeSelection && displayOptionIndex < 0){
        displayOptionIndex = ModeSelectionOptions.size() - 1;
    }
    else if (currentMode == automaticPlayerSelection && displayOptionIndex < 0){
        displayOptionIndex = PlayersNumOptions.size() - 1;
    }
    else if(currentMode == automatiocCardSelection){
        if(playerNum == 2 && displayOptionIndex < 0){
            displayOptionIndex = twoPlayersCardNumOption.size() - 1;
        }
        else if (playerNum == 3 && displayOptionIndex < 0){
            displayOptionIndex = threePlayersCardNumOption.size() - 1;
        }
        else if(playerNum == 4 && displayOptionIndex < 0){
            displayOptionIndex = fourPlayersCardNumOption.size() - 1;
        }
    }
} 

///When select button is pressed, determine which mode goes next
int Display::selectOption(){
    
    if(currentMode == ModeSelection ){
        if(displayOptionIndex == 0){
            currentMode = manual;
            return 0;
        }
        if(displayOptionIndex == 1){
            currentMode = automaticPlayerSelection;
            return 0;
        }
    }

    else if(currentMode == automaticPlayerSelection ){
        playerNum = displayOptionIndex + 2;
        currentMode = automatiocCardSelection;
        return displayOptionIndex + 2;
    }

    else if(currentMode == automatiocCardSelection){
        CardPerPile = displayOptionIndex + 1;
        currentMode = automatic;
        return displayOptionIndex + 1;
    }

    else if (currentMode == reset){
        currentMode = automatic;
        CardPerPile = displayOptionIndex + 1;
        return 0;
    }

    return 0;
} 

/// When back button is pressed, go back to mode selection mode
void Display::backToPrevious(){
    if(currentMode == manual 
        || currentMode == automaticPlayerSelection 
        || currentMode == automatiocCardSelection 
        || currentMode == automatic){
        currentMode = ModeSelection;
        displayOptionIndex = 0;
    }
}