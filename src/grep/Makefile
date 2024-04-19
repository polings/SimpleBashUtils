CC = gcc -Wall -Werror -Wextra
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	STD_FLAG = -std=c11
else
	STD_FLAG = -std=gnu11
endif

all: build

build: clean s21_grep 

s21_grep:
	$(CC) $(STD_FLAG) *.c -o s21_grep

clean: 
	@rm -rf s21_grep

rebuild: clean all

test: rebuild
	chmod +x tests/test_func_grep.sh
	sh tests/test_func_grep.sh

style: 
	clang-format -n -style=google *.c *.h

fix_style: 
	clang-format -i -style=google *.c *.h
