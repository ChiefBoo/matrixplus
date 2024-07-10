CC = gcc
CFLAGS = -std=c++17 -Wall -Werror -Wextra
GCOVFLAGS = -ftest-coverage -fprofile-arcs
TESTFLAGS = -lgtest -pthread

OS := $(shell uname)
ifeq ($(OS), Linux)
    TESTFLAGS += -lm -lrt -lsubunit -lpthread
endif

SOURCE = s21_*.cpp
HEADER = s21_*.h
OBJECTS= $(patsubst %.cpp, %.o, $(SOURCE))

TESTS_SOURCE = tests*.cpp
TESTS_OBJECTS = $(patsubst %.cpp, %.o, ${TESTS_SOURCE})


all: s21_matrix_oop.a gcov_report

s21_matrix_oop.a: $(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) -c $(SOURCE)
	ar rc s21_matrix_oop.a $(OBJECTS)
	ranlib s21_matrix_oop.a
	rm -rf *.o

test: s21_matrix_oop.a ${TESTS_SOURCE}
	$(CC) $(CFLAGS) ${TESTS_SOURCE} $(TESTFLAGS) s21_matrix_oop.a -lstdc++ -o unit_test
	./unit_test
	rm -rf *.o *.a unit_test

gcov_report: ${TESTS_SOURCE} $(SOURCE)
	$(CC) $(CFLAGS) $(GCOVFLAGS) ${TESTS_SOURCE} $(TESTFLAGS) $(SOURCE) -lstdc++ -o gcov_test
	./gcov_test
	lcov -t "gcov_test" -o test_report.info -c -d .
	genhtml -o report test_report.info
	rm -rf *.o *.gcno *.gcda *.info test
	open report/index.html

valgrind: s21_matrix_oop.a ${TESTS_SOURCE}
	$(CC) $(CFLAGS) ${TESTS_SOURCE} $(TESTFLAGS) s21_matrix_oop.a -lstdc++ -o test
	valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

style: clean
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n $(SOURCE) $(HEADER) ${TESTS_SOURCE}

leaks: s21_matrix_oop.a ${TESTS_SOURCE}
	$(CC) $(CFLAGS) ${TESTS_SOURCE} $(TESTFLAGS) s21_matrix_oop.a -lstdc++ -o test
	leaks -atExit -- ./test

clean:
	rm -rf *.o *.gcno *.a *.gcda
	rm -rf ./report/ *.info
	rm -rf test_report test unit_test gcov_test

rebuild:	clean all
