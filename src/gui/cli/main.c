/* вся отрисовка тут */
#include "../../brick_game/tetris/tetris.h"

void displayBoard(WINDOW *w, tetrisGame *tg) {
  int i, j;
  box(w, 0, 0);
  for (i = 0; i < TETRIS_ROWS; i++) {
    wmove(w, 1 + i, 1);
    for (j = 0; j < TETRIS_COLS; j++) {
      if (getCell(tg, i, j) != TET_EMPTY) {
        addBlock(w, getCell(tg, i, j));
      } else {
        addEmpty(w);
      }
    }
  }
  wnoutrefresh(w);
}

void displayFigure(WINDOW *w, tetris_block block) {
  int b;
  tetris_location c;
  wclear(w);
  box(w, 0, 0);
  if (block.typ == -1) {
    wnoutrefresh(w);
    return;
  }
  for (b = 0; b < tetrisBlocks; b++) {
    c = figures[block.typ][block.ori][b];
    wmove(w, c.row + 1, c.col + 1);
    addBlock(w, (block.typ + 1));
  }
  wnoutrefresh(w);
}

void displayInfo(WINDOW *w, tetrisGame *tg) {
  wclear(w);
  wprintw(w, "Highscore\n");
  wprintw(w, "%d\n", tg->game.high_score);
  wprintw(w, "Score\n");
  wprintw(w, "%d\n", tg->game.score);
  wprintw(w, "Level\n");
  wprintw(w, "%d\n", tg->game.level);
  wnoutrefresh(w);
}

void colorFigures(void) {
  start_color();
  init_pair(TET_I, COLOR_RED, COLOR_BLACK);
  init_pair(TET_J, COLOR_WHITE, COLOR_BLACK);
  init_pair(TET_L, COLOR_YELLOW, COLOR_BLACK);
  init_pair(TET_Q, COLOR_RED, COLOR_WHITE);
  init_pair(TET_S, COLOR_GREEN, COLOR_BLACK);
  init_pair(TET_T, COLOR_BLUE, COLOR_BLACK);
  init_pair(TET_Z, COLOR_MAGENTA, COLOR_BLUE);
}

int main() {
  tetrisGame *tg = malloc(sizeof(tetrisGame));
  UserAction_t move = Start;
  bool running = true;
  WINDOW *board, *next, *score;

  tetrisStart(tg, TETRIS_ROWS, TETRIS_COLS);
  initscr();
  cbreak(); 
  noecho();          
  keypad(stdscr, TRUE); 
  timeout(0); 
  curs_set(0); 
  colorFigures();

  board = newwin(TETRIS_ROWS + 2, 2 * TETRIS_COLS + 2, 0, 0);
  next = newwin(6, 10, 0, 2 * (TETRIS_COLS + 1) + 1);
  score = newwin(6, 10, 14, 2 * (TETRIS_COLS + 1) + 1);

  while (running) {
    running = tetTick(tg, move);
    setHighScore(tg);
    displayBoard(board, tg);
    displayFigure(next, tg->next);
    updateHighScore(tg);
    updateCurrentState(tg);
    displayInfo(score, tg);
    doupdate();
    delayTime(5);

    switch (getch()) {
      case KEY_LEFT:
        move = Left;
        break;
      case KEY_RIGHT:
        move = Right;
        break;
      case KEY_UP:
        move = Up;
        break;
      case KEY_DOWN:
        move = Down;
        break;
      case 'q':
        running = false;
        move = Start;
        break;
      case 'p':
        wclear(board);
        box(board, 0, 0);
        wmove(board, TETRIS_ROWS / 2, TETRIS_COLS / 2);
        wprintw(board, "PAUSED");
        wrefresh(board);
        timeout(-1);
        getch();
        timeout(0);
        move = Start;
        break;
      default:
        move = Start;
    }
  }
  wclear(stdscr);
  endwin();

  printf("Game over!\n");
  printf("You finished with %d points on level %d.\n", tg->game.score,
         tg->game.level);
  freeMemory(tg);
  return 0;
}

void updateHighScore(tetrisGame *tg) {
  if (tg->game.score > tg->game.high_score) {
    tg->game.high_score = tg->game.score;
    FILE *file = fopen("BestScore", "w");
    if (file) {
      fprintf(file, "%d", tg->game.high_score);
      fclose(file);
    }
  }
}

void setHighScore(tetrisGame *tg) {
  FILE *file = fopen("BestScore", "r");
  if (file) {
    int high_score;
    if (fscanf(file, "%d", &high_score) == 1) {
      tg->game.high_score = high_score;
    }
    fclose(file);
  }
}

void addBlock(WINDOW *w, int x) {
  waddch(w, ' ' | A_REVERSE | COLOR_PAIR(x));
  waddch(w, ' ' | A_REVERSE | COLOR_PAIR(x));
}

void addEmpty(WINDOW *w) {
  waddch(w, ' ');
  waddch(w, ' ');
}

void delayTime(int milliseconds) {
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = milliseconds * 1000 * 1000;
  nanosleep(&ts, NULL);
}

GameInfo_t updateCurrentState(tetrisGame *tg) {
  GameInfo_t gameInfo;
  gameInfo.score = tg->game.score;
  gameInfo.level = tg->game.level;
  return gameInfo;
}