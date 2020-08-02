CC=cc
CFLAGS=-Wall -Wextra -pedantic -Werror -std=c89

clean:
	rm -f test-c

test: test.c sar.c
	$(CC) test.c -o $@ $(CFLAGS)
	./$@

.PHONY: clean
