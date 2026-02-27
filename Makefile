CC = gcc

all: p1a p1b p1c p2a p2b

p1a: p1a.c
	gcc -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp -o p1a p1a.c

p1b: p1b.c
	gcc -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp -o p1b p1b.c

p1c: p1c.c
	gcc -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp -o p1c p1c.c

p2a: p2a.c
	gcc -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp -o p2a p2a.c

p2b: p2b.c
	gcc -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp -o p2b p2b.c

p3: p3.c
	gcc -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp -o p3 p3.c

p3a: p3a.c
	gcc -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp -o p3a p3a.c

p3b: p3b.c
	gcc -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp -o p3b p3b.c

clean:
	rm -f p1a p1b p1c p2a p2b