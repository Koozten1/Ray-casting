all:
	gcc main.c -lncurses -lm

test:
	gcc test.c -lncurses -lm