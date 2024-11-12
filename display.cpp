#include "display.h"
#include "global.h"


I2CPreInit gI2C(p28,p27);
Adafruit_SSD1306_I2c gOled2(gI2C,p30);

Display :: Display() : displayThread(osPriorityNormal, 1024){
    // optionIndex = 0;
    // currentStage = ModeSelection;
}

void Display::start(){
    gOled2.clearDisplay();
    displayThread.start(callback(this, &Display::displayMain));
}

void Display::displayMain(){
    while(1){
        if(currentMode == ModeSelection){
            gOled2.clearDisplay();
            gOled2.printf("Mode Select: %s \r", ModeSelectionOptions[displayOptionIndex].c_str());

            gOled2.display();
            ThisThread::sleep_for(200ms);
        }

        else if(currentMode == manual){
            gOled2.clearDisplay();
            gOled2.printf("Manual Mode \r");
            gOled2.display();
            ThisThread::sleep_for(700ms);
        }

        else if (currentMode == automaticPlayerSelection){
            gOled2.clearDisplay();
            gOled2.printf("Player Num: %s\r", PlayersNumOptions[displayOptionIndex].c_str());
            gOled2.display();
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
            ThisThread::sleep_for(200ms);
        }

        else if (currentMode == automatic){
            gOled2.clearDisplay();
            gOled2.printf("Auto Mode p:%d c:%d\r", playerNum, CardPerPile);

            gOled2.display();
            ThisThread::sleep_for(700ms);
        }
   
        
    }

 
}

void Display::nextOption(){
    displayOptionIndex += 1;
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

void Display::previousOption(){
    displayOptionIndex -= 1;
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

void Display::backToPrevious(){
    if(currentMode == manual 
        || currentMode == automaticPlayerSelection 
        || currentMode == automatiocCardSelection 
        || currentMode == automatic){
        currentMode = ModeSelection;
        displayOptionIndex = 0;
    }
}