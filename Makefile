all:
	g++ -Isrc/include -Lsrc/lib -o main src/*.cpp -lmingw32 -lSDL2main -lSDL2