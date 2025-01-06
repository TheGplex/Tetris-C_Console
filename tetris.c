/*
 * Bolena
 * - HTL StP - Elektronik und technische Informatik
 * - 2CHELS  - Embedded
 * - Created: 01.01.2025
*/

#include "tetris.h"
#include <stdio.h>
#include <time.h>

void initGame(figure *f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]) {
    srand(time(0));
    initConsole();
    textcolor(WHITE);
    textbackground(BLACK);
    gotoxy(0, 0);

    drawMainField();
    drawNextField();

    textcolor(BLUE);
    gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD) * X_FACTOR,  Y_SHIFT + SCORE_LINE);
    printf("Score: 0");
    textcolor(GREEN);
    gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD) * X_FACTOR,  Y_SHIFT + LEVEL_LINE);
    printf("Level: 0");
    gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD) * X_FACTOR,  Y_SHIFT + TIMER_LINE);
    textcolor(WHITE);
    printf("Timer: 0.00s");

    initGameField(gameField);
    f -> nextID = rand() % DIFFERENT_FIGURES + 1;
    initFigure(f);
    getFigureInGameField(f, gameField);
    printNextFigure(*f);
}



void drawMainField() {
    const char* word = "Tetris";
    for (int i = 0; i < strlen(word); i++) {
        textcolor(i + 1);
        gotoxy(X_SHIFT * X_FACTOR + FIELD_WIDTH + i - strlen(word) / 2, 1);
        printf("%c", word[i]);
    }
    textcolor(WHITE);


    for (int i = 0; i < FIELD_HEIGHT; i++) {
        gotoxy(X_SHIFT * X_FACTOR - 1, i + Y_SHIFT);
        printf("%c", BORDER_VERTICAL);
        gotoxy((X_SHIFT + FIELD_WIDTH ) * X_FACTOR, i + Y_SHIFT);
        printf("%c", BORDER_VERTICAL);
    }


    for (int i = 0; i < FIELD_WIDTH; i++) {
        gotoxy((X_SHIFT + i) * X_FACTOR, FIELD_HEIGHT + Y_SHIFT);
        printf("%c%c", BORDER_HORIZONTAL, BORDER_HORIZONTAL);
    }

    gotoxy(X_SHIFT * X_FACTOR - 1, FIELD_HEIGHT + Y_SHIFT);
    printf("%c", LEFT_BOTTOM_CORNER);

    gotoxy((X_SHIFT + FIELD_WIDTH) * X_FACTOR, FIELD_HEIGHT + Y_SHIFT);
    printf("%c", RIGHT_BOTTOM_CORNER);

    gotoxy((X_SHIFT + FIELD_WIDTH) * X_FACTOR,  Y_SHIFT);
    printf("%c", LEFT_TOP_CORNER);

    gotoxy(X_SHIFT * X_FACTOR - 1,  Y_SHIFT);
    printf("%c", RIGHT_TOP_CORNER);
}


void drawNextField() {
    textcolor(BLUE);
    gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD) * X_FACTOR + FIGURE_SIZE - strlen("Next") / 2 + 1,  1);
    printf("Next");
    textcolor(WHITE);

    for (int i = 0; i < FIGURE_SIZE; i++) {
        gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD) * X_FACTOR,  i + Y_SHIFT + 1);
        printf("%c", BORDER_VERTICAL);
        gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD + FIGURE_SIZE) * X_FACTOR + 1,  i + Y_SHIFT + 1);
        printf("%c", BORDER_VERTICAL);

        gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD + i) * X_FACTOR + 1,  Y_SHIFT);
        printf("%c%c", BORDER_HORIZONTAL, BORDER_HORIZONTAL);

        gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD + i) * X_FACTOR + 1,  Y_SHIFT + FIGURE_SIZE + 1);
        printf("%c%c", BORDER_HORIZONTAL, BORDER_HORIZONTAL);
    }

    gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD) * X_FACTOR,  Y_SHIFT);
    printf("%c", LEFT_TOP_CORNER);

    gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD + FIGURE_SIZE) * X_FACTOR + 1,  Y_SHIFT);
    printf("%c", RIGHT_TOP_CORNER);

    gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD) * X_FACTOR,  Y_SHIFT + FIGURE_SIZE + 1);
    printf("%c", LEFT_BOTTOM_CORNER);

    gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD + FIGURE_SIZE) * X_FACTOR + 1,  Y_SHIFT + FIGURE_SIZE + 1);
    printf("%c", RIGHT_BOTTOM_CORNER);
}


void gotoAdjXY(const int x, const int y) {
    gotoxy((x + X_SHIFT) * X_FACTOR, y + Y_SHIFT - FIGURE_SIZE);
}


void fillShape(figure *f) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
        for (int j = 0; j < FIGURE_SIZE; j++) {
            f -> shape[i][j] = FREE;
        }
    }

    switch (f -> id) {
        case I: f -> shape[4][2] = f -> id; f -> shape[3][2] = f -> id; f -> shape[2][2] = f -> id; f -> shape[1][2] = f -> id; break;
        case O: f -> shape[2][1] = f -> id; f -> shape[2][2] = f -> id; f -> shape[3][1] = f -> id; f -> shape[3][2] = f -> id; break;
        case T: f -> shape[2][2] = f -> id; f -> shape[1][1] = f -> id; f -> shape[1][2] = f -> id; f -> shape[1][3] = f -> id; break;
        case L: f -> shape[1][2] = f -> id; f -> shape[2][2] = f -> id; f -> shape[3][2] = f -> id; f -> shape[3][3] = f -> id; break;
        case J: f -> shape[1][2] = f -> id; f -> shape[2][2] = f -> id; f -> shape[3][2] = f -> id; f -> shape[3][1] = f -> id; break;
        case S: f -> shape[2][2] = f -> id; f -> shape[2][3] = f -> id; f -> shape[3][1] = f -> id; f -> shape[3][2] = f -> id; break;
        case Z: f -> shape[2][2] = f -> id; f -> shape[2][1] = f -> id; f -> shape[3][3] = f -> id; f -> shape[3][2] = f -> id; break;
        default: break;
    }

    getIgnorableRows(f);
}


void initFigure(figure *f) {
    f -> id = f -> nextID;
    f -> nextID = rand() % DIFFERENT_FIGURES + 1;
    f -> addRight = 0;
    setTextColor(f);
    fillShape(f);
    isAbleToRotate(f);
}


void initGameField(int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]) {
    for (int i = 0; i < ACTUAL_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            gameField[i][j] = FREE;
        }
    }
}


void isAbleToRotate(figure *f) {
    const int notAbleToRotate[NOT_ROTATABLE_FIGS] = {O};

    for (int i = 0; i < NOT_ROTATABLE_FIGS; i++) {
        if (notAbleToRotate[i] == f -> id) {
            f -> ableToRotate = false;
            return;
        }
    }

    f -> ableToRotate = true;
}


void rotateShape(figure *f) {
    int tempShape[FIGURE_SIZE][FIGURE_SIZE];

    for (int i = 0; i < FIGURE_SIZE; ++i) {
        for (int j = 0; j < FIGURE_SIZE; ++j) {
            tempShape[i][j] = f -> shape[j][FIGURE_SIZE - i - 1];
        }
    }

    for (int i = 0; i < FIGURE_SIZE; ++i) {
        for (int j = 0; j < FIGURE_SIZE; ++j) {
            f -> shape[i][j] = tempShape[i][j];
        }
    }

    getIgnorableRows(f);
}


void getIgnorableRows(figure *f) {
    f -> ignorableRows = 0;
    for (int i = FIGURE_SIZE - 1; i >= 0; i--) {
        bool freeRow = true;
        for (int j = 0; j < FIGURE_SIZE; j++) {
            if (f -> shape[i][j] != FREE)
                freeRow = false;
        }

        if (freeRow)
            f -> ignorableRows++;
        else
            break;
    }
}


void getFigureInGameField(figure *f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]) {
    const int shift = FIELD_WIDTH / 4 + 1;

    for (int i = 0; i < FIGURE_SIZE; i++) {
        for (int j = 0; j < FIGURE_SIZE; j++) {
            if (f -> shape[i][j] == f -> id)
                gameField[i + f -> ignorableRows][j + shift] = f -> shape[i][j];
        }
    }

    f -> yPos = -1;
}


void changeValueInGameField(int gameField[ACTUAL_HEIGHT][FIELD_WIDTH], const int oldValue, const int newValue, const bool replaceAll) {
    for (int i = 0; i < ACTUAL_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (replaceAll) {
                gameField[i][j] = newValue;
                continue;
            }
            if (gameField[i][j] == oldValue) {
                gameField[i][j] = newValue;
            }
        }
    }
}


int isMovePossible(const figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH], const int dir) {
    for (int i = ACTUAL_HEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (gameField[i][j] == f.id) {
                if ((dir == D_DOWN && i >= ACTUAL_HEIGHT - 1) || (dir == D_LEFT && j <= 0) || (dir == D_RIGHT && j >= FIELD_WIDTH - 1))
                    return false;
                if ((dir == D_DOWN && (gameField[i + 1][j] != f.id && gameField[i + 1][j] != FREE)) ||
                    (dir == D_LEFT && (gameField[i][j - 1] != f.id && gameField[i][j - 1] != FREE)) ||
                    (dir == D_RIGHT && (gameField[i][j + 1] != f.id && gameField[i][j + 1] != FREE))) {
                    return false;
                }
            }
        }
    }
    return true;
}


void move(const figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH], const int dir) {
    int outerLoopValue = 0, innerLoopValue = 0;
    bool outSmallerNormal = true, innerSmallerNormal = true;
    int outerLoopChange = 1, innerLoopChange = 1;
    int xChange = 0;
    int yChange = 0;


    switch (dir) {
        case D_DOWN: yChange = 1; outerLoopValue = ACTUAL_HEIGHT - 1; outSmallerNormal = false; outerLoopChange = -1; break;
        case D_LEFT: xChange = -1; break;
        case D_RIGHT: xChange = 1; innerLoopValue = FIELD_WIDTH - 1; innerSmallerNormal = false; innerLoopChange = -1; break;
        default: break;
    }

    for (int i = outerLoopValue; ; i += outerLoopChange) {
        if (!outSmallerNormal && i < 0)
            break;

        for (int j = innerLoopValue; ; j += innerLoopChange) {
            if (!innerSmallerNormal && j < 0)
                break;

            if (gameField[i][j] == f.id) {
                gameField[i + yChange][j + xChange] = f.id;
                gameField[i][j] = FREE;
            }

            if (innerSmallerNormal && j >= FIELD_WIDTH - 1)
                break;
        }

        if (outSmallerNormal && i >= ACTUAL_HEIGHT - 1)
            break;
    }
}


void printFigure(const figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]) {
    for (int i = FIGURE_SIZE; i < ACTUAL_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (gameField[i][j] == f.id) {
                gotoAdjXY(j, i);
                textcolor(f.color);
                printf("%c%c", BLOCK, BLOCK);
            }
        }
    }
}


void deleteFigure(const figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]) {
    for (int i = FIGURE_SIZE; i < ACTUAL_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (gameField[i][j] == f.id) {
                gotoAdjXY(j, i);
                printf("  ");
            }
        }
    }
}


void setTextColor(figure *f) {
    switch (f -> id) {
        case I: f -> color = I_C; break;
        case O: f -> color = O_C; break;
        case T: f -> color = T_C; break;
        case L: f -> color = L_C; break;
        case J: f -> color = J_C; break;
        case S: f -> color = S_C; break;
        case Z: f -> color = Z_C; break;
        default: f -> color = BLACK; break;
    }
}


int isRotationPossible(const figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]) {
    figure tempFigure = f;
    rotateShape(&tempFigure);

    const int shift = FIELD_WIDTH / 4 + 1;

    for (int i = 0; i < FIGURE_SIZE; i++) {
        for (int j = 0; j < FIGURE_SIZE; j++) {
            if (tempFigure.shape[i][j] == f.id) {
                const int yCoord = i + f.yPos + FIGURE_SIZE / 2;
                const int xCoord = j + shift + f.addRight;

                if (xCoord < 0 || xCoord >= FIELD_WIDTH || yCoord < 0 || yCoord >= ACTUAL_HEIGHT)
                    return false;

                const int gameFieldValue = gameField[yCoord][xCoord];
                if (gameFieldValue != FREE && gameFieldValue != f.id)
                    return false;
            }
        }
    }

    return true;
}


int isGameOver(const figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH]) {
    if (f.yPos < 0)
        return true;

    int partsInGameField = 0;

    for (int i = FIGURE_SIZE; i < ACTUAL_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (gameField[i][j] == f.id)
                partsInGameField++;
        }
    }

    int partsInShape = 0;

    for (int i = 0; i < FIGURE_SIZE; i++) {
        for (int j = 0; j < FIGURE_SIZE; j++) {
            if (f.shape[i][j] == f.id)
                partsInShape++;
        }
    }

    if (partsInGameField < partsInShape)
        return true;

    return false;
}


void printNextFigure(const figure f) {
    figure tempFig = f;

    tempFig.id = f.nextID;
    fillShape(&tempFig);
    setTextColor(&tempFig);

    textcolor(tempFig.color);

    for (int i = 0; i < FIGURE_SIZE; i++) {
        for (int j = 0; j < FIGURE_SIZE; j++) {
            gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD + j) * X_FACTOR + 1,  i + Y_SHIFT + 1);
            if (tempFig.shape[i][j] == tempFig.id)
                printf("%c%c", BLOCK, BLOCK);
            else
                printf("  ");
        }
    }
}


void handleCompletedRows(const figure f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH], int *score, int *lvl) {
    (*score)++;
    updateScore(*score);

    if (*score % 10 == 0 && *score != 0) {
        (*lvl)++;
        updateLvl(*lvl);
    }

    for (int i = FIGURE_SIZE; i < ACTUAL_HEIGHT; i++) {
        bool completeLine = true;
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (gameField[i][j] == FREE) {
                completeLine = false;
                break;
            }
        }

        if (completeLine) {
            for (int j = 0; j < FIELD_WIDTH; j++) {
                gotoAdjXY(j, i);
                printf("  ");
                delay(100);
            }

            for (int ii = i; ii > FIGURE_SIZE; ii--) {
                for (int j = 0; j < FIELD_WIDTH; j++) {
                    gameField[ii][j] = gameField[ii - 1][j];
                    figure fig = f;
                    fig.id = -gameField[ii][j];
                    setTextColor(&fig);
                    textcolor(fig.color);
                    gotoAdjXY(j, ii);
                    printf("%c%c", BLOCK, BLOCK);
                }
            }

            for (int j = 0; j < FIELD_WIDTH; j++) {
                gameField[FIGURE_SIZE][j] = FREE;
                gotoAdjXY(j, FIGURE_SIZE);
                printf("  ");
            }

            (*lvl)++;
            updateLvl(*lvl);
        }
    }
}


void updateScore(const int score) {
    gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD) * X_FACTOR,  Y_SHIFT + SCORE_LINE);
    textcolor(BLUE);
    printf("Score: %d", score);
}


void updateLvl(const int lvl) {
    gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD) * X_FACTOR,  Y_SHIFT + LEVEL_LINE);

    for (int i = 0; i < LEVEL_BLINK; i++) {
        if (i % 2 == 0)
            textcolor(BLACK);
        else
            textcolor(GREEN);

        gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD) * X_FACTOR,  Y_SHIFT + LEVEL_LINE);
        printf("Level: %d", lvl);
        delay(200);
    }
}


void updateTimer(const time_t time) {
    gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD) * X_FACTOR,  Y_SHIFT + TIMER_LINE);
    textcolor(WHITE);
    printf("Timer: %.2f \bs", (float) time / MS_IN_S);
}


void handleInput(figure *f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH], bool *down, bool *gameOver) {
    int key = getch();

    if (key == ESC) {
        *gameOver = true;
        return;
    }

    if (key == CURSOR) {
        key = getch();

        switch (key) {
            case LEFT: {
                if (isMovePossible(*f, gameField, D_LEFT)) {
                    deleteFigure(*f, gameField);
                    move(*f, gameField, D_LEFT);
                    printFigure(*f, gameField);
                    f -> addRight--;
                }
                break;
            }
            case RIGHT: {
                if (isMovePossible(*f, gameField, D_RIGHT)) {
                    deleteFigure(*f, gameField);
                    move(*f, gameField, D_RIGHT);
                    printFigure(*f, gameField);
                    f -> addRight++;
                }
                break;
            }
            case UP: {
                if (f -> ableToRotate && isRotationPossible(*f, gameField)) {
                    deleteFigure(*f, gameField);
                    changeValueInGameField(gameField, f -> id, FREE, false);
                    rotateShape(f);

                    const int shift = FIELD_WIDTH / 4 + 1;

                    for (int i = 0; i < FIGURE_SIZE; i++) {
                        for (int j = 0; j < FIGURE_SIZE; j++) {
                            if (f -> shape[i][j] == f -> id) {
                                gameField[i + f -> yPos + FIGURE_SIZE / 2][j + shift + f -> addRight] = f -> id;
                            }
                        }
                    }

                    printFigure(*f, gameField);
                }
                break;
            }
            case DOWN: {
                *down = true;
                break;
            }
            default: break;
        }
    }
}


time_t handleGravity(figure *f, int gameField[ACTUAL_HEIGHT][FIELD_WIDTH], int *score, int *lvl, bool *gameOver) {
    const time_t startTime = clock();
    if (isMovePossible(*f, gameField, D_DOWN)) {
        deleteFigure(*f, gameField);
        move(*f, gameField, D_DOWN);
        printFigure(*f, gameField);
        f -> yPos++;
    }
    else {
        if (isGameOver(*f, gameField)) {
            *gameOver = true;
            return clock() - startTime;
        }

        changeValueInGameField(gameField, f -> id, -f -> id, false);
        handleCompletedRows(*f, gameField, score, lvl);

        initFigure(f);
        getFigureInGameField(f, gameField);
        printNextFigure(*f);
    }

    return clock() - startTime;
}


time_t introduction() {
    clrscr();
    gotoxy(0, 0);
    textcolor(WHITE);
    setCursorType(0);

    printf("Welcome to Tetris\n");
    printf("Please select the difficulty:\n");
    printf("Easy - Press E\n");
    printf("Medium - Press M\n");
    printf("Hard - Press H\n");

    time_t retTime = 0;
    const int maxLen = strlen("Medium");
    char input[maxLen + 1];

    for (int i = 0; i < maxLen + 1; i++) {
        input[i] = '\0';
    }
    int key;

    while (retTime == 0) {
        key = getch();

        switch (key) {
            case 'e':
            case 'E': retTime = EASY_TIME; strcpy(input, "Easy"); break;
            case 'm':
            case 'M': retTime = MEDIUM_TIME; strcpy(input, "Medium"); break;
            case 'h':
            case 'H': retTime = HARD_TIME; strcpy(input, "Hard"); break;
            default: gotoxy(0, 7); printf("Invalid input - Please repeat"); break;
        }
    }

    clrscr();
    gotoxy(0, 0);

    printf("Selected difficulty: %s\n\n", input);
    printf("Quick Guide:\n");
    printf("Spin the figures by pressing the up arrow key\n");
    printf("Move the figures to the left and right by pressing the corresponding arrow keys\n");
    printf("By pressing the down arrow key, you can increase the falling speed\n\n");
    printf("If you manage it to fill an entire row, your level will increase\n");
    printf("With every figure, your score will increase, every ten score-increases, the level increases too\n");
    printf("The game is over if a figure doesn't fit entirely in the game field\n\n");
    printf("Press S to start the game");

    key = 0;
    while (key != 's' && key != 'S') {
        key = getch();
    }

    return retTime;
}


int endMenu(const time_t playedTime, const int score, const int lvl) {
    gotoxy((X_SHIFT + FIELD_WIDTH + MARGIN_NEXT_FIELD) * X_FACTOR,  Y_SHIFT + END_MSG_LINE);
    textcolor(RED);
    printf("GAME OVER - Press C to continue...");
    int key = getch();

    while (key != 'c' && key != 'C') {
        key = getch();
    }

    clrscr();
    gotoxy(0, 0);
    textcolor(WHITE);

    printf("Not bad - you reached level %d with a score of %d\n", lvl, score);
    printf("Your active play time (without delays) is %.2f \bs\n\n", (float) playedTime / MS_IN_S);
    printf("If you want to play again press A, if you want to quit press Q");

    key = getch();

    while (key != 'a' && key != 'A' && key != 'q' && key != 'Q') {
        key = getch();
    }

    return key == 'a' || key == 'A';
}
