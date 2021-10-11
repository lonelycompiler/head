FILE="head.c"
EXECUTABLE="head"

head: head.h head.c
	gcc $(FILE) -o $(EXECUTABLE) -g -Wall