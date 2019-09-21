CFLAGS = -g -Wall -pedantic -std=gnu99

all: morris

morris: morris.o util.o
	gcc -lm -o morris morris.o util.o $(CFLAGS)

morris.o: morris.c
	gcc -c morris.c $(CFLAGS)

util.o: util.c util.h
	gcc -c util.c  $(CFLAGS)

clean:
	rm *.o
