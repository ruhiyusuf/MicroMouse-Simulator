
#include "micromouseserver.h"
#include <string>
#include <iostream>

using namespace std;
// ruhiyusuf

const int NROWS = 20;
const int NCOLS = 20;

void updateCurrentPos(char cMove, int cDirection, int &currentXPos, int &currentYPos, int visitCount[][NCOLS]) {

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

int numVisitCount(int cDirection, char cMove, int x, int y, int visitCount[][NCOLS]){
    int num = 0;


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
        return 65536; // out of bounds, invalid value
    }

    return visitCount[x][y];
}
char updateDirFreq(int cDirection, int x, int y, int visitCount[][NCOLS]){
    switch (cDirection) {
        case 0:
            if ((visitCount[x + 1][y] < visitCount[x][y + 1]) && (visitCount[x + 1][y] < visitCount[x - 1][y]) && (visitCount[x + 1][y] < visitCount[x][y - 1])) {
                return 'r';
            } else if ((visitCount[x][y + 1] < visitCount[x - 1][y]) && (visitCount[x][y + 1] < visitCount[x][y - 1])){
                return 'f';
            } else if (visitCount[x - 1][y] < visitCount[x][y - 1]) {
                return 'l';
            } else {
                return 'b';
            }
        case 1:
            if ((visitCount[x][y - 1] < visitCount[x + 1][y]) && (visitCount[x][y - 1] < visitCount[x][y + 1]) && (visitCount[x][y - 1] < visitCount[x - 1][y])) {
                return 'r';
            } else if ((visitCount[x + 1][y] < visitCount[x][y + 1]) && (visitCount[x + 1][y] < visitCount[x - 1][y])){
                return 'f';
            } else if (visitCount[x][y + 1] < visitCount[x - 1][y]) {
                return 'l';
            } else {
                return 'b';
            }
        case 2:
            if ((visitCount[x - 1][y] < visitCount[x][y - 1]) && (visitCount[x - 1][y] < visitCount[x + 1][y]) && (visitCount[x - 1][y] < visitCount[x][y + 1])) {
                return 'r';
            } else if ((visitCount[x][y - 1] < visitCount[x + 1][y]) && (visitCount[x][y - 1] < visitCount[x][y + 1])){
                return 'f';
            } else if (visitCount[x + 1][y] < visitCount[x][y + 1]) {
                return 'l';
            } else {
                return 'b';
            }
        case 3:
            if ((visitCount[x][y + 1] < visitCount[x - 1][y]) && (visitCount[x][y + 1] < visitCount[x][y - 1]) && (visitCount[x][y + 1] < visitCount[x + 1][y])) {
                return 'r';
            } else if ((visitCount[x - 1][y] < visitCount[x][y - 1]) && (visitCount[x - 1][y] < visitCount[x + 1][y])){
                return 'f';
            } else if (visitCount[x][y - 1] < visitCount[x + 1][y]) {
                return 'l';
            } else {
                return 'b';
            }
        default:
            return 'z';

    }

}

void printArray(int array[][NCOLS]) {
    for (int i = NCOLS - 1; i >= 0; i--) {
        for (int j = 0; j < NROWS; j++) {
            cout << array[j][i] << "  ";
        }
        cout << endl;
    }

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

    if (startFlag) {
        memset(visitCount, 0, sizeof(visitCount[0][0]) * NROWS * NCOLS);
        visitCount[currentXPos][currentYPos] = 1;
        startFlag = false;
    }

    static char currentMove = 'z';
    static int numLeftTurns = 0;
    static int prevDirection = 0;
    static int nextDirection = 0;
    static int loopCount = 0;


    cout << "loopCount: " << loopCount << " ";
    cout << "Move: " << currentMove << " ";
    cout << "Direction: " << nextDirection << " ";
    cout << "x: " << currentXPos << " ";
    cout << "y: " << currentYPos << " ";
    cout << "current visitCount: " << visitCount[currentXPos][currentYPos] << "    ";
    cout << endl;

    int numVisitedLeft, numVisitedRight, numVisitedFront;
    numVisitedLeft = numVisitCount(nextDirection, 'l', currentXPos, currentYPos, visitCount);
    numVisitedRight = numVisitCount(nextDirection, 'r', currentXPos, currentYPos, visitCount);
    numVisitedFront = numVisitCount(nextDirection, 'f', currentXPos, currentYPos, visitCount);


    cout << "numVisitedLeft: " << numVisitedLeft << " ";
    cout << "numVisitedRight: " << numVisitedRight << " ";
    cout << "numVisitedFront: " << numVisitedFront << " ";
    cout << endl;
    cout << endl;

    if (loopCount % 10 == 0) printArray(visitCount);

    // check for alley way (surrounded by walls on right, left, and front)
    if (isWallRight() && isWallForward() && isWallLeft()) {
           turnRight();
           turnRight();
           nextDirection = (nextDirection + 2) % 4;
           currentMove = 'b';
           numLeftTurns = 0;

       } else if (isWallForward() && isWallLeft()) {
        turnRight();
        nextDirection = (nextDirection + 1) % 4;
        currentMove = 'r';
        numLeftTurns = 0;
    } else if (isWallForward() && isWallRight()) {
        turnLeft();
        currentMove = 'l';
        numLeftTurns += 1;
        nextDirection = (nextDirection + 3) % 4;
    }

    else {

        if (!isWallRight() && (numVisitedRight <= numVisitedFront) && (numVisitedRight <= numVisitedLeft)) {
           turnRight();
           nextDirection = (nextDirection + 1) % 4;
           currentMove = 'r';
           numLeftTurns = 0;

       } else if (!isWallForward() && (numVisitedFront <= numVisitedLeft)) {
           currentMove = 'f';
           numLeftTurns = 0;

       } else if (!isWallLeft()){
           turnLeft();
           currentMove = 'l';
           numLeftTurns += 1;
           nextDirection = (nextDirection + 3) % 4;
       } else {
            cout << "why are we here" << endl;
            currentMove = 'f';
            numLeftTurns = 0;
        }

    }

    if (!moveForward()) {
        cout << "cannot move forward" << endl;
        foundFinish();
    }

    if (numLeftTurns == 3) {
        cout << endl;
        cout << "WE FOUND THE FINISH" << endl;
        foundFinish();
    }

    updateCurrentPos(currentMove, prevDirection, currentXPos, currentYPos, visitCount);

    if (currentXPos < 0 || currentYPos < 0 || currentXPos >= NROWS || currentYPos >= NCOLS) {
        cout << "error, out of bounds x y" << endl;
        foundFinish();
    }
    prevDirection = nextDirection;
    loopCount++;
}
