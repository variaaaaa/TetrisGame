
#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define tetrisBlocks 4
#define figType 7
#define figOrientation 4
#define MAX_LEVEL 10
#define TETRIS_ROWS 20
#define TETRIS_COLS 10

typedef enum {
  TET_EMPTY = 0,
  TET_I,
  TET_J,
  TET_L,
  TET_Q,
  TET_S,
  TET_T,
  TET_Z
} tetris_type;

typedef struct {
  int row;
  int col;
} tetris_location;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int typ;
  int ori;
  tetris_location loc;
} tetris_block;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  GameInfo_t game;
  tetris_block falling;
  tetris_block next;
  int ticks_till_gravity;
} tetrisGame;

extern tetris_location figures[figType][figOrientation][tetrisBlocks];
extern int GRAVITY_LEVEL[MAX_LEVEL];

void tetrisStart(tetrisGame *tg, int rows, int cols);
void freeMemory(tetrisGame *tg);
char getCell(tetrisGame *tg, int row, int col);
void setCell(tetrisGame *tg, int row, int column, int value);
bool checkCell(int row, int col);
bool tetTick(tetrisGame *tg, UserAction_t move);
void updateHighScore(tetrisGame *tg);
void setHighScore(tetrisGame *tg);
GameInfo_t updateCurrentState();
void delayTime(int milliseconds);
void addBlock(WINDOW *w, int x);
void addEmpty(WINDOW *w);
void tetRotate(tetrisGame *tg, int direction);
void newFalling(tetrisGame *tg);
void tetRotate(tetrisGame *tg, int direction);
void removeFigure(tetrisGame *tg, tetris_block block);
void putFigure(tetrisGame *tg, tetris_block block);
bool isFit(tetrisGame *tg, tetris_block block);
void tetDown(tetrisGame *tg);
void tetMove(tetrisGame *tg, int direction);
int checkLines(tetrisGame *tg);
int chooseFigure(void);
void shiftLines(tetrisGame *tg, int r);
bool isLineFull(tetrisGame *tg, int i);
bool isOver(tetrisGame *tg);
void changeScoreLevel(tetrisGame *tg, int lines_cleared);
void doTick(tetrisGame *tg);
void tg_handle_move(tetrisGame *tg, UserAction_t move, bool hold);
void userInput(tetrisGame *tg, UserAction_t action, bool hold);

#endif
