CC=g++
CFLAGS=-ltbb -std=c++20
APPNAME=aoc2020.13

obj/%.o: src/%.c++
	$(CC) -c $(CFLAGS) -o $@ $< 

main: obj/day13.o
	$(CC) $(CFLAGS) -o bin/$(APPNAME) $^

run: main
	bin/$(APPNAME)

clean:
	rm -rf bin/$(APPNAME) obj/*.o
