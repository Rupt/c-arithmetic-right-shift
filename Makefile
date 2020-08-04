CC=cc
CXX=c++
CFLAGS=-Wall -Wextra -pedantic -Werror


clean:
	rm -f test


test: test.c sar.c
	$(CC) test.c -o $@ $(CFLAGS) -std=c89
	./$@
	$(CC) test.c -o $@ $(CFLAGS) -std=c99
	./$@
	$(CXX) test.c -o $@ $(CFLAGS) -std=c++98
	./$@
	$(CXX) test.c -o $@ $(CFLAGS) -std=c++11
	./$@


.PHONY: clean test
