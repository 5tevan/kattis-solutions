CC=g++
CFLAGS=-g -O2 -static -std=gnu++11

.cpp:
	$(CC) $(CFLAGS) $< -o $@.run

clean:
	rm -f *.run *~
