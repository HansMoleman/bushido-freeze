
all: main.o token.o
	gcc -Wall main.o token.o -o ghpat

ghpat.o: main.c
	gcc -Wall -c main.c

token.o: token.c
	gcc -Wall -c token.c


clean:
	rm *.o