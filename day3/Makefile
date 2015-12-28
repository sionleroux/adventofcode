.PHONY: all clean run

all: bin/navigator run

run: bin/navigator
	./bin/navigator <input.txt

clean:
	rm -rf bin

bin/navigator: navigator.c house.c house.h bin
	gcc -Wall -o bin/navigator house.c navigator.c

bin:
	mkdir -p bin
