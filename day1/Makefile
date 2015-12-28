.PHONY: all clean run

all: bin/balanceBrackets bin/basementCounter run

clean:
	rm -rf bin

run: bin/balanceBrackets bin/basementCounter
	./bin/balanceBrackets
	./bin/basementCounter

bin/balanceBrackets: balanceBrackets.c bin
	gcc -Wall -o bin/balanceBrackets balanceBrackets.c

bin/basementCounter: basementCounter.c bin
	gcc -Wall -o bin/basementCounter basementCounter.c

bin:
	mkdir -p bin
