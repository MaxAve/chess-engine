all:
	g++ src/main.cpp src/bitboard.cpp src/transposition.cpp -o chess -lsfml-graphics -lsfml-window -lsfml-system