CC = gcc
SRCS = main.c playlist.c album.c library.c 

run: main
	./main

main: $(SRCS)
	$(CC) $(SRCS) -o main