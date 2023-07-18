PROJ=libgpiod-input
CC=cc
SRC=main.c
LIBS=-lgpiod
CFLAGS=-D CONSUMER=\"$(PROJ)\" -g -std=c11 

all:
	$(CC) $(SRC) $(LIBS) $(CFLAGS) -o $(PROJ)

clean:
	rm $(PROJ)
