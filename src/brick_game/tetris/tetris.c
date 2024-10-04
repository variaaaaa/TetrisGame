/* вся логика тут */
#include "tetris.h"

/*
   [            фигура            ]
       [      ориентация      ]
             [координаты]
*/

tetris_location figures[figType][figOrientation][tetrisBlocks] = {
    // палочка (I)
    {{{1, 0}, {1, 1}, {1, 2}, {1, 3}},
     {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
     {{3, 0}, {3, 1}, {3, 2}, {3, 3}},
     {{0, 1}, {1, 1}, {2, 1}, {3, 1}}},
    // буква Г (J)
    {{{0, 0}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {2, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
     {{0, 1}, {1, 1}, {2, 1}, {2, 0}}},
    // та же фигура но зеркально (L)
    {{{0, 2}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
     {{0, 0}, {0, 1}, {1, 1}, {2, 1}}},
    // квадрат (Q)
    {{{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}}},
    // змейка (S)
    {{{0, 1}, {0, 2}, {1, 0}, {1, 1}},
     {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
     {{1, 1}, {1, 2}, {2, 0}, {2, 1}},
     {{0, 0}, {1, 0}, {1, 1}, {2, 1}}},
    // т (T)
    {{{0, 1}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {1, 2}, {2, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
     {{0, 1}, {1, 0}, {1, 1}, {2, 1}}},
    // змейка зеркально (Z)
    {{{0, 0}, {0, 1}, {1, 1}, {1, 2}},
     {{0, 2}, {1, 1}, {1, 2}, {2, 1}},
     {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
     {{0, 1}, {1, 0}, {1, 1}, {2, 0}}},
};

int GRAVITY_LEVEL[MAX_LEVEL] = {30, 28, 26, 24, 22, 20, 16, 14, 10, 8};

char getCell(tetrisGame *tg, int row, int column) {
  return tg->game.field[row][column];
}

void setCell(tetrisGame *tg, int row, int column, int value) {
  tg->game.field[row][column] = value;
}

bool checkCell(int row, int col) {
  return 0 <= row && row < TETRIS_ROWS && 0 <= col && col < TETRIS_COLS;
}

void putFigure(tetrisGame *tg, tetris_block block) {
  int i;
  for (i = 0; i < tetrisBlocks; i++) {
    tetris_location cell = figures[block.typ][block.ori][i];
    setCell(tg, block.loc.row + cell.row, block.loc.col + cell.col,
            (block.typ + 1));
  }
}

void removeFigure(tetrisGame *tg, tetris_block block) {
  int i;
  for (i = 0; i < tetrisBlocks; i++) {
    tetris_location cell = figures[block.typ][block.ori][i];
    setCell(tg, block.loc.row + cell.row, block.loc.col + cell.col, TET_EMPTY);
  }
}

bool isFit(tetrisGame *tg, tetris_block block) {
  int i, r, c;
  for (i = 0; i < tetrisBlocks; i++) {
    tetris_location cell = figures[block.typ][block.ori][i];
    r = block.loc.row + cell.row;
    c = block.loc.col + cell.col;
    if (!checkCell(r, c) || getCell(tg, r, c) != TET_EMPTY) {
      return false;
    }
  }
  return true;
}

int chooseFigure(void) { return rand() % figType; }

void newFalling(tetrisGame *tg) {
  tg->falling = tg->next;
  tg->next.typ = chooseFigure();
  tg->next.ori = 0;
  tg->next.loc.row = 0;
  tg->next.loc.col = TETRIS_COLS / 2 - 2;
}

void doTick(tetrisGame *tg) {
  tg->ticks_till_gravity--;
  if (tg->ticks_till_gravity <= 0) {
    removeFigure(tg, tg->falling);
    tg->falling.loc.row++;
    if (isFit(tg, tg->falling)) {
      tg->ticks_till_gravity = GRAVITY_LEVEL[tg->game.level];
    } else {
      tg->falling.loc.row--;
      putFigure(tg, tg->falling);

      newFalling(tg);
    }
    putFigure(tg, tg->falling);
  }
}

void tetMove(tetrisGame *tg, int direction) {
  removeFigure(tg, tg->falling);
  tg->falling.loc.col += direction;
  if (!isFit(tg, tg->falling)) {
    tg->falling.loc.col -= direction;
  }
  putFigure(tg, tg->falling);
}

void tetDown(tetrisGame *tg) {
  removeFigure(tg, tg->falling);
  while (isFit(tg, tg->falling)) {
    tg->falling.loc.row++;
  }
  tg->falling.loc.row--;
  putFigure(tg, tg->falling);
  newFalling(tg);
}

void tetRotate(tetrisGame *tg, int direction) {
  removeFigure(tg, tg->falling);

  while (true) {
    tg->falling.ori = (tg->falling.ori + direction) % figOrientation;
    if (isFit(tg, tg->falling)) break;
    tg->falling.loc.col--;
    if (isFit(tg, tg->falling)) break;
    tg->falling.loc.col += 2;
    if (isFit(tg, tg->falling)) break;
    tg->falling.loc.col--;
  }

  putFigure(tg, tg->falling);
}

void tg_handle_move(tetrisGame *tg, UserAction_t move, bool hold) {
  userInput(tg, move,
            hold);  
  switch (move) {
    case Left:
      tetMove(tg, -1);
      break;
    case Right:
      tetMove(tg, 1);
      break;
    case Down:
      tetDown(tg);
      break;
    case Up:
      tetRotate(tg, 1);
      break;
    case Action:
      tetRotate(tg, -1);
      break;
    case Start:
      break;
    default:
      break;
  }
}

void userInput(tetrisGame *tg, UserAction_t action, bool hold) {
  bool isHolding = false;
  UserAction_t heldAction = Action;
  if (hold && !isHolding) {
    isHolding = true;
    heldAction = action;
  } else if (!hold && isHolding) {
    isHolding = false;
    heldAction = action;
  }

  if (isHolding) {
    switch (heldAction) {
      case Left:
        tetMove(tg, -1);
        break;
      case Right:
        tetMove(tg, 1);
        break;
      case Down:
        tetDown(tg);
        break;
      default:
        break;
    }
  }
}

bool isLineFull(tetrisGame *tg, int i) {
  int j;
  for (j = 0; j < TETRIS_COLS; j++) {
    if (getCell(tg, i, j) == TET_EMPTY) return false;
  }
  return true;
}

void shiftLines(tetrisGame *tg, int r) {  // смещаем строки из за очищенной
  int i, j;
  for (i = r - 1; i >= 0; i--) {
    for (j = 0; j < TETRIS_COLS; j++) {
      setCell(tg, i + 1, j, getCell(tg, i, j));
      setCell(tg, i, j, TET_EMPTY);
    }
  }
}

int checkLines(tetrisGame *tg) {
  int i, nlines = 0;
  removeFigure(tg, tg->falling);

  for (i = TETRIS_ROWS - 1; i >= 0; i--) {
    if (isLineFull(tg, i)) {
      shiftLines(tg, i);
      i++;
      nlines++;
    }
  }
  putFigure(tg, tg->falling);
  return nlines;
}

void changeScoreLevel(tetrisGame *tg, int lines_cleared) {
  static int line_multiplier[] = {0, 100, 300, 700, 1500};
  int counter = 0;
  tg->game.score += line_multiplier[lines_cleared] * (tg->game.level + 1);
  counter += line_multiplier[lines_cleared] * (tg->game.level + 1);
  if (tg->game.level >= 10) {
    counter = 0;
  } else if (counter >= 600) {
    tg->game.level++;
    counter = 0;
  }
}

bool isOver(tetrisGame *tg) {
  int i, j;
  bool over = false;
  removeFigure(tg, tg->falling);
  for (i = 0; i < 2; i++) {
    for (j = 0; j < TETRIS_COLS; j++) {
      if (getCell(tg, i, j) != TET_EMPTY) {
        over = true;
      }
    }
  }
  putFigure(tg, tg->falling);
  return over;
}

bool tetTick(tetrisGame *tg, UserAction_t move) {
  int lines_cleared;
  doTick(tg);
  tg_handle_move(tg, move, false);
  lines_cleared = checkLines(tg);
  changeScoreLevel(tg, lines_cleared);
  return !isOver(tg);
}

void tetrisStart(tetrisGame *tg, int rows, int cols) {
  tg->game.field = malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++) {
    tg->game.field[i] = malloc(cols * sizeof(int));
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      setCell(tg, i, j, TET_EMPTY);
    }
  }
  tg->game.score = 0;
  tg->game.level = 0;
  tg->ticks_till_gravity = GRAVITY_LEVEL[tg->game.level];
  srand(time(NULL));
  newFalling(tg);
  newFalling(tg);
  tg->next.loc.col = TETRIS_COLS / 2 - 2;
  printf("%d", tg->falling.loc.col);
}

void freeMemory(tetrisGame *tg) {
  for (int i = 0; i < TETRIS_ROWS; i++) {
    free(tg->game.field[i]);
  }
  free(tg->game.field);
  free(tg);
}
