CC = gcc
CFLAGS =-I -Wall -g

paraphrace: main.c ntarray.c dictionary.c paraphrace.c macro.h
	$(CC) -o paraphrace main.c ntarray.c dictionary.c paraphrace.c $(CFLAGS)
