CC=cc
CXX=c++
CFLAGS=-Wall -Wextra -pedantic -Werror -fsanitize=undefined


options:
	@echo "CC=${CC}"
	@echo "CXX=${CXX}"
	@echo "CFLAGS=${CFLAGS}"


clean:
	rm -f test


test: test.c sar.c saru.c
	$(CC) test.c -o $@ $(CFLAGS) -std=c99
	./$@
	$(CXX) test.c -o $@ $(CFLAGS) -std=c++11
	./$@


.PHONY: clean options
