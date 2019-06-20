CC=gcc
CFLAGS=-g -march=native -pipe -Wall -Werror=array-bounds -Werror=format-overflow=0 -Werror=format -Werror=implicit-function-declaration -Werror=implicit-int -Werror=incompatible-pointer-types -Wno-comment -Wno-switch -Wno-unused-variable -Werror=address -Werror=int-conversion -fsanitize=undefined
objects = main.o aep.o http.o https.o smtp.o Includes/Brotli.o Includes/SixBit.o IntMsg.o Database.o

ae-mail: $(objects)
	$(CC) $(CFLAGS) -o ae-mail $(objects) -lsodium -lmbedtls -lmbedcrypto -lmbedx509 -lbrotlienc -lm -lsqlite3

main: main.c aep.h http.h https.h smpt.h

Includes/Brotli.o: Includes/Brotli.c
Includes/SixBit.o: Includes/SixBit.c

Database.o: Database.c
IntMsg.o: IntMsg.c
aep.o: aep.c
http.o: http.c
https.o: https.c Includes/SixBit.h Database.h IntMsg.h
smtp.o: smtp.c

.PHONY: clean
clean:
	-rm $(objects)
