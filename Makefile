all:
	g++ main.cpp src/bitboard.cpp src/transposition.cpp src/utils.cpp src/pieces.cpp -o chess -lsfml-graphics -lsfml-window -lsfml-system