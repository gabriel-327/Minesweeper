#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include "button.h"
using namespace std;



#ifndef MINESWEEPER_TILES_H
#define MINESWEEPER_TILES_H

enum class TileStatus {
    COVERED,
    REVEALED,
    SHOWBOMB,
    FLAG

};

class Tiles{
//    vector<vector<TileStatus>> tile_vec;
    Texture * texture;
//    vector<vector<bool>> has_bomb;
public:
    vector<vector<TileStatus>> tile_vec;
    vector<vector<bool>> has_bomb;
    vector<vector<int>> tile_numbers;

    Tiles(array<int, 3> config_array, Texture &texture);

    void render(sf::RenderWindow &game_window, bool bombs_show);

    TileStatus getStatus(int x, int y);

    void setStatus(int x, int y, TileStatus status);

    bool getBomb(int x, int y);

    void setBomb(int x, int y);

    void randomize_bombs(array<int, 3> config_array, Tiles& board);


    void num_adjacent_tiles(Tiles& board);

    void recursive_reveal(int x, int y);

    int check_flag_bomb(int bombs);
};

#endif //MINESWEEPER_TILES_H
