/*
 * File board.cpp
 *
 *
 */
#include <iostream>
#include <random>
#include <utility>
#include "deck.h"
#include "board.h"

extern std::default_random_engine random_engine;
extern const Tile Board::EMPTY;

/*
int main () {
    Board board;

    std::cout << board << std::endl;
    std::cout << "Points: " << board.getScore() << std::endl;
    board.move(BoardMove::UP);
    std::cout << board << std::endl;
    board.move(BoardMove::RIGHT);
    std::cout << board << std::endl;
    for (int i = 0; i < 5; i++) {
        board.move(BoardMove::LEFT);
        std::cout << board << std::endl;
    }
}
*/

std::ostream& operator<<(std::ostream &os, const Board &board) {
    for (auto& row : board.grid) {
        os << " ";
        for (auto& tile : row) {
            std::string s = std::to_string(threes::get_tile_value(tile));
            os << s;
            for (int i = s.length(); i < 6; i++) {
                os << " ";
            }
        }

        os << std::endl;
    }
    os << "Next tile: " << threes::get_tile_value(board.nextTile);
    return os;
}

Board::Board(): maxTile(0), gameOver(false), deck() {
    nextTile = deck.nextTile(maxTile);
    
    Tile fillValue = EMPTY;
    for (auto &row : grid) {
        row.fill(fillValue);
    }
    
    for (int i = 0; i < INITIAL_FILL; i++) {
        addTile();
    }

    gameOver = !checkMoves();
}

Board::~Board() {

}

bool Board::addTile() {
    std::vector<std::pair<int, int>> v;

    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) { 
            if (grid[i][j] == EMPTY) {
                v.push_back(std::pair<int, int>(i, j));
            }
        }
    }
    if (v.size() == 0) {
        return false;
    }

    std::uniform_int_distribution<int> index(0, v.size()-1);
    
    const std::pair<int, int> &loc = v[index(random_engine)];
    
    grid[std::get<0>(loc)][std::get<1>(loc)] = nextTile;

    nextTile = deck.nextTile(maxTile);
    
    return true;
}

void Board::move(BoardMove m) {
    if (!gameOver && legalMoves[(size_t) m]) {
        grid = std::get<1>(checkMove(m));
        addTile();
        gameOver = !checkMoves();
    }
}

bool Board::checkMoves() {
    if (gameOver) {
        return false;
    }

    for (int m = 0; m < 4; m++) {
        auto pair = checkMove(static_cast<BoardMove>(m));
        legalMoves[m] = std::get<0>(pair);
    }
    
    bool atLeastOneMove = false;
    
    for (auto direction : legalMoves) {
        atLeastOneMove = atLeastOneMove || direction;
    }
    
    return atLeastOneMove;
}

std::pair<bool, Board::Grid> Board::checkMove(BoardMove m) {
     
    if (gameOver) {
        return std::make_pair(false, grid);
    }

    Grid newGrid = grid;
    const Grid &oldGrid = grid;

    switch (m) {
        case BoardMove::UP:

            for (int r = 0; r < DIM-1; r++) {
                for (int c = 0; c < DIM; c++) {
                    if (newGrid[r][c] == EMPTY) {
                        newGrid[r][c] = oldGrid[r+1][c];
                        newGrid[r+1][c] = EMPTY;
                    }  else if (newGrid[r][c] == -1 || newGrid[r][c] == 0) {
                        if ((oldGrid[r+1][c] == -1 || oldGrid[r+1][c] == 0) &&
                                (newGrid[r][c] != oldGrid[r+1][c])) {
                            // matched 1 and 2
                            newGrid[r][c] = 1; // make a three
                            newGrid[r+1][c] = EMPTY; //get rid of second tile
                        }

                    } else if (newGrid[r][c] == oldGrid[r+1][c]) { // match
                        newGrid[r][c] = newGrid[r][c] + 1; // combine tiles
                        newGrid[r+1][c] = EMPTY; // get rid of second tile
                    }
                }
            }
            break;
        case BoardMove::RIGHT:
  
            for (int c = DIM-1; c > 0; c--) {
                for (int r = 0; r < DIM; r++) {
                    if (newGrid[r][c] == EMPTY) {
                        newGrid[r][c] = oldGrid[r][c-1];
                        newGrid[r][c-1] = EMPTY;
                    } else if (newGrid[r][c] == -1 || newGrid[r][c] == 0) {
                        if ((oldGrid[r][c-1] == -1 || oldGrid[r][c-1] == 0) &&
                                (newGrid[r][c] != oldGrid[r][c-1])) {
                            // matched 1 and 2
                            newGrid[r][c] = 1; // make a three
                            newGrid[r][c-1] = EMPTY; //get rid of second tile
                        }
                    } else if (newGrid[r][c] == oldGrid[r][c-1]) { // match
                        newGrid[r][c] = newGrid[r][c] + 1; // combine tiles
                        newGrid[r][c-1] = EMPTY; // get rid of second tile
                    }
                }
            }
            break;
        
        case BoardMove::DOWN:
 
            for (int r = DIM-1; r > 0; r--) {
                for (int c = 0; c < DIM; c++) {
                    if (newGrid[r][c] == EMPTY) {
                        newGrid[r][c] = oldGrid[r-1][c];
                        newGrid[r-1][c] = EMPTY;
                    }  else if (newGrid[r][c] == -1 || newGrid[r][c] == 0) {
                        if ((oldGrid[r-1][c] == -1 || oldGrid[r-1][c] == 0) &&
                                (newGrid[r][c] != oldGrid[r-1][c])) {
                            // matched 1 and 2
                            newGrid[r][c] = 1; // make a three
                            newGrid[r-1][c] = EMPTY; //get rid of second tile
                        }
                        
                    } else if (newGrid[r][c] == oldGrid[r-1][c]) { // match
                        newGrid[r][c] = newGrid[r][c] + 1; // combine tiles
                        newGrid[r-1][c] = EMPTY; // get rid of second tile
                    }
                }
            }
            break;
        
        case BoardMove::LEFT:
 
            for (int c = 0; c < DIM-1; c++) {
                for (int r = 0; r < DIM; r++) {
                    if (newGrid[r][c] == EMPTY) {
                        newGrid[r][c] = oldGrid[r][c+1];
                        newGrid[r][c+1] = EMPTY;
                    } else if (newGrid[r][c] == -1 || newGrid[r][c] == 0) {
                        if ((oldGrid[r][c+1] == -1 || oldGrid[r][c+1] == 0) &&
                                (newGrid[r][c] != oldGrid[r][c+1])) {
                            // matched 1 and 2
                            newGrid[r][c] = 1; // make a three
                            newGrid[r][c+1] = EMPTY; //get rid of second tile
                        }
                        
                    } else if (newGrid[r][c] == oldGrid[r][c+1]) { // match
                        newGrid[r][c] = newGrid[r][c] + 1; // combine tiles
                        newGrid[r][c+1] = EMPTY; // get rid of second tile
                    }
                }
            }
            break;
    
    }
    /*
    for (auto &row : newGrid) {
        for (auto &tile : row) {
            std::cout << tile << " ";
        }
    }

    std::cout << std::endl << std::endl;
    */

    if(newGrid == oldGrid) {
        return std::make_pair(false, newGrid);
    } else {
        return std::make_pair(true, newGrid);
    }


}

std::array<bool,4> Board::getLegalMoves() {
    return legalMoves;
}

void Board::getBoardAsArray(std::array<int, DIM*DIM+1> array) {
    auto it = array.begin();
    for (auto &row : grid) {
        for (auto &tile : row) {
            *it = tile;
            it++;
        }
    }
    *it = nextTile;
}

bool Board::isGameOver() {
    return gameOver;
}

int Board::getScore() {
    int points = 0;
    for (auto &row : grid) {
        for (auto &tile : row) {
            points += threes::get_tile_points(tile);
        }
    }
    return points;
}
