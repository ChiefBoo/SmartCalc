CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
GCOVFLAGS = -ftest-coverage -fprofile-arcs
TESTFLAGS = -lcheck

OS := $(shell uname)
ifeq ($(OS), Linux)
    TESTFLAGS += -lm -lrt -lsubunit -lpthread
endif

SOURCE = $(wildcard ./backend/*.c)
HEADER = $(wildcard ./backend/*.h)
OBJECTS= $(patsubst %.c, %.o, $(../SOURCE))

TESTS_SOURCE = $(wildcard ./tests/tests/test_*.c)
TESTS_OBJECTS = $(patsubst ./tests/tests/%.c, .tests/tests/%.o, ${TESTS_SOURCE})
TESTS_HEADER = ./tests/test_includes/s21_tests.h


all: test gcov_report install dist

smartcalc.a: $(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) -c $(SOURCE)
	ar rc smartcalc.a $(OBJECTS)
	ranlib smartcalc.a
	rm -rf *.o

build: 
	cmake -S frontend/SmartCalc -B build
	make -C build

install: build
	mkdir SmartCalc_v1.0
	cp build/SmartCalc SmartCalc_v1.0/

uninstall:
	rm -rf SmartCalc_v1.0
	rm -rf build

dist:
	mkdir Archive_SmartCalc_v1.0
	cp Makefile -R tests -R backend -R frontend -R files Archive_SmartCalc_v1.0/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	rm -rf Archive_SmartCalc_v1.0

dvi: 
	#open files/readme.dvi
	open files/readme.pdf


test: ./tests/main_test.c ${TESTS_SOURCE} $(TESTS_HEADER)
	$(CC) $(CFLAGS) ./tests/main_test.c $(SOURCE) ${TESTS_SOURCE} $(TESTFLAGS) -o atest
	./atest
	rm -rf *.o *.a atest

gcov_report: ./tests/main_test.c ${TESTS_SOURCE} $(TESTS_HEADER) $(SOURCE)
	$(CC) $(CFLAGS) $(GCOVFLAGS) ./tests/main_test.c ${TESTS_SOURCE} $(TESTFLAGS) $(SOURCE) -o test
	./test
	lcov -t "test" -o test_report.info -c -d .
	genhtml -o report test_report.info
	rm -rf *.o *.gcno *.gcda *.info test

open:
	open report/index.html

valgrind: ./tests/main_test.c ${TESTS_SOURCE} $(TESTS_HEADER)
	$(CC) $(CFLAGS) ./tests/main_test.c $(SOURCE) ${TESTS_SOURCE} $(TESTFLAGS) -o test
	valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

style: clean
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n $(SOURCE) $(HEADER) ${TESTS_SOURCE} $(TESTS_HEADER) ./tests/main_test.c

leaks: ./tests/main_test.c ${TESTS_SOURCE} $(TESTS_HEADER)
	$(CC) $(CFLAGS) ./tests/main_test.c ${TESTS_SOURCE} $(TESTFLAGS) $(SOURCE) -o test
	leaks -atExit -- ./test

clean:
	rm -rf *.o *.gcno *.a *.gcda
	rm -rf ./report/ *.info
	rm -rf test_report test
	rm -rf build
	rm -rf Archive_SmartCalc_v1.0.tgz
	rm -rf SmartCalc_v1.0

rebuild: clean all

