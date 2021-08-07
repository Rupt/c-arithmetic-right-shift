CC=cc
CXX=c++
CFLAGS=-Wall -Wextra -pedantic -Werror \
	-fsanitize=undefined -fstrict-aliasing
TEMP=.clang_cpp_test.cpp


test: test.c sar.c saru.c
	$(CC) test.c -o $@ $(CFLAGS) -std=c99
	./$@
	$(CXX) -x c++ test.c -o $@ $(CFLAGS) -std=c++11
	./$@

options:
	@echo "CC=${CC}"
	@echo "CXX=${CXX}"
	@echo "CFLAGS=${CFLAGS}"


clean:
	rm -f test


.PHONY: clean options
