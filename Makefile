CC=cc
CFLAGS=-Wall -Wextra -pedantic -Werror

clean:
	rm -f test

test: test.c sar.c
	$(CC) test.c -o $@ $(CFLAGS) -std=c89
	./$@
	$(CC) test.c -o $@ $(CFLAGS) -std=c99
	./$@

.PHONY: clean
