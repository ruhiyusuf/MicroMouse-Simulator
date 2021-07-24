
#include "micromouseserver.h"
#include <string>

// ruhiyusuf

const int NROWS = 20;
const int NCOLS = 20;


int visitCount[NROWS][NCOLS];
char move[NROWS][NCOLS];
bool arrayInitialized = false;

int currentXPos = 0;
int currentYPos = 0;

char currentMove = 'z';

bool turnFlag = false;

int leftTurns = 0;

int direction = 0;

void initializeArrays() {
    /* for (int i = 0; i < NROWS; i++) {
        for (int j = 0; j < NCOLS; j++) {
            visitCount[i][j] = 0;
            move[i][j] = 'z'; // 'z' represent invalid move
        }
    }

    visitCount[0][0] = 1; // initialize robot starting position at [0, 0] */

    memset(visitCount, 0, NROWS*NCOLS*sizeof(int));
    arrayInitialized = true;
}

void updateCurrentPos(char cMove, int cDirection) {
    if (currentXPos == 20 || currentYPos == 20) {
        int stuff = 1;
        stuff += 1;
    }
    if (cDirection == 0) { // North
        if (cMove == 'f') {
            currentYPos += 1;
        }
        if (cMove == 'r') {
            currentXPos += 1;
        }
        if (cMove == 'l') {
            currentXPos -= 1;
        }
        if (cMove == 'b') {
            currentYPos -= 1;
        }
    }

    if (cDirection == 1) { // East
        if (cMove == 'f') {
            currentXPos += 1;
        }
        if (cMove == 'r') {
            currentYPos -= 1;
        }
        if (cMove == 'l') {
            currentYPos += 1;
        }
        if (cMove == 'b') {
            currentXPos -= 1;
        }
    }

    if (cDirection == 2) { // South
        if (cMove == 'f') {
            currentYPos -= 1;
        }
        if (cMove == 'r') {
            currentXPos -= 1;
        }
        if (cMove == 'l') {
            currentXPos += 1;
        }
        if (cMove == 'b') {
            currentYPos += 1;
        }
    }

    if (cDirection == 3) { // West
        if (currentMove == 'f') {
            currentXPos -= 1;
        }
        if (currentMove == 'r') {
            currentYPos += 1;
        }
        if (currentMove == 'l') {
            currentYPos -= 1;
        }
        if (currentMove == 'b') {
            currentXPos += 1;
        }
    }

    visitCount[currentXPos][currentYPos] += 1;
    move[currentXPos][currentYPos] = cMove;
}

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


    turnFlag = false;
    if (!arrayInitialized) initializeArrays();

    if (!isWallRight()) {
        turnRight();
        direction = (direction + 1) % 4;
        turnFlag = true;

        currentMove = 'r';
        leftTurns = 0;

    } else if (isWallForward() && !isWallLeft()) {
        turnLeft();

        turnFlag = true;
        currentMove = 'l';

        leftTurns += 1;
        direction = (direction - 1 + 4) % 4;

    } else if (isWallForward() && isWallLeft() && isWallRight()) {
        turnRight();
        turnRight();

        direction = (direction + 2) % 4;

        turnFlag = true;
        currentMove = 'b';
        leftTurns = 0;
    }

    moveForward();
    if (!turnFlag) {
        currentMove = 'f';

        leftTurns = 0;
    }

    if (leftTurns == 3) {
        foundFinish();
    }

    printUI(QString::number(direction).toStdString().c_str());
    updateCurrentPos(currentMove, direction);
    printUI(QString::number(currentXPos).toStdString().c_str());
    printUI(QString::number(currentYPos).toStdString().c_str());

}
