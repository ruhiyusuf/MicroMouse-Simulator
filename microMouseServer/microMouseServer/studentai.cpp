
#include "micromouseserver.h"
#include <string>

const int NROWS = 20;
const int NCOLS = 20;


int visitCount[NROWS][NCOLS];
char move[NROWS][NCOLS];
bool arrayInitialized = false;

int currentXPos = 0;
int currentYPos = 0;

char currentMove = 'z';
int degree = 90;

void initializeArrays() {

    for (int i = 0; i < NROWS; i++) {
        for (int j = 0; j < NCOLS; j++) {
            visitCount[i][j] = 0;
            move[i][j] = 'z'; // 'z' represent invalid move
        }
    }

    visitCount[0][0] = 1; // initialize robot starting position at [0, 0]
    arrayInitialized = true;
}

void findFinish() {

}

/*void getCurrentMove(char moveChar) {
    char moveChar;

    switch(moveChar) {
    case 'r':
        turnRight();
    }
}*/

void microMouseServer::studentAI()
{
/*
 * The following are the eight functions that you can call. Feel free to create your own fuctions as well.
 * Remember that any solution that calls moveForward more than once per call of studentAI() will have points deducted.
 *
 *The following functions return if there is a wall in their respective directions
 *bool isWallLeft();
 *bool isWallRight();
 *bool isWallForward();
 *
 *The following functions move the mouse. Move forward returns if the mouse was able to move forward and can be used for error checking
 *bool moveForward();
 *void turnLeft();
 *void turnRight();
 *
 * The following functions are called when you need to output something to the UI or when you have finished the maze
 * void foundFinish();
 * void printUI(const char *mesg);
*/


    if (!arrayInitialized) initializeArrays();

    if (!isWallRight()) {
        turnRight();
        degree = degree - 90;

    } else if (isWallForward() && !isWallLeft()) {
        turnLeft();

        degree = degree + 90;
    } else if (isWallForward() && isWallLeft() && isWallRight()) {
        turnRight();
        turnRight();

        degree = degree + 180;
    }

    moveForward();

    // std::string msg = "Degree: " + std::to_string(degree);
    // printUI(msg);



    /*if (!isWallRight()) {
        currentMove = 'r';
    } else if (!isWallForward()) {
        currentMove = 'f';
    }
    else if (!isWallLeft()) {
        currentMove = 'l';
    } else {
        currentMove = 'b';
    }

    if currentMove = 'r'*/

}
