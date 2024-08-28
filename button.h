#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
using namespace std;


#ifndef MINESWEEPER_BUTTON_H
#define MINESWEEPER_BUTTON_H




class Texture{
private:
    sf::Texture * happy_texture;
    sf::Texture * debug_texture;
    sf::Texture * pause_texture;
    sf::Texture * play_texture;
    sf::Texture * leaderboard_texture;
    sf::Texture * digits_texture;
    sf::Texture * sadface_texture;
    sf::Texture * coolface_texture;
    sf::Texture * flag_texture;
    sf::Texture * mine_texture;
    sf::Texture * tile_hidden_texture;
    sf::Texture * tile_revealed_texture;
    sf::Texture * num1_texture;
    sf::Texture * num2_texture;
    sf::Texture * num3_texture;
    sf::Texture * num4_texture;
    sf::Texture * num5_texture;
    sf::Texture * num6_texture;
    sf::Texture * num7_texture;
    sf::Texture * num8_texture;

    map<string, sf::Texture *> texturemap;
public:
    Texture(array<int, 3> config_array);
    sf::Texture& getTexture(string texturename);

    sf::Sprite Sprite_info(string name, int x, int y);

    sf::Texture& getDigit(int digit);

   void counter(array<int, 3> config_array,int flag_count, sf::RenderWindow &game_window);

    map<int, sf::Sprite> timer(array<int, 3> config_array, sf::RenderWindow &game_window);
};


#endif //MINESWEEPER_BUTTON_H
