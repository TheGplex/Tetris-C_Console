/*
 * Bolena
 * - HTL StP - Elektronik und technische Informatik
 * - 2CHELS  - Embedded
 * - Created: 01.01.2025
*/

#include "tetris.h"

int main(void) {
    while (true) {
        int gameField[ACTUAL_HEIGHT][FIELD_WIDTH];
        int lvl = 0;
        int score = 0;
        const time_t waitTime = introduction();

        figure fig;
        initGame(&fig, gameField);

        time_t oldTime = clock(), timer = clock(), addTime = 0, startT = clock(), currentTime = 0;
        bool down = false;
        bool gameOver = false;

        while (!gameOver) {
            if (clock() - oldTime >= waitTime || down) {
                down = false;
                oldTime = clock();
                addTime = handleGravity(&fig, gameField, &score, &lvl, &gameOver);
                startT += addTime;
            }
            if (gameOver) {
                break;
            }
            if (clock() - timer >= TIMER_UPDATE) {
                currentTime = clock() - startT;
                timer = clock();
                updateTimer(currentTime);
            }
            if (kbhit()) {
                handleInput(&fig, gameField, &down, &gameOver);
            }
        }

        if (!endMenu(currentTime, score, lvl)) {
            break;
        }
    }

    return 0;
}
