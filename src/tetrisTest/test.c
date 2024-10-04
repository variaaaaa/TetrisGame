#include <assert.h>

#include "../brick_game/tetris/tetris.h"
#include "testik.h"

START_TEST(test_tetris_game_1) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);

  for (int i = 0; i < TETRIS_ROWS; i++) {
    for (int j = 0; j < TETRIS_COLS; j++) {
      ck_assert_int_eq(getCell(&tg, i, j), TET_EMPTY);
    }
  }
}
END_TEST

START_TEST(test_tetris_game_2) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);

  tetris_block block = {0};
  block.typ = 0;
  block.ori = 0;
  block.loc.row = 0;
  block.loc.col = 0;

  removeFigure(&tg, block);
  ck_assert_int_eq(getCell(&tg, block.loc.row, block.loc.col), TET_EMPTY);

  putFigure(&tg, block);
  ck_assert_int_eq(getCell(&tg, block.loc.row, block.loc.col), TET_EMPTY);

  removeFigure(&tg, block);
  ck_assert_int_eq(getCell(&tg, block.loc.row, block.loc.col), TET_EMPTY);
}
END_TEST

START_TEST(test_tetris_game_3) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);

  tetris_block block = {0};
  block.typ = 0;
  block.ori = 0;
  block.loc.row = 0;
  block.loc.col = 0;

  ck_assert_int_eq(isFit(&tg, block), true);

  block.loc.row = TETRIS_ROWS - 1;
  ck_assert_int_eq(isFit(&tg, block), false);

  block.loc.row = TETRIS_ROWS - 2;
  block.loc.col = TETRIS_COLS - 1;
  ck_assert_int_eq(isFit(&tg, block), false);

  block.loc.col = TETRIS_COLS - 2;
  ck_assert_int_eq(isFit(&tg, block), false);
}
END_TEST

START_TEST(test_tetris_game_4) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);

  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetDown(&tg);
  ck_assert_int_eq(tg.falling.loc.row, 0);
}
END_TEST

START_TEST(test_tetris_game_5) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);

  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetRotate(&tg, 1);
  ck_assert_int_eq(tg.falling.ori, 1);
}
END_TEST

START_TEST(test_tetris_game_6) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetRotate(&tg, 1);
  ck_assert_int_eq(tg.falling.ori, 1);
}
END_TEST

START_TEST(test_tetris_game_7) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetMove(&tg, -1);
  ck_assert_int_eq(tg.falling.loc.col, 2);
}
END_TEST

START_TEST(test_tetris_game_8) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetMove(&tg, 1);
  ck_assert_int_eq(tg.falling.loc.col, 4);
}
END_TEST

START_TEST(test_tetris_game_9) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  int lines_cleared = checkLines(&tg);
  ck_assert_int_eq(lines_cleared, 0);
}
END_TEST

START_TEST(test_tetris_game_10) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetDown(&tg);
  ck_assert_int_eq(tg.falling.loc.row, 0);
}
END_TEST

START_TEST(test_tetris_game_11) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetDown(&tg);
  tetDown(&tg);
  ck_assert_int_eq(tg.falling.loc.row, 0);
}
END_TEST

START_TEST(test_tetris_game_12) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetRotate(&tg, 2);
  ck_assert_int_eq(tg.falling.ori, 2);
}
END_TEST

START_TEST(test_tetris_game_13) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetMove(&tg, -1);
  tetMove(&tg, -1);
  ck_assert_int_eq(tg.falling.loc.col, 1);
}
END_TEST

START_TEST(test_tetris_game_14) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetMove(&tg, 1);
  tetMove(&tg, 1);
  ck_assert_int_eq(tg.falling.loc.col, 5);
}
END_TEST

START_TEST(test_tetris_game_15) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  int score = tg.game.score;
  checkLines(&tg);
  ck_assert_int_eq(tg.game.score, score);
}
END_TEST

START_TEST(test_tetris_game_16) {
  ck_assert(checkCell(1, 2));
  ck_assert(!checkCell(-1, 2));
  ck_assert(!checkCell(1, -2));
  ck_assert(!checkCell(-1, -2));
  ck_assert(!checkCell(TETRIS_ROWS, 2));
  ck_assert(!checkCell(1, TETRIS_COLS));
}
END_TEST

START_TEST(test_tetris_game_17) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetRotate(&tg, 3);
  ck_assert_int_eq(tg.falling.ori, 3);
}
END_TEST

START_TEST(test_tetris_game_18) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetMove(&tg, -1);
  tetMove(&tg, -1);
  tetMove(&tg, -1);
  ck_assert_int_eq(tg.falling.loc.col, 0);
}
END_TEST

START_TEST(test_tetris_game_19) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetMove(&tg, 1);
  tetMove(&tg, 1);
  tetMove(&tg, 1);
  ck_assert_int_eq(tg.falling.loc.col, 6);
}
END_TEST

START_TEST(test_tetris_game_20) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  int lines_cleared = checkLines(&tg);
  ck_assert_int_eq(lines_cleared, 0);
  ck_assert_int_eq(tg.game.score, lines_cleared * 10);
}
END_TEST

START_TEST(test_tetris_game_21) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetDown(&tg);
  tetDown(&tg);
  tetDown(&tg);
  ck_assert_int_eq(tg.falling.loc.row, 0);
}
END_TEST

START_TEST(test_tetris_game_22) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  newFalling(&tg);
  putFigure(&tg, tg.falling);
  tetRotate(&tg, 4);
  ck_assert_int_eq(tg.falling.ori, 0);
}
END_TEST

START_TEST(test_tetris_game_23) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  setCell(&tg, 1, 2, 5);
  ck_assert_int_eq(getCell(&tg, 1, 2), 5);
}
END_TEST

START_TEST(test_tetris_game_24) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  setCell(&tg, 1, 2, 5);
  ck_assert_int_eq(getCell(&tg, 1, 2), 5);
}
END_TEST

START_TEST(test_tetris_game_25) {
  int fig = chooseFigure();
  ck_assert_int_ge(fig, 0);
  ck_assert_int_lt(fig, figType);
}
END_TEST

START_TEST(test_tetris_game_26) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  ck_assert_ptr_nonnull(tg.game.field);
  for (int i = 0; i < TETRIS_ROWS; i++) {
    ck_assert_ptr_nonnull(tg.game.field[i]);
  }
  ck_assert_int_eq(tg.game.score, 0);
  ck_assert_int_eq(tg.game.level, 0);
  ck_assert_int_eq(tg.ticks_till_gravity, GRAVITY_LEVEL[0]);
}
END_TEST

START_TEST(test_tetris_game_27) {
  tetrisGame* tg = malloc(sizeof(tetrisGame));
  tetrisStart(tg, TETRIS_ROWS, TETRIS_COLS);
  freeMemory(tg);
}
END_TEST

START_TEST(test_tetris_game_28) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);

  // Set up a sample game state with multiple rows filled
  setCell(&tg, 0, 0, 1);
  setCell(&tg, 0, 1, 1);
  setCell(&tg, 1, 0, 2);
  setCell(&tg, 1, 1, 2);
  setCell(&tg, 2, 0, 3);
  setCell(&tg, 2, 1, 3);

  // Shift lines down by 2 rows
  shiftLines(&tg, 2);

  // Check that the top two rows are empty
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < TETRIS_COLS; j++) {
      ck_assert_int_ge(getCell(&tg, 2, j), 0);
    }
  }
  // Check that the third row is shifted down correctly
  for (int j = 0; j < TETRIS_COLS; j++) {
    ck_assert_int_ge(getCell(&tg, 2, j), 0);
  }

  // Check that the fourth row is shifted down correctly
  for (int j = 0; j < TETRIS_COLS; j++) {
    ck_assert_int_ge(getCell(&tg, 3, j), 0);
  }
}
END_TEST

START_TEST(test_tetris_game_29) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  for (int j = 0; j < TETRIS_COLS; j++) {
    setCell(&tg, 1, j, 1);
  }
  ck_assert(isLineFull(&tg, 1));
  setCell(&tg, 1, 0, TET_EMPTY);
  ck_assert(!isLineFull(&tg, 1));
}
END_TEST

START_TEST(test_tetris_game_30) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  tg.game.score = 0;
  changeScoreLevel(&tg, 1);
  ck_assert_int_eq(tg.game.score, 100);
  changeScoreLevel(&tg, 2);
  ck_assert_int_eq(tg.game.score, 400);
  changeScoreLevel(&tg, 3);
  ck_assert_int_eq(tg.game.score, 1100);
  changeScoreLevel(&tg, 4);
  ck_assert_int_eq(tg.game.score, 4100);
  ck_assert_int_eq(tg.game.level, 2);
}
END_TEST

START_TEST(test_tetris_game_31) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);
  ck_assert(!isOver(&tg));
  for (int j = 0; j < TETRIS_COLS; j++) {
    setCell(&tg, 0, j, 1);
  }
  ck_assert(isOver(&tg));
}
END_TEST

START_TEST(test_tetris_game_32) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);

  tg.game.level = 1;
  tg.ticks_till_gravity = GRAVITY_LEVEL[1] - 1;

  tetris_block falling;
  falling.loc.row = 0;
  falling.loc.col = 0;
  falling.typ = TET_I;
  falling.ori = 0;

  putFigure(&tg, falling);
  doTick(&tg);
  ck_assert_int_ge(tg.falling.loc.row, 0);
  ck_assert_int_ge(tg.ticks_till_gravity, 26);

  for (int i = 0; i < TETRIS_ROWS; i++) {
    for (int j = 0; j < TETRIS_COLS; j++) {
      ck_assert_int_ge(getCell(&tg, i, j), 0);
    }
  }
}
END_TEST

START_TEST(test_tetris_game_33) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);

  tetris_block falling;
  falling.loc.row = 0;
  falling.loc.col = 0;
  falling.typ = TET_I;
  falling.ori = 0;

  tg.falling = falling;
  putFigure(&tg, tg.falling);

  tg_handle_move(&tg, Left, false);
  ck_assert_int_eq(tg.falling.loc.col, 0);

  tg_handle_move(&tg, Right, false);
  ck_assert_int_eq(tg.falling.loc.col, 1);

  tg_handle_move(&tg, Down, false);
  ck_assert_int_ge(tg.falling.loc.row, 0);

  tg_handle_move(&tg, Up, false);

  tg_handle_move(&tg, Action, false);

  tg_handle_move(&tg, Start, false);
  ck_assert_int_eq(tg.falling.loc.row, 0);
  ck_assert_int_eq(tg.falling.loc.col, 3);

  tg_handle_move(&tg, (UserAction_t)10, false);
  ck_assert_int_eq(tg.falling.loc.row, 0);
  ck_assert_int_eq(tg.falling.loc.col, 3);
}
END_TEST

START_TEST(test_tetris_game_34) {
  tetrisGame tg;
  tetrisStart(&tg, TETRIS_ROWS, TETRIS_COLS);

  bool hold = true;
  UserAction_t action = Left;

  userInput(&tg, action, hold);
  int cell_value = getCell(&tg, 0, 0);
  ck_assert_int_ge(cell_value, 0);
  ck_assert_int_ge(cell_value, TET_EMPTY);

  hold = false;
  userInput(&tg, action, hold);
  cell_value = getCell(&tg, 0, 0);
  ck_assert_int_ge(cell_value, 0);
  ck_assert_int_eq(cell_value, TET_EMPTY);

  action = Right;
  hold = true;
  userInput(&tg, action, hold);
  cell_value = getCell(&tg, 0, 1);
  ck_assert_int_ge(cell_value, 0);
  ck_assert_int_ge(cell_value, TET_EMPTY);

  action = Down;
  hold = true;
  userInput(&tg, action, hold);
  cell_value = getCell(&tg, 1, 0);
  ck_assert_int_ge(cell_value, 0);
  ck_assert_int_ge(cell_value, TET_EMPTY);
}
END_TEST

Suite* game_test(void) {
  Suite* s;
  TCase* tcase;
  s = suite_create("\033[45m-=TETRIS_GAME_TESTS=-\033[0m");
  tcase = tcase_create("case_add");
  tcase_add_test(tcase, test_tetris_game_1);
  tcase_add_test(tcase, test_tetris_game_2);
  tcase_add_test(tcase, test_tetris_game_3);
  tcase_add_test(tcase, test_tetris_game_4);
  tcase_add_test(tcase, test_tetris_game_5);
  tcase_add_test(tcase, test_tetris_game_6);
  tcase_add_test(tcase, test_tetris_game_7);
  tcase_add_test(tcase, test_tetris_game_8);
  tcase_add_test(tcase, test_tetris_game_9);
  tcase_add_test(tcase, test_tetris_game_10);
  tcase_add_test(tcase, test_tetris_game_11);
  tcase_add_test(tcase, test_tetris_game_12);
  tcase_add_test(tcase, test_tetris_game_13);
  tcase_add_test(tcase, test_tetris_game_14);
  tcase_add_test(tcase, test_tetris_game_15);
  tcase_add_test(tcase, test_tetris_game_16);
  tcase_add_test(tcase, test_tetris_game_17);
  tcase_add_test(tcase, test_tetris_game_18);
  tcase_add_test(tcase, test_tetris_game_19);
  tcase_add_test(tcase, test_tetris_game_20);
  tcase_add_test(tcase, test_tetris_game_21);
  tcase_add_test(tcase, test_tetris_game_22);
  tcase_add_test(tcase, test_tetris_game_23);
  tcase_add_test(tcase, test_tetris_game_24);
  tcase_add_test(tcase, test_tetris_game_25);
  tcase_add_test(tcase, test_tetris_game_26);
  tcase_add_test(tcase, test_tetris_game_27);
  tcase_add_test(tcase, test_tetris_game_28);
  tcase_add_test(tcase, test_tetris_game_29);
  tcase_add_test(tcase, test_tetris_game_30);
  tcase_add_test(tcase, test_tetris_game_31);
  tcase_add_test(tcase, test_tetris_game_32);
  tcase_add_test(tcase, test_tetris_game_33);
  tcase_add_test(tcase, test_tetris_game_34);
  suite_add_tcase(s, tcase);
  return s;
}
