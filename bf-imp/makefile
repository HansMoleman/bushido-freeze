
all: cryptrand.o utilities.o
	gcc -Wall cryptrand.o utilities.o -o crand

cryptrand.o: cryptrand.c
	gcc -Wall -c cryptrand.c

utilities.o: utilities.c
	gcc -Wall -c utilities.c

clean:
	rm *.o
