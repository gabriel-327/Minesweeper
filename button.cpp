#include <fstream>
#include <map>
#include <SFML/Graphics.hpp>
using namespace std;
#include "button.h"
#include "Tiles.h"

Texture::Texture(array<int, 3> config_array) {
    happy_texture = new sf::Texture();
    debug_texture = new sf::Texture();
    pause_texture = new sf::Texture();
    play_texture = new sf::Texture();
    leaderboard_texture = new sf::Texture();
    digits_texture = new sf::Texture();
    sadface_texture = new sf::Texture();
    coolface_texture = new sf::Texture();
    flag_texture = new sf::Texture();
    mine_texture = new sf::Texture();
    tile_hidden_texture = new sf::Texture();
    tile_revealed_texture = new sf::Texture();
    num1_texture = new sf::Texture();
    num2_texture = new sf::Texture();
    num3_texture = new sf::Texture();
    num4_texture = new sf::Texture();
    num5_texture = new sf::Texture();
    num6_texture = new sf::Texture();
    num7_texture = new sf::Texture();
    num8_texture = new sf::Texture();
    happy_texture->loadFromFile(
            "files/images/face_happy.png");
    debug_texture->loadFromFile(
            "files/images/debug.png");
    pause_texture->loadFromFile(
            "files/images/pause.png");
    play_texture->loadFromFile(
            "files/images/play.png");
    leaderboard_texture->loadFromFile(
            "files/images/leaderboard.png");
    digits_texture->loadFromFile(
            "files/images/digits.png");
    sadface_texture->loadFromFile(
            "files/images/face_lose.png");
    coolface_texture->loadFromFile(
            "files/images/face_win.png");
    flag_texture->loadFromFile(
            "files/images/flag.png");
    mine_texture->loadFromFile(
            "files/images/mine.png");
    tile_hidden_texture->loadFromFile(
            "files/images/tile_hidden.png");
    tile_revealed_texture->loadFromFile(
            "files/images/tile_revealed.png");
    num1_texture->loadFromFile(
            "files/images/number_1.png");
    num2_texture->loadFromFile(
            "files/images/number_2.png");
    num3_texture->loadFromFile(
            "files/images/number_3.png");
    num4_texture->loadFromFile(
            "files/images/number_4.png");
    num5_texture->loadFromFile(
            "files/images/number_5.png");
    num6_texture->loadFromFile(
            "files/images/number_6.png");
    num7_texture->loadFromFile(
            "files/images/number_7.png");
    num8_texture->loadFromFile(
            "files/images/number_8.png");

    texturemap.insert({"happy_face", happy_texture});
    texturemap.insert({"debug_bomb", debug_texture});
    texturemap.insert({"pause", pause_texture});
    texturemap.insert({"play", play_texture});
    texturemap.insert({"leaderboard", leaderboard_texture});
    texturemap.insert({"digits", digits_texture});
    texturemap.insert({"sad_face", sadface_texture});
    texturemap.insert({"cool_face", coolface_texture});
    texturemap.insert({"flag", flag_texture});
    texturemap.insert({"mine", mine_texture});
    texturemap.insert({"tile_hidden", tile_hidden_texture});
    texturemap.insert({"tile_revealed", tile_revealed_texture});
    texturemap.insert({"num_1", num1_texture});
    texturemap.insert({"num_2", num2_texture});
    texturemap.insert({"num_3", num3_texture});
    texturemap.insert({"num_4", num4_texture});
    texturemap.insert({"num_5", num5_texture});
    texturemap.insert({"num_6", num6_texture});
    texturemap.insert({"num_7", num7_texture});
    texturemap.insert({"num_8", num8_texture});
}

sf::Texture& Texture::getTexture(string texturename) {
    return *texturemap[texturename];
}


sf::Sprite Texture::Sprite_info(string name, int x, int y){
    sf::Sprite happy_sprite;
    happy_sprite.setTexture(getTexture(name));
    happy_sprite.setPosition((float)x, (float)y);
    return happy_sprite;
}

sf::Texture &Texture::getDigit(int digit) {
        return getTexture("num_" + to_string(digit));
}

void Texture::counter(array<int, 3> config_array, int flag_count, sf::RenderWindow &game_window) {
    map<char, sf::Sprite> number_map;
    sf::Sprite sprite_digit_0;
    sprite_digit_0.setTexture(getTexture("digits"));
    sprite_digit_0.setTextureRect(sf::IntRect(0, 0, 21, 32));
    number_map['0'] = sprite_digit_0;

    sf::Sprite sprite_digit_1;
    sprite_digit_1.setTexture(getTexture("digits"));
    sprite_digit_1.setTextureRect(sf::IntRect(21, 0, 21, 32));
    number_map['1'] = sprite_digit_1;

    sf::Sprite sprite_digit_2;
    sprite_digit_2.setTexture(getTexture("digits"));
    sprite_digit_2.setTextureRect(sf::IntRect(42, 0, 21, 32));
    number_map['2'] = sprite_digit_2;

    sf::Sprite sprite_digit_3;
    sprite_digit_3.setTexture(getTexture("digits"));
    sprite_digit_3.setTextureRect(sf::IntRect(63, 0, 21, 32));
    number_map['3'] = sprite_digit_3;

    sf::Sprite sprite_digit_4;
    sprite_digit_4.setTexture(getTexture("digits"));
    sprite_digit_4.setTextureRect(sf::IntRect(84, 0, 21, 32));
    number_map['4'] = sprite_digit_4;

    sf::Sprite sprite_digit_5;
    sprite_digit_5.setTexture(getTexture("digits"));
    sprite_digit_5.setTextureRect(sf::IntRect(105, 0, 21, 32));
    number_map['5'] = sprite_digit_5;

    sf::Sprite sprite_digit_6;
    sprite_digit_6.setTexture(getTexture("digits"));
    sprite_digit_6.setTextureRect(sf::IntRect(126, 0, 21, 32));
    number_map['6'] = sprite_digit_6;

    sf::Sprite sprite_digit_7;
    sprite_digit_7.setTexture(getTexture("digits"));
    sprite_digit_7.setTextureRect(sf::IntRect(147, 0, 21, 32));
    number_map['7'] = sprite_digit_7;

    sf::Sprite sprite_digit_8;
    sprite_digit_8.setTexture(getTexture("digits"));
    sprite_digit_8.setTextureRect(sf::IntRect(168, 0, 21, 32));
    number_map['8'] = sprite_digit_8;

    sf::Sprite sprite_digit_9;
    sprite_digit_9.setTexture(getTexture("digits"));
    sprite_digit_9.setTextureRect(sf::IntRect(189, 0, 21, 32));
    number_map['9'] = sprite_digit_9;

    sf::Sprite sprite_digit_negative;
    sprite_digit_negative.setTexture(getTexture("digits"));
    sprite_digit_negative.setTextureRect(sf::IntRect(210, 0, 21, 32));
    number_map['-'] = sprite_digit_negative;

    string buffer;
    sf::Sprite sprite_buffer;
    sf::Sprite zero;
    buffer = to_string(flag_count);
    // 5 0
    int num_digits = buffer.size();
    float y_value = 32 * (float(config_array[1]) + 0.5f) + 16;

    if(num_digits == 3 && flag_count > 0){
        sprite_buffer = number_map[buffer[0]];
        sprite_buffer.setPosition(33, y_value);
        game_window.draw(sprite_buffer);

        sprite_buffer = number_map[buffer[1]];
        sprite_buffer.setPosition(54, y_value);
        game_window.draw(sprite_buffer);
        sprite_buffer = number_map[buffer[1]];
        sprite_buffer.setPosition(75, y_value);
        game_window.draw(sprite_buffer);
    }

    if(num_digits == 2 && flag_count > 0){
        zero = number_map['0'];
        zero.setPosition(33, y_value);
        game_window.draw(zero);

        sprite_buffer = number_map[buffer[0]];
        sprite_buffer.setPosition(54, y_value);
        game_window.draw(sprite_buffer);

        sprite_buffer = number_map[buffer[1]];
        sprite_buffer.setPosition(75, y_value);
        game_window.draw(sprite_buffer);
    }

    if(num_digits == 1 && flag_count > 0){
        zero = number_map['0'];
        zero.setPosition(33, y_value);
        game_window.draw(zero);

        sprite_buffer = number_map['0'];
        sprite_buffer.setPosition(54, y_value);
        game_window.draw(sprite_buffer);

        sprite_buffer = number_map[buffer[0]];
        sprite_buffer.setPosition(75, y_value);
        game_window.draw(sprite_buffer);
    }

    if(flag_count == 0){
        zero = number_map['0'];
        zero.setPosition(33, y_value);
        game_window.draw(zero);

        sprite_buffer = number_map['0'];
        sprite_buffer.setPosition(54, y_value);
        game_window.draw(sprite_buffer);

        sprite_buffer = number_map['0'];
        sprite_buffer.setPosition(75, y_value);
        game_window.draw(sprite_buffer);
    }
    //-100
    if(num_digits == 4 && flag_count < 0){
        zero = number_map['-'];
        zero.setPosition(12, y_value);
        game_window.draw(zero);

        sprite_buffer = number_map[buffer[1]];
        sprite_buffer.setPosition(33, y_value);
        game_window.draw(sprite_buffer);

        sprite_buffer = number_map[buffer[2]];
        sprite_buffer.setPosition(54, y_value);
        game_window.draw(sprite_buffer);

        sprite_buffer = number_map[buffer[3]];
        sprite_buffer.setPosition(75, y_value);
        game_window.draw(sprite_buffer);
    }
    // -010
    if(num_digits == 3 && flag_count < 0){
        zero = number_map['-'];
        zero.setPosition(12, y_value);
        game_window.draw(zero);

        sprite_buffer = number_map['0'];
        sprite_buffer.setPosition(33, y_value);
        game_window.draw(sprite_buffer);

        sprite_buffer = number_map[buffer[1]];
        sprite_buffer.setPosition(54, y_value);
        game_window.draw(sprite_buffer);

        sprite_buffer = number_map[buffer[2]];
        sprite_buffer.setPosition(75, y_value);
        game_window.draw(sprite_buffer);
    }

    if(num_digits == 2 && flag_count < 0){
        zero = number_map['-'];
        zero.setPosition(12, y_value);
        game_window.draw(zero);

        sprite_buffer = number_map['0'];
        sprite_buffer.setPosition(33, y_value);
        game_window.draw(sprite_buffer);

        sprite_buffer = number_map['0'];
        sprite_buffer.setPosition(54, y_value);
        game_window.draw(sprite_buffer);

        sprite_buffer = number_map[buffer[1]];
        sprite_buffer.setPosition(75, y_value);
        game_window.draw(sprite_buffer);
    }


}

map<int, sf::Sprite> Texture::timer(array<int, 3> config_array, sf::RenderWindow &game_window) {
    map<int, sf::Sprite> number_map;
    sf::Sprite sprite_digit_0;
    sprite_digit_0.setTexture(getTexture("digits"));
    sprite_digit_0.setTextureRect(sf::IntRect(0, 0, 21, 32));
    number_map[0] = sprite_digit_0;

    sf::Sprite sprite_digit_1;
    sprite_digit_1.setTexture(getTexture("digits"));
    sprite_digit_1.setTextureRect(sf::IntRect(21, 0, 21, 32));
    number_map[1] = sprite_digit_1;

    sf::Sprite sprite_digit_2;
    sprite_digit_2.setTexture(getTexture("digits"));
    sprite_digit_2.setTextureRect(sf::IntRect(42, 0, 21, 32));
    number_map[2] = sprite_digit_2;

    sf::Sprite sprite_digit_3;
    sprite_digit_3.setTexture(getTexture("digits"));
    sprite_digit_3.setTextureRect(sf::IntRect(63, 0, 21, 32));
    number_map[3] = sprite_digit_3;

    sf::Sprite sprite_digit_4;
    sprite_digit_4.setTexture(getTexture("digits"));
    sprite_digit_4.setTextureRect(sf::IntRect(84, 0, 21, 32));
    number_map[4] = sprite_digit_4;

    sf::Sprite sprite_digit_5;
    sprite_digit_5.setTexture(getTexture("digits"));
    sprite_digit_5.setTextureRect(sf::IntRect(105, 0, 21, 32));
    number_map[5] = sprite_digit_5;

    sf::Sprite sprite_digit_6;
    sprite_digit_6.setTexture(getTexture("digits"));
    sprite_digit_6.setTextureRect(sf::IntRect(126, 0, 21, 32));
    number_map[6] = sprite_digit_6;

    sf::Sprite sprite_digit_7;
    sprite_digit_7.setTexture(getTexture("digits"));
    sprite_digit_7.setTextureRect(sf::IntRect(147, 0, 21, 32));
    number_map[7] = sprite_digit_7;

    sf::Sprite sprite_digit_8;
    sprite_digit_8.setTexture(getTexture("digits"));
    sprite_digit_8.setTextureRect(sf::IntRect(168, 0, 21, 32));
    number_map[8] = sprite_digit_8;

    sf::Sprite sprite_digit_9;
    sprite_digit_9.setTexture(getTexture("digits"));
    sprite_digit_9.setTextureRect(sf::IntRect(189, 0, 21, 32));
    number_map[9] = sprite_digit_9;

    sf::Sprite sprite_0;
    sf::Sprite sprite_1;
    sf::Sprite sprite_2;
    sf::Sprite sprite_3;

    return number_map;
}

