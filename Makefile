all: aes.o
	gcc main.c aes.o -o main

aes.o: aes.c aes.h helper.h
	gcc -c aes.c

clean:
	rm main *.o
