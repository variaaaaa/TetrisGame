CC=gcc
ADD_LIB=-lpthread -lcheck_pic -lrt -lm -lsubunit
SOURCES=$(shell find . -name "*.c")
OBJECTS=$(patsubst %.c, obj/%.o, $(SOURCES))

LIBS= -lncurses -lm
FRONTEND= gui/cli
BACKEND= brick_game/tetris
TEST_DIR= tetrisTest
CFLAGS= -Wall -Werror -Wextra -std=c11 -D_POSIX_C_SOURCE=200112L -fprofile-arcs -ftest-coverage
LFLAGS=-lncurses

.PHONY: all clean install uninstall dist test gcov_report

all: install

install: clean
	$(CC) $(CFLAGS) $(BACKEND)/*.c $(FRONTEND)/*.c $(LIBS) -o tetrisGame
	./tetrisGame

tetrisGame:
	./tetrisGame

style:
	clang-format -i -style=Google */*/*.c */*/*.h tetrisTest/*

clean:
	rm -rf obj/* tetrisGame
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css tests report *.txt test.info test.dSYM 


uninstall:
	rm -rf tetrisGame

test: clean
	$(CC) $(CFLAGS) $(BACKEND)/*.c $(TEST_DIR)/*.c -o tests $(ADD_LIB)
	./tests

gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
