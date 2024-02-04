all:
	g++ -O3 main.cpp src/bitboard.cpp src/transposition.cpp src/utils.cpp src/eval.cpp src/search.cpp src/pieces.cpp -o chess -lsfml-graphics -lsfml-window -lsfml-system
