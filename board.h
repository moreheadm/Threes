/*
 * File: board.h
 *
 *
 */

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <utility>
#include "deck.h"

enum class BoardMove {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

class Board {

    private:
        static constexpr int INITIAL_FILL = 9;
    public:    
        static constexpr int DIM = 4;
        static constexpr Tile EMPTY = -2;

        typedef std::array<std::array<Tile, DIM>, DIM> Grid;
    private: 
        Grid grid;
        
        Tile nextTile;
        Tile maxTile;
        
        Deck deck;
        
        std::array<bool,4> legalMoves;

        bool gameOver;

        bool addTile();

    public:

        Board();
        ~Board();
        

        std::pair<bool, Grid> checkMove(BoardMove m);
        bool checkMoves();
        void move(BoardMove m);
        
        std::array<bool,4> getLegalMoves();

        bool isGameOver();
        
        int getScore();

        void getBoardAsArray(std::array<int, DIM*DIM+1>);
                
        friend std::ostream& operator<<(std::ostream&, const Board&);
};

std::ostream& operator<<(std::ostream&, const Board&);

#endif
