CC=gcc
CFLAGS=-O3 -w
STYLE=-std=c99
EXE = bin_BAT_64128 bin_BAT_128128

all: $(EXE)

bin_BAT_128128: test_BAT_128128.c BAT128128.h
	$(CC) $(CFLAGS) test_BAT_128128.c -o $@

bin_BAT_64128: test_BAT_64128.c BAT64128.h
	$(CC) $(CFLAGS) test_BAT_64128.c -o $@

clean:
	@echo "cleaning..."
	@rm -r $(EXE) *.o 2> /dev/null || true
