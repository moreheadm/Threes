/*
 * File: deck.cpp
 *
 * Implements the Threes deck of numbers
 *
 */

#include <array>
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "deck.h"

extern std::default_random_engine random_engine;

/*
int main() {
    Deck deck;
    
    std::cout << deck << std::endl;
    deck.nextTile(0);
    std::cout << deck << std::endl;
}
*/

namespace threes {
    int get_tile_value(Tile t) {
        if (t == -1) {
            return 1;
        } else if (t == 0) {
            return 2;
        } else if (t < -1) {
            return 0;
        } else {
            if (t > 13) 
                std::cout << t << std::endl;
            return value_table.at(t);
        }
    }

    int get_tile_points(Tile t) {
        if (t <= 0) {
            return 0;
        } else {
            if (t > 13)
                std::cout << t << std::endl;

            return points_table.at(t);
        } 
    }

    constexpr std::array<int,MAX_TILE+1> calculate_constant_values(
            int maxTile) {
        using result = std::array<int,MAX_TILE+1>;
        result array{};

        array[0] = 0;
        int value = 3;
        for (int i = 1; i <= maxTile; i++) {
            array[i] = value;
            value *= 2;
        }
        
        result result_array(array);

        return result_array;
    }

    constexpr std::array<int,MAX_TILE+1> calculate_constant_points(
            int maxTile) {
        using result = std::array<int,MAX_TILE+1>;
        result array{};

        array[0] = 0;
        int value = 3;
        for (int i = 1; i <= maxTile; i++) {
            array[i] = value;
            value *= 3;
        }
        
        return array;
    }
    
    /*constexpr std::array<int, MAX_TILE+1> value_table =
            calculate_constant_values(MAX_TILE);
    constexpr std::array<int, MAX_TILE+1> points_table =
            calculate_constant_points(MAX_TILE);
  */ 
    //value_table = calculate_constant_values(MAX_TILE);
    //constexpr std::array<int,MAX_TILE+1> points_table = calculate_constant_points(MAX_TILE);

}




std::ostream& operator<<(std::ostream& os, const Deck& deck) {
    os << "Deck: [ ";
    
    auto end = deck.tiles.begin() + deck.numTiles;
    for (auto it = deck.tiles.begin() + deck.nextTileIndex; it != end; it++) {
        os << threes::get_tile_value(*it) << " ";
    }

    os << "]";
    return os;
}

Deck::Deck(): tiles(), highestTile(0) {
    makeDeck(highestTile);
}

Deck::~Deck() {
    
}

Tile Deck::nextTile(Tile maxTile) {
    Tile tile = tiles[nextTileIndex++];
    
    if (nextTileIndex == numTiles) {
        makeDeck(maxTile);
    }

    return tile;
}

void Deck::makeDeck(Tile maxTile) {
    static constexpr int TILES_PER_TYPE = BASE_TILES_IN_DECK / 3;
    
    static std::uniform_real_distribution<double> gen(0.0,1.0);

    for (int i = 0; i < TILES_PER_TYPE; i++) {
        tiles[i] = -1; // 1
        tiles[TILES_PER_TYPE + i] = 0; // 2
        tiles[2*TILES_PER_TYPE + i] = 1; // 3
    }

    if (maxTile >= MIN_BIG_TILE + BIG_TILE_DIST &&
            gen(random_engine) < PROB_BIG_TILE_PER_DECK) {
        std::uniform_int_distribution<Tile> bigTile(MIN_BIG_TILE, maxTile);

        tiles[BASE_TILES_IN_DECK] = bigTile(random_engine);

        numTiles = BASE_TILES_IN_DECK + 1;
    } else {
        numTiles = BASE_TILES_IN_DECK;
    }

    std::shuffle(tiles.begin(), tiles.begin() + numTiles, random_engine);
    
    nextTileIndex = 0;
}


