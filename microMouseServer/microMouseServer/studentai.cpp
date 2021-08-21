
#include "micromouseserver.h"
#include <string>
#include <iostream>

using namespace std;
// ruhiyusuf

const int NROWS = 20;
const int NCOLS = 20;
const int OOBCOUNT = 65536; // error value for out of bounds visitCount
const bool DEBUG = false;

//-----------------------------------------------------------------------------
// void updateCurrentPos(char cMove, int cDirection, int &currentXPos, int &currentYPos, int visitCount[][NCOLS])
// Updates currentXPos and currentYPos based on cDirection and cMove.
// Once the new currentXPos and currentYPos are calculated, they are used as
// index values in the visitCount array to update number of times the mouse
// has visited that position.
//-----------------------------------------------------------------------------
void updateCurrentPos(char cMove, int cDirection, int &currentXPos, int &currentYPos, int visitCount[][NCOLS]) {
    // updates current x and y value of mouse
    switch(cDirection) {

    case 0: // North
        switch(cMove) {
        case 'f':
            currentYPos++;
            break;
        case 'r':
            currentXPos++;
            break;
        case 'l':
            currentXPos--;
            break;
        case 'b':
            currentYPos--;
            break;
        }

        break;

    case 1: // East
        switch(cMove) {
        case 'f':
            currentXPos++;
            break;
        case 'r':
            currentYPos--;
            break;
        case 'l':
            currentYPos++;
            break;
        case 'b':
            currentXPos--;
            break;
        }
        break;

    case 2: // South
        switch(cMove) {
        case 'f':
            currentYPos--;
            break;
        case 'r':
            currentXPos--;
            break;
        case 'l':
            currentXPos++;
            break;
        case 'b':
            currentYPos++;
            break;
        }
        break;

    case 3: // West
        switch(cMove) {
        case 'f':
            currentXPos--;
            break;
        case 'r':
            currentYPos++;
            break;
        case 'l':
            currentYPos--;
            break;
        case 'b':
            currentXPos++;
            break;
        }
        break;

    }

    visitCount[currentXPos][currentYPos] += 1;
}

//-----------------------------------------------------------------------------
// int numVisitCount(int cDirection, char cMove, int x, int y, int visitCount[][NCOLS])
// Returns number of times mouse has visited a destination location based on
// its current direction, (x, y) position, and desired move.
// If the destination location is out of bounds, return OOBCOUNT.
//-----------------------------------------------------------------------------
int numVisitCount(int cDirection, char cMove, int x, int y, int visitCount[][NCOLS]) {

    // mouse facing North
    if (cDirection == 0) {
        if (cMove == 'f') {
            y++;
        } else if (cMove == 'r') {
            x++;
        } else if (cMove == 'l') {
            x--;
        } else if (cMove == 'b') {
            y--;
        }
    }

    // mouse facing East
    if (cDirection == 1) {
        if (cMove == 'f') {
            x++;
        } else if (cMove == 'r') {
            y--;
        } else if (cMove == 'l') {
            y++;
        } else if (cMove == 'b') {
            x--;
        }
    }


    // mouse facing South
    if (cDirection == 2) {
        if (cMove == 'f') {
            y--;
        } else if (cMove == 'r') {
            x--;
        } else if (cMove == 'l') {
            x++;
        } else if (cMove == 'b') {
            y++;
        }
    }

    // mouse facing West
    if (cDirection == 3) {
        if (cMove == 'f') {
            x--;
        } else if (cMove == 'r') {
            y++;
        } else if (cMove == 'l') {
            y--;
        } else if (cMove == 'b') {
            x++;
        }
    }

    if  (x < 0 || x >= NCOLS || y < 0 || y >= NCOLS) {
        return OOBCOUNT; // out of bounds, invalid value
    }

    return visitCount[x][y];
}

//-----------------------------------------------------------------------------
// void printArray(int array[][NCOLS])
// Prints the cpp array in grid orientation
// (0, 0) is found on bottom left; (NROWS, NCOLS) is found at top right
//-----------------------------------------------------------------------------
void printArray(int array[][NCOLS]) {
    for (int i = NCOLS - 1; i >= 0; i--) {
        for (int j = 0; j < NROWS; j++) {
            cout << array[j][i] << "  ";
        }
        cout << endl;
    }
}

void recordTurnRight(int &nextDirection, char &currentMove, int &numLeftTurns) {
    nextDirection = (nextDirection + 1) % 4;
    currentMove = 'r';
    numLeftTurns = 0;
}

void recordTurnLeft(int &nextDirection, char &currentMove, int &numLeftTurns) {
    currentMove = 'l';
    numLeftTurns += 1;
    nextDirection = (nextDirection + 3) % 4;
}

void recordMoveForward(char &currentMove, int &numLeftTurns) {
    currentMove = 'f';
    numLeftTurns = 0;
}

void recordMoveBack(int &nextDirection, char &currentMove, int &numLeftTurns) {
    nextDirection = (nextDirection + 2) % 4;
    currentMove = 'b';
    numLeftTurns = 0;
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
    static int visitCount[NROWS][NCOLS];
    static int currentXPos = 0;
    static int currentYPos = 0;
    static bool startFlag = true;

    // use startFlag to initialize visitCount once at beginning of program
    if (startFlag) {
        memset(visitCount, 0, sizeof(visitCount[0][0]) * NROWS * NCOLS);
        visitCount[currentXPos][currentYPos] = 1;
        startFlag = false;
    }

    static char currentMove = 'z';
    static int numLeftTurns = 0; // tracks numLeftTurns to detect end of maze
    static int prevDirection = 0;
    static int nextDirection = 0;
    static int loopCount = 0;

    int numVisitedLeft, numVisitedRight, numVisitedFront;
    numVisitedLeft = numVisitCount(nextDirection, 'l', currentXPos, currentYPos, visitCount);
    numVisitedRight = numVisitCount(nextDirection, 'r', currentXPos, currentYPos, visitCount);
    numVisitedFront = numVisitCount(nextDirection, 'f', currentXPos, currentYPos, visitCount);

    if (DEBUG) {
        cout << "loopCount: " << loopCount << " ";
        cout << "Move: " << currentMove << " ";
        cout << "Direction: " << nextDirection << " ";
        cout << "x: " << currentXPos << " ";
        cout << "y: " << currentYPos << " ";
        cout << "current visitCount: " << visitCount[currentXPos][currentYPos] << "    ";
        cout << endl;

        cout << "numVisitedLeft: " << numVisitedLeft << " ";
        cout << "numVisitedRight: " << numVisitedRight << " ";
        cout << "numVisitedFront: " << numVisitedFront << " ";
        cout << endl;
        cout << endl;

        if (loopCount % 10 == 0) printArray(visitCount);
    }

    // check for alley way (surrounded by walls on right, left, and front)
    if (isWallRight() && isWallForward() && isWallLeft()) {
        turnRight();
        turnRight();
        recordMoveBack(nextDirection, currentMove, numLeftTurns);

    } else if (isWallForward() && isWallLeft()) {
        turnRight();
        recordTurnRight(nextDirection, currentMove, numLeftTurns);

    } else if (isWallForward() && isWallRight()) {
        turnLeft();
        recordTurnLeft(nextDirection, currentMove, numLeftTurns);

    } else {

        if (!isWallRight() && (numVisitedRight <= numVisitedFront) && (numVisitedRight <= numVisitedLeft)) {
           turnRight();
           recordTurnRight(nextDirection, currentMove, numLeftTurns);

       } else if (!isWallForward() && (numVisitedFront <= numVisitedLeft)) {
           recordMoveForward(currentMove, numLeftTurns);

       } else if (!isWallLeft()){
           turnLeft();
           recordTurnLeft(nextDirection, currentMove, numLeftTurns);
       } else {
           recordMoveForward(currentMove, numLeftTurns);
        }

    }

    if (!moveForward()) {
        cout << "ERROR: cannot move forward" << endl;
        foundFinish();
    }

    if (numLeftTurns == 3) {
        cout << endl;
        cout << "WE FOUND THE FINISH IN " << loopCount << " STEPS!!!!" << endl;
        foundFinish();
    }

    updateCurrentPos(currentMove, prevDirection, currentXPos, currentYPos, visitCount);

    if (currentXPos < 0 || currentYPos < 0 || currentXPos >= NROWS || currentYPos >= NCOLS) {
        cout << "ERROR: out of bounds x y" << endl;
        foundFinish();
    }
    prevDirection = nextDirection;
    loopCount++;
}
