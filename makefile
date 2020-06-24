GCC=gcc
FLAGS=-g -Wall
SRC=test.c
OUT=hw4

.PHONY: single multi

single:
	$(GCC) $(FLAGS) $(SRC) -o $(OUT)

multi:
	$(GCC) $(FLAGS) -fopenmp $(SRC) -o $(OUT)
