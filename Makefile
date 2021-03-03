all: clean compile run

compile: g++ Backward.cpp Forward.cpp main.cpp -o main

clean: rm -rf Backward.o Forward.o main.o

run: ./main


