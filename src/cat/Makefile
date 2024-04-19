CC = gcc -Wall -Werror -Wextra -std=c11 

all: build

build: clean s21_cat

s21_cat:
	$(CC) *.c -o s21_cat

clean: 
	rm -rf s21_cat

rebuild: clean all

test: rebuild
	chmod +x tests/test_func_cat.sh
	sh tests/test_func_cat.sh

style: 
	clang-format -n -style=google *.c *.h

fix_style: 
	clang-format -i -style=google *.c *.h
