all: linux

linux:
	g++ -O3  main.cpp src/bitboard.cpp src/transposition.cpp src/utils.cpp src/eval.cpp src/search.cpp src/pieces.cpp -o chess -lsfml-graphics -lsfml-window -lsfml-system

windows:
	x86_64-w64-mingw32-g++ -O3 main.cpp src/bitboard.cpp src/transposition.cpp src/utils.cpp src/eval.cpp src/search.cpp src/pieces.cpp -o chess

clean:
	rm chess*
