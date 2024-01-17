/**
 * At the moment this file is the GUI
 * I might move GUI stuff to a different folder some time later
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "bitboard.h"
#include "utils.h"
#include "types.h"
#include "transposition.h"

void UpdatePieceSprites(sf::Sprite *sprites, sf::Texture *textures, const Bitboard &board)
{
    for (int i = 0; i < NUM_PIECES; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if (board.bitboards[i] & (0x8000000000000000ULL >> j))
            {
                sprites[j].setTexture(textures[i]);
            }
        }
    }
}

int main(int argc, char** argv)
{
    const int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;
    const int SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Chess Engine");
    window.setVerticalSyncEnabled(true);

    sf::Texture pieceTextures[NUM_PIECES];
    std::string pieceTexturePaths[NUM_PIECES] = {
        "assets/textures/pb.png", "assets/textures/nb.png", "assets/textures/bb.png", "assets/textures/rb.png", "assets/textures/qb.png", "assets/textures/kb.png", "assets/textures/pw.png", "assets/textures/nw.png", "assets/textures/bw.png", "assets/textures/rw.png", "assets/textures/qw.png", "assets/textures/kw.png"};
    for (int i = 0; i < NUM_PIECES; i++)
        pieceTextures[i].loadFromFile(pieceTexturePaths[i]);

    sf::Texture boardTexture;
    boardTexture.loadFromFile("assets/textures/chessboard.png");

    const int SQUARE_SIZE = 100;
    const int PIECE_SIZE = SQUARE_SIZE;
    const sf::Vector2i chessboardRenderOffset(100, 100);
    sf::Sprite boardSprite;
    boardSprite.setTexture(boardTexture);
    boardSprite.setPosition(chessboardRenderOffset.x, chessboardRenderOffset.y);
    boardSprite.setScale(SQUARE_SIZE, SQUARE_SIZE);
	sf::Sprite chessPieceSprites[64];
	for (int i = 0; i < 64; i++)
    {
		chessPieceSprites[i] = sf::Sprite();
        chessPieceSprites[i].setScale(
            (float)PIECE_SIZE / (float)pieceTextures[PW].getSize().x, (float)PIECE_SIZE / (float)pieceTextures[PW].getSize().y);
        chessPieceSprites[i].setPosition(
            GET_2D_X(i) * SQUARE_SIZE + chessboardRenderOffset.x + (SQUARE_SIZE - PIECE_SIZE),
            GET_2D_Y(i) * SQUARE_SIZE + chessboardRenderOffset.y + (SQUARE_SIZE - PIECE_SIZE));
	}

    Bitboard mainBoard;
    InitBitboard(&mainBoard, BOARD_SETUP_CLASSIC);
    TPosTable::InitZobristKeys();
    UpdatePieceSprites(chessPieceSprites, pieceTextures, mainBoard);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear(sf::Color::White);

        window.draw(boardSprite);
        for(int i = 0; i < 64; i++) {
            window.draw(chessPieceSprites[i]);
        }

        window.display();
    }

    return 0;
}