all:
	g++ -I src/include -L /path/to/sdl2/libs -o main main.cpp igralec.cpp portal.cpp vrata.cpp arena.cpp neprijatelji.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
