
#include "micromouseserver.h"
#include <string>
#include <iostream>

using namespace std;
// ruhiyusuf

const int NROWS = 20;
const int NCOLS = 20;
const int NDIRS = 4;

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

    switch(cDirection) {
        case 0:
            switch (cMove) {
                case 'f':
                    num = visitCount[x][y + 1];
                break;
                case 'r':
                    num = visitCount[x + 1][y];
                    break;
                case 'l':
                    num = visitCount[x - 1][y];
                    break;
                case 'b':
                    num = visitCount[x][y - 1];
                    break;

            }
            break;
        case 1:
            switch (cMove) {
                case 'f':
                    num = visitCount[x + 1][y];
                    break;
                case 'r':
                    num = visitCount[x][y - 1];
                    break;
                case 'l':
                    num = visitCount[x][y + 1];
                    break;
                case 'b':
                    num = visitCount[x - 1][y];
                    break;

            }
            break;
        case 2:
            switch (cMove) {
                case 'f':
                    num = visitCount[x][y - 1];
                    break;
                case 'r':
                    num = visitCount[x - 1][y];
                    break;
                case 'l':
                    num = visitCount[x + 1][y];
                    break;
                case 'b':
                    num = visitCount[x][y + 1];
                    break;

            }
            break;
        case 3:
            switch (cMove) {
                case 'f':
                    num = visitCount[x - 1][y];
                    break;
                case 'r':
                    num = visitCount[x][y + 1];
                    break;
                case 'l':
                    num = visitCount[x][y - 1];
                    break;
                case 'b':
                    num = visitCount[x + 1][y];
                    break;

            }
            break;

    }

    return num;
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
    static int moveCount[NROWS][NCOLS][NDIRS];

    static int currentXPos = 0;
    static int currentYPos = 0;

    static int prevXPos = 0;
    static int prevYPos = 0;

    static bool startFlag = true;

    if (startFlag) {
        memset(visitCount, 0, sizeof(visitCount[0][0]) * NROWS * NCOLS);
        memset(moveCount, 0, sizeof(moveCount[0][0][0]) * NROWS * NCOLS * NDIRS);
        visitCount[currentXPos][currentYPos] = 1;
        startFlag = false;
    }

    static char currentMove = 'z';

    static bool turnFlag = false;

    static int leftTurns = 0;

    static int prevDirection = 0;
    static int nextDirection = 0;

    moveCount[currentXPos][currentYPos][nextDirection] += 1;


    turnFlag = false;

    cout << "Move: " << currentMove << " ";
    cout << "Direction: " << nextDirection << " ";
    cout << "x: " << currentXPos << " ";
    cout << "y: " << currentYPos << " ";
    cout << "visitCount: " << visitCount[currentXPos][currentYPos] << "    ";
    // cout << "moveCount (front, 0): " << moveCount[currentXPos][currentYPos][0] << "      ";
    // cout << "moveCount (right, 1): " << moveCount[currentXPos][currentYPos][1] << "      ";
    // cout << "moveCount (back, 2): " << moveCount[currentXPos][currentYPos][2] << "      ";
    // cout << "moveCount (left, 3): " << moveCount[currentXPos][currentYPos][3] << "      ";
    // cout << endl;
    char test = numVisitCount(nextDirection, 'f', currentXPos, currentYPos, visitCount);
    cout << test << endl;
    cout << endl;
//  && updateDirFreq(nextDirection, currentXPos, currentYPos, visitCount)
    if (!isWallRight() && (numVisitCount(nextDirection, 'r', currentXPos, currentYPos, visitCount) < numVisitCount(nextDirection, 'f', currentXPos, currentYPos, visitCount)) && (numVisitCount(nextDirection, 'r', currentXPos, currentYPos, visitCount) < numVisitCount(nextDirection, 'l', currentXPos, currentYPos, visitCount))) {
        turnRight();
        nextDirection = (nextDirection + 1) % 4;
        turnFlag = true;

        currentMove = 'r';
        leftTurns = 0;

    } else if (!isWallForward() && (numVisitCount(nextDirection, 'f', currentXPos, currentYPos, visitCount) < numVisitCount(nextDirection, 'l', currentXPos, currentYPos, visitCount))) {
        currentMove = 'f';
        leftTurns = 0;

    } else if (!isWallLeft() && (numVisitCount(nextDirection, 'l', currentXPos, currentYPos, visitCount) < numVisitCount(nextDirection, 'b', currentXPos, currentYPos, visitCount))) {

        turnLeft();

        turnFlag = true;
        currentMove = 'l';

        leftTurns += 1;
        nextDirection = (nextDirection + 3) % 4;

    } else {
        turnRight();
        turnRight();

        nextDirection = (nextDirection + 2) % 4;

        turnFlag = true;
        currentMove = 'b';
        leftTurns = 0;
    }

    moveForward();

    if (leftTurns == 3) {
        foundFinish();
    }


/*
    cout << "prev currentXPos: " << currentXPos << " ";
    cout << "prev currentYPos: " << currentYPos << " ";
    cout << "------" << endl;
*/
    updateCurrentPos(currentMove, prevDirection, currentXPos, currentYPos, visitCount);
/*    cout << "after currentXPos: " << currentXPos << " ";
    cout << "after currentYPos: " << currentYPos << " ";
    cout << "------" << endl;



    cout << "prevDirection: " << prevDirection << endl;
    cout << "nextDirection: " << nextDirection << endl;
*/
    prevDirection = nextDirection;
    prevXPos = currentXPos;
    prevYPos = currentYPos;
}
