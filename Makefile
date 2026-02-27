CC = gcc

all: p1a p1b p1c p2a p2b p3

p1a: p1a.c
	$(CC) -fopenmp -o p1a p1a.c

p1b: p1b.c
	$(CC) -fopenmp -o p1b p1b.c

p1c: p1c.c
	$(CC) -fopenmp -o p1c p1c.c

p2a: p2a.c
	$(CC) -fopenmp -o p2a p2a.c

p2b: p2b.c
	$(CC) -fopenmp -o p2b p2b.c

p3: p3.c
	$(CC) -fopenmp -o p3 p3.c

clean:
	rm -f p1a p1b p1c p2a p2b p3
