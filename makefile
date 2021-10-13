FILE="head.c"
EXECUTABLE="head"

head: src/head.h src/head.c
	gcc src/$(FILE) -o $(EXECUTABLE) -g -Wall -std=c11 -pedantic