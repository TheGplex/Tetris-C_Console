/*
 * Bolena
 * - HTL StP - Elektronik und technische Informatik
 * - 2CHELS  - Embedded
 * - Created: 01.01.2025
*/

#ifndef TETRIS_H
#define TETRIS_H

/**************/

#include <time.h>
#include <stdbool.h>
#include "console.h"

/**************/

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define X_FACTOR 2

#define X_SHIFT 4
#define Y_SHIFT 3

#define FIGURE_SIZE 5
#define ACTUAL_HEIGHT (FIELD_HEIGHT + FIGURE_SIZE)
#define MARGIN_NEXT_FIELD 2
#define NOT_ROTATABLE_FIGS 1
#define SCORE_LINE 11
#define LEVEL_LINE 13
#define TIMER_LINE 15
#define END_MSG_LINE 17
#define LEVEL_BLINK 6
#define TIMER_UPDATE 10

#define MS_IN_S 1000
#define EASY_TIME 750
#define MEDIUM_TIME 500
#define HARD_TIME 250

#define BORDER_HORIZONTAL 205
#define BORDER_VERTICAL 186
#define LEFT_BOTTOM_CORNER 200
#define RIGHT_BOTTOM_CORNER 188
#define LEFT_TOP_CORNER 201
#define RIGHT_TOP_CORNER 187
#define BLOCK 219

#define NOT_POSSIBLE (-1)
#define FREE 0

#define I_C WHITE
#define O_C H_GREEN
#define T_C CYAN
#define L_C BLUE
#define J_C H_YELLOW
#define S_C MAGENTA
#define Z_C RED

/***************/

typedef struct figure {
    bool ableToRotate;
    int id;
    int nextID;
    int yPos;
    int ignorableRows;
    int addRight;
    int color;
    int shape[FIGURE_SIZE][FIGURE_SIZE];
} figure;


#define DIFFERENT_FIGURES 7
enum figures {
    I = 1, O, T, J, L, S, Z
};


enum directions {
    D_DOWN, D_LEFT, D_RIGHT
};

/***************/

void initGame(figure *f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]);
void drawMainField();
void drawNextField();
void gotoAdjXY(int x, int y);
void initFigure(figure *f);
void initGameField(int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]);
void isAbleToRotate(figure *f);
void fillShape(figure *f);
void rotateShape(figure *f);
void getIgnorableRows(figure *f);
void getFigureInGameField(figure *f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]);
void changeValueInGameField(int gameField[ACTUAL_HEIGHT][FIELD_WIDTH], int oldValue, int newValue, bool replaceAll);
int isMovePossible(figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH], int dir);
void move(figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH], int dir);
void printFigure(figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]);
void deleteFigure(figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]);
void setTextColor(figure *f);
int isRotationPossible(figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]);
int isGameOver(figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]);
void printNextFigure(figure f);
void handleCompletedRows(figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH], int *score, int *lvl);
void updateScore(int score);
void updateLvl(int lvl);
void updateTimer(time_t time);
void handleInput(figure *f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH], bool *down, bool *gameOver);
time_t handleGravity(figure *f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH], int *score, int *lvl, bool *gameOver);
time_t introduction();
int endMenu(time_t playedTime, int score, int lvl);


/***************/

#endif //TETRIS_H
