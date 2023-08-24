CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
GCOVFLAGS = -ftest-coverage -fprofile-arcs
TESTFLAGS = -lcheck

OS := $(shell uname)
ifeq ($(OS), Linux)
    TESTFLAGS += -lm -lrt -lsubunit -lpthread
endif

SOURCE = $(wildcard backend/*.c)
HEADER = $(wildcard backend/*.h)
OBJECTS= $(patsubst %.c, %.o, $(../SOURCE))

# TESTS_SOURCE = $(wildcard ./tests/test_*.c)
# TESTS_OBJECTS = $(patsubst ./tests/%.c, ./tests/%.o, ${TESTS_SOURCE})
# TESTS_HEADER = ./test/tests.h

all: smartcalc.a # gcov_report

smartcalc.a: $(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) -c $(SOURCE)
	ar rc smartcalc.a $(OBJECTS)
	ranlib smartcalc.a
# mv smartcalc.a ../frontend
	rm -rf *.o

build: smartcalc.a
	rm -rf build
	mkdir build
	cd build &&	cmake ../frontend
	cmake --build .

# test: smartcalc.a main.c ${TESTS_SOURCE} $(TESTS_HEADER)
# 	$(CC) $(CFLAGS) main.c ${TESTS_SOURCE} $(TESTFLAGS) s21_matrix.a -o atest
# 	./atest
# 	rm -rf *.o *.a atest

# gcov_report: main.c ${TESTS_SOURCE} $(TESTS_HEADER) $(SOURCE)
# 	$(CC) $(CFLAGS) $(GCOVFLAGS) main.c ${TESTS_SOURCE} $(TESTFLAGS) $(SOURCE) -o test
# 	./test
# 	lcov -t "test" -o test_report.info -c -d .
# 	genhtml -o report test_report.info
# 	rm -rf *.o *.gcno *.gcda *.info test

# open:
# 	open report/index.html

# valgrind: s21_matrix.a main.c ${TESTS_SOURCE} $(TESTS_HEADER)
# 	$(CC) $(CFLAGS) main.c ${TESTS_SOURCE} $(TESTFLAGS) s21_matrix.a -o test
# 	valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

# style: clean
# 	cp ../materials/linters/.clang-format .clang-format
# 	clang-format -n $(SOURCE) $(HEADER) ${TESTS_SOURCE} $(TESTS_HEADER) main.c

# leaks: s21_matrix.a main.c ${TESTS_SOURCE} $(TESTS_HEADER)
# 	$(CC) $(CFLAGS) main.c ${TESTS_SOURCE} $(TESTFLAGS) s21_matrix.a -o test
# 	leaks -atExit -- ./test

# clean:
# 	rm -rf *.o *.gcno *.a *.gcda
# 	rm -rf ./report/ *.info
# 	rm -rf test_report test

# rebuild:	clean all

