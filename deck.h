/*
 * File: deck.h
 *
 * Defines the Threes deck of numbers.
 *
 */

#ifndef DECK_H
#define DECK_H

#include <array>
#include <iostream>
//#include "strong_typedef.h"

//STRONG_TYPEDEF(int, Tile);
typedef int Tile;

namespace threes {
    constexpr int MAX_TILE = 13;

    int get_tile_value(Tile);
    int get_tile_points(Tile);
    
    constexpr std::array<int, MAX_TILE+1> calculate_tables(
            int maxTile, int inc) {
        std::array<int,MAX_TILE+1> array{};

        array[0] = 0;
        int value = 3;
        for (int i = 1; i <= maxTile; i++) {
            array[i] = value;
            value *= inc;
        }
        
        return array;
    }

    /*constexpr std::array<int, MAX_TILE+1> calculate_constant_values(
            int maxTile) {
        
    } */
    /*constexpr std::array<int, MAX_TILE+1> calculate_constant_points(
            int maxTile);
*/
    constexpr std::array<int, MAX_TILE+1> value_table =
            calculate_tables(MAX_TILE, 2);
    
    constexpr std::array<int, MAX_TILE+1> points_table =
            calculate_tables(MAX_TILE, 3);

} // end namespace threes

class Deck {
    private:
        static constexpr int BASE_TILES_IN_DECK = 12;

        // probability of a big tile in each deck
        static constexpr double PROB_BIG_TILE_PER_DECK = 0.5;
        
        // minimum value of a big tile
        static constexpr Tile MIN_BIG_TILE = 2;
        
        // distance from max tile of largest big tile
        static constexpr Tile BIG_TILE_DIST = 3;
        
        void makeDeck(Tile);
    
        std::array<Tile, BASE_TILES_IN_DECK+1> tiles;
        
        int nextTileIndex;
        int numTiles;
        Tile highestTile;

    public:
        Deck();
        ~Deck();
        
        Tile nextTile(Tile);

        friend std::ostream& operator<<(std::ostream&, const Deck&);
         
};

std::ostream& operator<<(std::ostream&, const Deck&);

#endif
