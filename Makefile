CC=g++
CFLAGS=-std=c++20
APPNAME=aoc2020.13

obj/%.o: src/%.c++
	$(CC) -c -o $@ $< $(CFLAGS)

main: obj/day13.o
	$(CC) -o bin/$(APPNAME) $^

run: main
	bin/$(APPNAME)

clean:
	rm -rf bin/$(APPNAME) obj/*.o
