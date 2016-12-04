.PHONY: run

run: bin/lights
	./bin/lights <input.txt

bin/lights: lights.c
	mkdir -p bin
	ctags lights.c
	gcc -Wall -o bin/lights lights.c
