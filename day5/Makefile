all: bin/nicestr bin/nicestr2

bin/nicestr: nicestr.c
	mkdir -p bin
	gcc -Wall -o bin/nicestr nicestr.c
	./bin/nicestr <input.txt

bin/nicestr2: nicestr2.c
	mkdir -p bin
	gcc -Wall -o bin/nicestr2 nicestr2.c
	./bin/nicestr2 <input.txt
