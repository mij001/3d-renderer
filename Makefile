build:
	gcc -Wall -Wextra -lm -lSDL2 -std=c99 ./src/*.c -o ./bin/renderer

run:
	./bin/renderer

clean:
	rm ./bin/*

bun: clean build
	./bin/renderer