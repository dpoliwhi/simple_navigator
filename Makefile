GXX=g++
FLAGS=-Wall -Wextra -Werror -std=c++17
TEST=-lgtest
OS=$(shell uname -s)
LINUX=-lrt -lpthread -lm -D_GNU_SOURCE
DIRBUILD=build/

all: s21_graph.a s21_graph_algorithms.a view

s21_graph.a: s21_graph.o
	ar rcs s21_graph.a s21_graph.o
	ranlib s21_graph.a

s21_graph.o:
	$(GXX) -c Model/s21_graph.cpp -o s21_graph.o

s21_graph_algorithms.a: s21_graph_algorithms.o
	ar rcs s21_graph_algorithms.a s21_graph_algorithms.o
	ranlib s21_graph_algorithms.a

s21_graph_algorithms.o:
	$(GXX) -c Model/s21_graph_algorithms.cpp -o s21_graph_algorithms.o

view:
	$(GXX) main.cpp */*.cpp -o run $(FLAGS)
	./run

test:
ifeq ($(OS), Darwin)
	$(GXX) test.cpp  Model/*.cpp Matrix/*.cpp -o test $(TEST) $(FLAGS)
	./test
else
	$(GXX) test.cpp  Model/*.cpp Matrix/*.cpp -o test $(TEST) $(LINUX) $(FLAGS)
	./test
endif

clean:
	rm -rf run test *.a *.o

check: cpplint test
	cppcheck --enable=all --suppress=missingInclude --suppress=unusedFunction --language=c++ Containers/*.* Matrix/*.* Model/*.* Interface/*.*
	# CK_FORK=no leaks --atExit -- ./test
	valgrind --leak-check=full --leak-resolution=med ./test

cpplint:
	cp -f linters/CPPLINT.cfg ./
	python3 linters/cpplint.py --extensions=cpp  Containers/*.* Matrix/*.* Model/*.* Interface/*.*
	rm -rf CPPLINT.cfg
