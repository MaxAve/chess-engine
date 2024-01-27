all:
	g++ main.cpp src/bitboard.cpp src/transposition.cpp src/pieces.cpp -o chess -lsfml-graphics -lsfml-window -lsfml-system