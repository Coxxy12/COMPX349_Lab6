/* @source lab_6 ****************************************************
**
 * This lab will give you experience with threads and events. 
 * To do this you will build a very simple game.
 *
 * @author Copyright (C) 2022  Cameron.C
 * @version 1.0   __description of version__
 * @modified __EditDate__  __EditorName__  __description of edit__
 * @@
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
**
******************************************************************************/


/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

#include "MicroBit.h"
#include "Event.h"

/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

/* Game states */
typedef enum game {
    ACTIVE, 
    RESTART,
    GAME_OVER
} GAME;

/* Game bord */
const int leftBorder = 0;
const int rightBorder = 4;
const int topBorder = 0;
const int bottomBorder = 4;

/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Game specs */
int pixBlinkSpeed = 500;
int score = 0;
int revDirection = 1;

GAME state = ACTIVE;

/* Pixel Loc */
int pixelLocX = 2;
int pixelLocY = 0;

/* pixelBar */
int pixelBarLocX = 2;
int pixelBarLocY = bottomBorder;


/* ==================================================================== */
/* ============================== data ================================ */
/* ==================================================================== */

MicroBit uBit;

/* Messages */
ManagedString errorMessageGen("Sorry there is an error");
ManagedString errorButtonA("Error on A");
ManagedString errorButtonB("Error on B");
ManagedString errorButtonAB("Error on AB");
ManagedString gameOver("Game OVER, Score: ");
ManagedString restartMessage("Game Restarted");
ManagedString hit("Bar hit");

/* ==================================================================== */
/* ==================== function prototypes =========================== */
/* ==================================================================== */

void errorMessage(ManagedString message);
void onButton_A(MicroBitEvent);
void onButton_B(MicroBitEvent);
void onButton_AB(MicroBitEvent);
void pixelDisplay();
void pixelBarDisplay();
int barHit();
int pixFail();
void debugMessage(ManagedString msg);

/* @prog __lab_4 ****************************************************
**
 * Task 1:
 * Build a micro:bit application to move a pixel left and right 
 * across the display in response to button click events.
 * Task 2:
 * Add a thread to have a flashing pixel descend from the top of 
 * the display. You can randomly choose which column for it to descend 
 * using the int microbit_random(range) function.
 * Task 3:
 * Move the controlled pixel from part A to the bottom row. 
 * When the flashing pixel from part B reaches the bottom row check 
 * whether both pixels are in the same location. 
**
******************************************************************************/

int main() 
{
    /* Initialse Micro:Bit */
    uBit.init();
    uBit.display.setDisplayMode(DISPLAY_MODE_GREYSCALE);

    /* Listen for the button */
    uBit.messageBus.listen(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_CLICK, onButton_A);
    uBit.messageBus.listen(DEVICE_ID_BUTTON_B, DEVICE_BUTTON_EVT_CLICK, onButton_B);
    uBit.messageBus.listen(DEVICE_ID_BUTTON_AB, DEVICE_BUTTON_EVT_CLICK, onButton_AB);
    
    /* Create the various threads */
    create_fiber(pixelBarDisplay);
    create_fiber(pixelDisplay);
    
    release_fiber(); // Stops the program from quitting
}

/* ==================================================================== */
/* ============================ functions ============================= */
/* ==================================================================== */

/* Display error messages */
void errorMessage(ManagedString message) {
    uBit.display.scroll(message);
}

/* Function for button A */
void onButton_A(MicroBitEvent) {
    // errorMessage(errorButtonA);
    /* Move pix left */
    if (pixelBarLocX > leftBorder) {
        pixelBarLocX --;
        debugMessage(errorButtonA);
    }
}

/* Function for button B */
void onButton_B(MicroBitEvent) {
    // errorMessage(errorButtonB);
    /* Move pix right */
    if (pixelBarLocX < rightBorder) {
        pixelBarLocX ++;
        debugMessage(errorButtonB);
    }
}

/* Function for button AB */
void onButton_AB(MicroBitEvent) {
    // errorMessage(errorButtonAB);
    /* Restart the game */
    state = RESTART;
    debugMessage(errorButtonAB);
}

/* Function to display the "player" */
void pixelDisplay() {
    while(state == ACTIVE) {   
        /* Make the pix blink */
        uBit.display.image.setPixelValue(pixelLocX, pixelLocY, 255);
        uBit.sleep(pixBlinkSpeed);
        uBit.display.image.setPixelValue(pixelLocX, pixelLocY, 0);
        uBit.sleep(pixBlinkSpeed/5);
        
        /* Random X loc if at top border */
        if (pixelLocY < topBorder) {
            pixelLocX = microbit_random(5);
            revDirection *= -1;
        }
        
        /* If hit bar go back up */
        if (barHit()) {
            /* Increase hit rate by 1 */
            score ++;
            revDirection *= -1;
            pixBlinkSpeed -= 5;
            debugMessage(hit);
        }
        
        /* Check if pix hit the bottom */
        if (pixFail()) {
            state = GAME_OVER;
        }
        
        /* Update pixel Loc Y */
        pixelLocY += revDirection;
    }
}

/* Run game state */
void pixelBarDisplay() {
    /* Display the dottom bar */
    while(1) {
        switch (state) {
            /* Active state */
            case ACTIVE:
                /* Set the bottom bar */
                uBit.display.image.clear();
                uBit.display.image.setPixelValue(pixelBarLocX, pixelBarLocY, 255);
                uBit.sleep(pixBlinkSpeed);                       
                break;
            /* Restart state */
            case RESTART:
                errorMessage(restartMessage);
                debugMessage(restartMessage);
                /* Rest score */
                score = 0;
                /* Rest Bar Loc */
                pixelBarLocX = 2;
                pixelBarLocY = bottomBorder;
                /* Rest pix Loc */
                pixelLocX = 2;
                pixelLocY = 0;
                create_fiber(pixelDisplay);
                state = ACTIVE;
                break;
            /* Game Over state */
            case GAME_OVER:
                errorMessage(gameOver);
                errorMessage(score);
                debugMessage(gameOver);
                state = RESTART;
                break;
            /* Default case */
            default:
                break;           
        }
    }
}

/* Check if pix hits the bottom bar */
int barHit() {
    if ((pixelLocX == pixelBarLocX) && (pixelLocY == pixelBarLocY)) {
        return 1;
    }
    return 0;
}

/* Check if pix hits the bottom */
int pixFail() {
    if ((pixelLocX != pixelBarLocX) && (pixelLocY == bottomBorder)) {
        return 1;
    }
    return 0;
}

void debugMessage(ManagedString msg) {
    uBit.serial.send(msg + "\n\r");
}


