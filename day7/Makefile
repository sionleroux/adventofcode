.PHONY: run

run: bin/circuit
	./bin/circuit <input.txt

bin/circuit: circuit.c
	mkdir -p bin
	ctags circuit.c
	gcc -Wall -o bin/circuit circuit.c
