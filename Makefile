CC=gcc
flags=-O2 -std=c11 -Wshadow -Wall -pedantic
fla=-std=c11 -Wshadow -Wall -pedantic -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g -DLOCAL
# maybe needed later :  -static-libasan -lasan
sdl=`pkg-config sdl2 --libs` -lSDL2_image
objs=obj/mysdl.o obj/block.o obj/movement.o obj/cvector.o

bin/game.out: src/main.c $(objs)
	$(CC) $(flags) $(objs) src/main.c -o bin/game.out $(sdl)

obj/mysdl.o: src/mysdl.c include/mysdl.h
	$(CC) $(flags) -c src/mysdl.c -o obj/mysdl.o

obj/block.o: src/block.c include/block.h
	$(CC) $(flags) -c src/block.c -o obj/block.o

obj/movement.o: src/movement.c include/movement.h
	$(CC) $(flags) -c src/movement.c -o obj/movement.o

obj/cvector.o: src/cvector.c include/cvector.h
	$(CC) $(flags) -c src/cvector.c -o obj/cvector.o

run: bin/game.out
	./bin/game.out
