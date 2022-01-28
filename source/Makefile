CC=g++
CFLAGS=-Wall -std=c++17 -O3
BINS=testSort test
all: clean test

test:
	$(CC) $(CFLAGS) -o testSort testSorting.cpp
	
clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)
