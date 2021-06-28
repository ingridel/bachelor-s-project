all: aes.o key_expansion.o
	gcc aes_wrap.c aes.o key_expansion.o -o main

aes.o: aes.c aes.h helper.h unmasked_ops.h masked_ops.h
	gcc -c aes.c

key_expansion.o: key_expansion.c key_expansion.h
	gcc -c key_expansion.c

clean:
	rm main *.o
