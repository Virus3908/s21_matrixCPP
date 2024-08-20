CC=g++
CFLAGS=-std=c++17 -Wall -Werror -Wextra
CLANG_FORMAT = ../materials/linters/.clang-format
OS = $(shell uname)

ifeq ("$(OS)","Linux")
	LEAKS_RUN_TEST = valgrind --tool=memcheck --leak-check=yes --log-file=1.txt
else
	LEAKS_RUN_TEST = leaks -atExit -- 
endif

OBJ = s21_matrix.o
TEST_OBJ = tests/tests.o
LIBFLAGS=-lgtest
GCOV_FLAG= --coverage

GCOV_OBJ = $(addprefix gcov_obj/,$(OBJ))

all: s21_matrix_oop.a

rebuild: clean all

s21_matrix_oop.a: $(OBJ)
	mkdir -p obj	
	ar -rcs $(@F) obj/$(<F)
	ranlib $(@F)

%.o: %.cpp
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o obj/$(@F)


test.exe: $(TEST_OBJ)
	$(CC) $(CFLAGS) obj/$(<F) -L. s21_matrix_oop.a -o test $(LIBFLAGS)

test: all test.exe
	./test

gcov_obj/%.o: %.cpp
	mkdir -p gcov_obj
	$(CC) $(CFLAGS) $(GCOV_FLAG) -c $< -o gcov_obj/$(@F)

gcov_report: clean gcov

leak_test: all test.exe
	$(LEAKS_RUN_TEST) ./test

gcov: $(TEST_OBJ) $(GCOV_OBJ)
	$(CC) $(CFLAGS) obj/$(<F) $(GCOV_OBJ) -o test $(LIBFLAGS) $(GCOV_FLAG)
	./test
	lcov -t "test" -o test.info -c -d ./ --no-external
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf obj/ *.o *.a *.out test report test.* gcov_obj

clang:
	clang-format --style=file:$(CLANG_FORMAT) -i *.cpp *.h ./*/*.cpp
	clang-format --style=file:$(CLANG_FORMAT) -n *.cpp *.h ./*/*.cpp

.PHONY: all clean test s21_matrix_oop.a gcov_report rebuild