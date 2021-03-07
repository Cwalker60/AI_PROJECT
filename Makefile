all: clean compile run

clean:
	rm -rf Backward.o Forward.o main.o

compile:
	g++ Backward.cpp Forward.cpp main.cpp -o main

run:
	./main


