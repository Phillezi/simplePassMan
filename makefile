SRCDIR=./src
OUTDIR=./out
CC=gcc
CFLAGS = -g -c
LDFLAGS = -Wall -Werror -Wpedantic -lssl -lcrypto

# Determine the operating system
ifeq ($(OS),Windows_NT)
# Windows specific
	BIN_EXT =.exe
	LDFLAGS +=-lmingw32

else
# other os
	BIN_EXT =
	LDFLAGS +=-lm

endif

main:
	@echo Building main...
	$(CC) $(CFLAGS) $(SRCDIR)/AES.c
	$(CC) $(CFLAGS) $(SRCDIR)/base64.c
	$(CC) $(CFLAGS) $(SRCDIR)/main.c
	$(CC) AES.o base64.o main.o -o $(OUTDIR)/main$(BIN_EXT) $(LDFLAGS)
	@echo Building AES_Key_gen...
	$(CC) $(CFLAGS) $(SRCDIR)/AES_Key_gen.c
	$(CC) AES_Key_gen.o -o $(OUTDIR)/AES_Key_gen$(BIN_EXT) $(LDFLAGS)
	@echo Done Building!
	./out/main

clean:
	rm *.exe
	rm *.o