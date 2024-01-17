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

void DrawRectangle(sf::RenderWindow& window, float x, float y, float width, float height, const sf::Color& color) {
    sf::Vertex vertices[] = {
        sf::Vertex(sf::Vector2f(x, y), color),
        sf::Vertex(sf::Vector2f(x + width, y), color),
        sf::Vertex(sf::Vector2f(x + width, y + height), color),
        sf::Vertex(sf::Vector2f(x, y + height), color)
    };
    window.draw(vertices, 4, sf::Quads);
}

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

    sf::Texture whiteOutlineTexture;
    whiteOutlineTexture.loadFromFile("assets/textures/white_outline.png");

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

    sf::Sprite squareOutline;
    squareOutline.setTexture(whiteOutlineTexture);
    squareOutline.setScale(
        (float)PIECE_SIZE / (float)pieceTextures[PW].getSize().x, (float)PIECE_SIZE / (float)pieceTextures[PW].getSize().y);

    Bitboard mainBoard;
    InitBitboard(&mainBoard, BOARD_SETUP_CLASSIC);
    TPosTable::InitZobristKeys();
    UpdatePieceSprites(chessPieceSprites, pieceTextures, mainBoard);

    sf::Vector2i cursorSquarePos(0, 0);
    sf::Vector2i selectedSquare(0, 0);

    uint64_t squareMarks = 0ULL;

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
                case sf::Event::MouseButtonPressed:
                    if (cursorSquarePos == selectedSquare)
                    {
                        squareMarks = 0ULL;
                    }
                    else {
                        squareMarks = 0ULL;
                        sf::Vector2i oldSelectedSquare = selectedSquare;
                        selectedSquare = cursorSquarePos;
                        squareMarks |= (0x8000000000000000ULL >> GET_1D_X(selectedSquare.x, selectedSquare.y, BOARD_WIDTH));
                        squareMarks &= GetCombinedBitboard(&mainBoard);
                    }
                    break;
            }
        }

        cursorSquarePos.x = (sf::Mouse::getPosition().x - window.getPosition().x) / SQUARE_SIZE - 1;
        cursorSquarePos.y = (sf::Mouse::getPosition().y - window.getPosition().y - 30) / SQUARE_SIZE - 1;

        squareOutline.setPosition(
            cursorSquarePos.x * SQUARE_SIZE + chessboardRenderOffset.x, cursorSquarePos.y * SQUARE_SIZE + chessboardRenderOffset.y);

        window.clear(sf::Color::White);

        window.draw(boardSprite);
        for(int i = 0; i < 64; i++) {
            window.draw(chessPieceSprites[i]);
        }

        for(int i = 0; i < 64; i++)
        {
            if (squareMarks & (1ULL << i))
            {
                DrawRectangle(window, (7 - GET_2D_X(i)) * SQUARE_SIZE + chessboardRenderOffset.x, (7 - GET_2D_Y(i)) * SQUARE_SIZE + chessboardRenderOffset.y, SQUARE_SIZE, SQUARE_SIZE, sf::Color(255, 0, 0, 127));
            }
        }

        window.draw(squareOutline);

        window.display();
    }

    return 0;
}