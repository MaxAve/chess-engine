/**
 * At the moment this file is the GUI
 * I might move GUI stuff to a different folder some time later
 * 
 * Just don't touch anything here. This is just black magic for all you need
 * to know. Go focus on the engine itself.
 * 
 * All you need to know about this is that this is just a piece of code that
 * interacts with the engine API to do stuff.
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "src/bitboard.h"
#include "src/utils.h"
#include "src/types.h"
#include "src/transposition.h"
#include "src/pieces.h"
#include "src/eval.h"

#define DEBUG_TEXT_DATA_ZOBRIST_HASH 0
#define DEBUG_TEXT_DATA_EVAL 1
#define DEBUG_TEXT_DATA_DEPTH 2
#define DEBUG_TEXT_DATA_DEEP_EVAL 3

sf::Font openSans;

void InitText(sf::Text *text, int x, int y, std::string str)
{
    (*text).setFont(openSans);
    (*text).setString(str);
    (*text).setCharacterSize(20);
    (*text).setFillColor(sf::Color::Black);
    (*text).setPosition(x, y);
}

/* Draw rectangle using vertexes */
void DrawRectangle(sf::RenderWindow& window, float x, float y, float width, float height, const sf::Color& color)
{
    sf::Vertex vertices[] = {
        sf::Vertex(sf::Vector2f(x, y), color),
        sf::Vertex(sf::Vector2f(x + width, y), color),
        sf::Vertex(sf::Vector2f(x + width, y + height), color),
        sf::Vertex(sf::Vector2f(x, y + height), color)
    };
    window.draw(vertices, 4, sf::Quads);
}

/* Update sprite grid for pieces */
void UpdatePieceSprites(sf::Sprite *sprites, sf::Texture *textures, const Bitboard &board)
{
    for (int j = 0; j < 64; j++)
    {
        sf::Color c = sprites[j].getColor();
        c.a = 0;
        sprites[j].setColor(c);
    }
    for (int i = 0; i < NUM_PIECES; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if (board.bitboards[i] & (0x8000000000000000ULL >> j))
            {
                sprites[j].setTexture(textures[i]);
                sf::Color c = sprites[j].getColor();
                c.a = 255;
                sprites[j].setColor(c);
            }
        }
    }
}

int main(int argc, char** argv)
{
    Bitboard mainBoard;
    InitBitboard(&mainBoard, BOARD_SETUP_EMPTY);
    TranspositionTable::InitZobristKeys();
    mainBoard.bitboards[KB] |= (1ULL << 63);
    mainBoard.bitboards[KW] |= (1ULL << 50);
    mainBoard.bitboards[PB] |= (1ULL << 55);

    bool debugMode = false;
    if(argc > 1)
        bool debugMode = argv[1];

    const int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;
    const int SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Chess Engine");
    window.setVerticalSyncEnabled(true);

    /* Textures */
    sf::Texture pieceTextures[NUM_PIECES];
    std::string pieceTexturePaths[NUM_PIECES] = {
        "assets/textures/pb.png", "assets/textures/nb.png", "assets/textures/bb.png", "assets/textures/rb.png", "assets/textures/qb.png", "assets/textures/kb.png", "assets/textures/pw.png", "assets/textures/nw.png", "assets/textures/bw.png", "assets/textures/rw.png", "assets/textures/qw.png", "assets/textures/kw.png"};
    for (int i = 0; i < NUM_PIECES; i++)
        pieceTextures[i].loadFromFile(pieceTexturePaths[i]);

    sf::Texture boardTexture;
    boardTexture.loadFromFile("assets/textures/chessboard.png");

    sf::Texture whiteOutlineTexture;
    whiteOutlineTexture.loadFromFile("assets/textures/white_outline.png");

    /* Fonts */
    openSans.loadFromFile("assets/fonts/OpenSans-VariableFont_wdth,wght.ttf");

    /* Board sprite */
    const int SQUARE_SIZE = 100;
    const int PIECE_SIZE = SQUARE_SIZE;
    sf::Sprite boardSprite;
    boardSprite.setTexture(boardTexture);
    const sf::Vector2i chessboardRenderOffset(100, 100);
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

    /* Text */
    sf::Text debug_zobristHash;
    InitText(&debug_zobristHash, SQUARE_SIZE * 8 + chessboardRenderOffset.x + 20, chessboardRenderOffset.y, "Hash: " + std::to_string(TranspositionTable::ZobristHash(mainBoard)));
    sf::Text debug_flags;
    InitText(&debug_flags, SQUARE_SIZE * 8 + chessboardRenderOffset.x + 20, chessboardRenderOffset.y + 20, "Flags: " + BinaryToString(mainBoard.flags));
    sf::Text debug_eval;
    InitText(&debug_eval, SQUARE_SIZE * 8 + chessboardRenderOffset.x + 20, chessboardRenderOffset.y + 40, "Eval: " + std::to_string(Eval::PieceSquareTablesEval(&mainBoard)));
    sf::Text debug_deepEval;
    InitText(&debug_deepEval, SQUARE_SIZE * 8 + chessboardRenderOffset.x + 20, chessboardRenderOffset.y + 60, "Deep eval: 0");

    /* Square cursor */
    sf::Sprite squareOutline;
    squareOutline.setTexture(whiteOutlineTexture);
    squareOutline.setScale(
        (float)PIECE_SIZE / (float)pieceTextures[PW].getSize().x, (float)PIECE_SIZE / (float)pieceTextures[PW].getSize().y);

    UpdatePieceSprites(chessPieceSprites, pieceTextures, mainBoard);

    /* UI stuff */
    sf::Vector2i cursorSquarePos(0, 0);
    sf::Vector2i selectedSquare(0, 0);
    sf::Vector2i selectedPiecePosition(-1, -1);
    uint8_t selectedPiece = NO_PIECE;
    uint64_t squareMarks = 0ULL;
    uint64_t legalMoves = 0ULL;
    bool player1Turn = true;

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
                    squareMarks = 0ULL;
                    selectedSquare = cursorSquarePos;
                    const uint8_t bit = (63-GET_1D_X(selectedSquare.x, selectedSquare.y, BOARD_WIDTH));
                    // If the selected piece is not set, set it; else move the piece unless the selected piece is clicked on again
                    if (selectedPiecePosition.x < 0 || selectedPiecePosition.y < 0)
                    {
                        // If there is a piece on this square, set the selected piece
                        if (GetPieceType(&mainBoard, bit) != NO_PIECE)
                        {
                            selectedPiecePosition = selectedSquare;
                            selectedPiece = GetPieceType(&mainBoard, bit);
                            legalMoves = GetLegalMoves(&mainBoard, selectedPiece, bit);
                            squareMarks = legalMoves;
                        }
                    }
                    else {
                        if(selectedPiecePosition.x != selectedSquare.x || selectedPiecePosition.y != selectedSquare.y)
                        {
                            if(legalMoves & (1ULL << bit) || debugMode)
                            {
                                // Remove all pieces at the target position
                                for(uint8_t i = 0; i < 12; i++)
                                    mainBoard.bitboards[i] &= ~(1ULL << bit);

                                mainBoard.bitboards[selectedPiece] |= (1ULL << bit); // Place piece at target square
                                mainBoard.bitboards[selectedPiece] &= ~(1ULL << (63-GET_1D_X(selectedPiecePosition.x, selectedPiecePosition.y, BOARD_WIDTH))); // Remove piece from old square
                                
                                legalMoves = 0ULL;

                                player1Turn = false;

                                UpdatePieceSprites(chessPieceSprites, pieceTextures, mainBoard);
                                debug_zobristHash.setString("Hash: " + std::to_string(TranspositionTable::ZobristHash(mainBoard)));
                                debug_eval.setString("Eval: " + std::to_string(Eval::PieceSquareTablesEval(&mainBoard)));
                            }
                        }
                        selectedPiecePosition = sf::Vector2i(-1, -1);
                    }
                    break;
            }
        }

        cursorSquarePos.x = (sf::Mouse::getPosition().x - window.getPosition().x) / SQUARE_SIZE - 1;
        cursorSquarePos.y = (sf::Mouse::getPosition().y - window.getPosition().y - 30) / SQUARE_SIZE - 1;

        squareOutline.setPosition(
            cursorSquarePos.x * SQUARE_SIZE + chessboardRenderOffset.x, cursorSquarePos.y * SQUARE_SIZE + chessboardRenderOffset.y);

        window.clear(sf::Color::White);

        /* Draws board & chess pieces */
        window.draw(boardSprite);
        for(int i = 0; i < 64; i++)
            window.draw(chessPieceSprites[i]);

        /* Highlights marked squares (red) */
        for(int i = 0; i < 64; i++)
            if (squareMarks & (1ULL << i))
                DrawRectangle(window, (7 - GET_2D_X(i)) * SQUARE_SIZE + chessboardRenderOffset.x, (7 - GET_2D_Y(i)) * SQUARE_SIZE + chessboardRenderOffset.y, SQUARE_SIZE, SQUARE_SIZE, sf::Color(255, 0, 0, 127));

        /* Highlights selected piece (yellow) */
        if(selectedPiecePosition.x != -1 && selectedPiecePosition.y != -1)
        {
            DrawRectangle(
                window,
                chessboardRenderOffset.x + selectedPiecePosition.x * SQUARE_SIZE,
                chessboardRenderOffset.y + selectedPiecePosition.y * SQUARE_SIZE,
                SQUARE_SIZE,
                SQUARE_SIZE,
                sf::Color(255, 255, 0, 130));
        }

        window.draw(debug_zobristHash);
        window.draw(debug_flags);
        window.draw(debug_eval);
        window.draw(debug_deepEval);

        window.draw(squareOutline);

        window.display();

        if(!player1Turn && !debugMode)
        {
            //TODO computer move; move this to a thread or some shit
            Search::DeepEval cpuEval = Search::minimax(&mainBoard, 4, false);
            for(uint8_t i = 0; i < 12; ++i)
            {
                mainBoard.bitboards[i] &= ~cpuEval.bestMove.modified;
                mainBoard.bitboards[i] &= ~cpuEval.extra.modified;
            }
            mainBoard.bitboards[cpuEval.bestMove.pieceType] = cpuEval.bestMove.modified;
            mainBoard.bitboards[cpuEval.extra.pieceType] = cpuEval.extra.modified;

            UpdatePieceSprites(chessPieceSprites, pieceTextures, mainBoard);
            debug_zobristHash.setString("Hash: " + std::to_string(TranspositionTable::ZobristHash(mainBoard)));
            debug_eval.setString("Eval: " + std::to_string(Eval::PieceSquareTablesEval(&mainBoard)));
            debug_deepEval.setString("Deep eval: " + std::to_string(cpuEval.eval));

            player1Turn = true;
        }
    }

    return 0;
}
