CC=gcc
CFLAGS=-O3 -w
STYLE=-std=c99
EXE = bin_simon_64128 bin_simon_128128

all: $(EXE)

bin_simon_128128: test_simon_128128.c simon128128.h
	$(CC) $(CFLAGS) test_simon_128128.c -o $@

bin_simon_64128: test_simon_64128.c simon64128.h
	$(CC) $(CFLAGS) test_simon_64128.c -o $@

clean:
	@echo "cleaning..."
	@rm -r $(EXE) *.o 2> /dev/null || true
