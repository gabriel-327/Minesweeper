#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include "Tiles.h"
#include <cstdlib>


using namespace std;


Tiles::Tiles(array<int, 3> config_array, Texture &texture) : tile_vec(config_array[0], vector<TileStatus>(config_array[1], TileStatus::COVERED)),
has_bomb(config_array[0], vector<bool>(config_array[1], false)), tile_numbers(config_array[0], vector<int>(config_array[1], 0)){
    this->texture = &texture;
}

void Tiles::render(sf::RenderWindow &game_window, bool bombs_show) {
    sf::Texture tile_hidden = texture->getTexture("tile_hidden");
    sf::Texture tile_revealed = texture->getTexture("tile_revealed");
    sf::Texture tile_flagged = texture->getTexture("flag");
    sf::Texture tile_bomb = texture->getTexture("mine");

    sf::Sprite sprite;
    for(int i = 0; i < tile_vec.size(); i++){
        for(int j = 0; j < tile_vec[0].size(); j++){
            switch (tile_vec[i][j]) {
                case TileStatus::COVERED:
                    sprite.setTexture(tile_hidden);
                    sprite.setPosition(i * 32, j * 32);
                    game_window.draw(sprite);
                    if (bombs_show && has_bomb[i][j]) {
                        sprite.setTexture(tile_bomb);
                        game_window.draw(sprite);
                    }
                    break;
                case TileStatus::REVEALED:
                    sprite.setTexture(tile_revealed);
                    sprite.setPosition(i * 32, j * 32);
                    game_window.draw(sprite);
                    if (has_bomb[i][j]) {
                        sprite.setTexture(tile_bomb);
                        game_window.draw(sprite);
                        // draws numbers around each tile
                    } else if (tile_numbers[i][j] > 0) {
                        sprite.setTexture((texture->getDigit(tile_numbers[i][j])));
                        game_window.draw(sprite);
                    }
                    break;
                case TileStatus::FLAG:
                    sprite.setTexture(tile_hidden);
                    sprite.setPosition(i * 32, j * 32);
                    game_window.draw(sprite);
                    if (bombs_show && has_bomb[i][j]) {
                        sprite.setTexture(tile_bomb);
                    } else {
                        sprite.setTexture(tile_flagged);
                    }
                    game_window.draw(sprite);
                    break;
                case TileStatus::SHOWBOMB:
                    sprite.setTexture(tile_hidden);
                    sprite.setPosition(i * 32, j * 32);
                    game_window.draw(sprite);
                    sprite.setTexture(tile_bomb);
                    game_window.draw(sprite);
                    break;

            }
        }
    }
}

TileStatus Tiles::getStatus(int x, int y) {
    return tile_vec[x][y];
}

void Tiles::setStatus(int x, int y, TileStatus status) {
    tile_vec[x][y] = status;
}

void Tiles::setBomb(int x, int y) {
    has_bomb[x][y] = true;
}

bool Tiles::getBomb(int x, int y) {
    return has_bomb[x][y];
}

void Tiles::randomize_bombs(array<int, 3> config_array, Tiles& board) {
    map<pair<int, int>, bool> mymap;

    // Sets has bomb vector to false so multiple bombs will not be printed
            for (int i = 0; i < board.has_bomb.size(); i++) {
                for (int j = 0; j < board.has_bomb[0].size(); j++) {
                    board.has_bomb[i][j] = false;
                    board.tile_numbers[i][j] = 0;
                }
            }
            while(0 < config_array[2]){
                int randomNumber = rand() % config_array[0];
                int randomNumber2 = rand() % config_array[1];
                pair<int, int> location = {randomNumber, randomNumber2};
                if(!mymap[location]) {


                    board.has_bomb[randomNumber][randomNumber2] = true;
                    mymap[location] = true;
                    config_array[2]--;
        }
    }
    num_adjacent_tiles(board);
}


void Tiles::num_adjacent_tiles(Tiles &board){
    for (int i = 0; i < board.has_bomb.size(); i++) {
        for (int j = 0; j < board.has_bomb[0].size(); j++) {
            if(board.getBomb(i,j)){
                if (i - 1 >= 0 && j - 1 >= 0)
                    board.tile_numbers[i-1][j-1]++;
                if (i - 1 >= 0)
                    board.tile_numbers[i-1][j]++;
                if (i - 1 >= 0 && j + 1 < board.tile_vec[0].size())
                    board.tile_numbers[i-1][j+1]++;
                if (j - 1 >= 0)
                    board.tile_numbers[i][j-1]++;
                if(j + 1 < board.tile_vec[0].size())
                    board.tile_numbers[i][j+1]++;
                if(i + 1 < board.tile_vec.size() && j-1 >= 0)
                    board.tile_numbers[i+1][j-1]++;
                if(i + 1 < board.tile_vec.size())
                    board.tile_numbers[i+1][j]++;
                if(i + 1 < board.tile_vec.size() && j + 1 < board.tile_vec[0].size())
                    board.tile_numbers[i+1][j+1]++;
            }
        }
    }
}

int Tiles::check_flag_bomb(int bombs) {
    bool won = true;
    for (int i = 0; i < tile_vec.size(); i++) {
        for (int j = 0; j < tile_vec[0].size(); j++) {
            if(getStatus(i, j) != TileStatus::REVEALED && !getBomb(i,j)) {
                won = false;
            }
            if(getStatus(i,j) == TileStatus::REVEALED && getBomb(i,j)) {
                for (int d= 0; d < tile_vec.size(); d++) {
                    for (int a = 0; a < tile_vec[0].size(); a++) {
                        setStatus(d, a, TileStatus::REVEALED);
                    }
                }
                // Game Lost
                return 2;
            }
        }
    }
    if (won) {
        for (int d= 0; d < tile_vec.size(); d++) {
            for (int a = 0; a < tile_vec[0].size(); a++) {
                if (has_bomb[d][a])
                    setStatus(d, a, TileStatus::FLAG);
            }
        }
        // Game Won
        return 3;
    }
    // Game Continues
    return 1;
}

void Tiles::recursive_reveal(int x, int y) {
    if (tile_vec[x][y] != TileStatus::COVERED)
        return;
    tile_vec[x][y] = TileStatus::REVEALED;
    if (tile_numbers[x][y] == 0) {
        if (x - 1 >= 0 && y - 1 >= 0)
            recursive_reveal(x - 1,y - 1);
        if (x - 1 >= 0)
            recursive_reveal(x - 1,y);
        if (x - 1 >= 0 && y + 1 < tile_vec[0].size())
            recursive_reveal(x - 1,y + 1);
        if (y - 1 >= 0)
            recursive_reveal(x,y - 1);
        if(y + 1 < tile_vec[0].size())
            recursive_reveal(x,y + 1);
        if(x + 1 < tile_vec.size() && y - 1 >= 0)
            recursive_reveal(x + 1,y - 1);
        if(x + 1 < tile_vec.size())
            recursive_reveal(x + 1,y);
        if(x + 1 < tile_vec.size() && y + 1 < tile_vec[0].size())
            recursive_reveal(x + 1,y + 1);
    }
}





