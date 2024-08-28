#include <iostream>
#include <SFML/Graphics.hpp>
#include "readfile.h"
#include "button.h"
#include "Tiles.h"
#include <chrono>
#include <thread>
using namespace std;

int main() {
    int menu_switch = 0;

    // reading cols, row and mine into an array [1] is col, [2] is row, [3] is num_bombs
    array<int, 3> config_array;
    readConfig(config_array);
    int width, height, num_bombs;
    width = (config_array[0] * 32);
    height = (config_array[1] * 32) + 100;
    num_bombs = config_array[2];

    sf::Font welcome_font;
    if (!welcome_font.loadFromFile(
            "files/font.ttf")) {
        cout << "not working" << endl;
    }
    // welcome window
    if(menu_switch == 0) {
        menu_switch = create_welcome(width, height, welcome_font);
    }
    bool play_on = true;
    bool bombs_show = false;
    bool happy_sprite_time = false;
    int win = 1;
    int prevwon = win;
    int flag_count = num_bombs;
    if(menu_switch == 1) {
        sf::RenderWindow game_window(sf::VideoMode(width, height), "Minesweeper");
        // reads textures
        Texture generate_texture(config_array);
        // creates board
        Tiles board(config_array, generate_texture);
        board.randomize_bombs(config_array, board);

       //timer
        auto start_time = chrono::high_resolution_clock::now();
        int total_time = 0;
        auto pause_time = chrono::high_resolution_clock::now();


        while (game_window.isOpen()) {

            sf::Sprite happy_sprite;
            happy_sprite = generate_texture.Sprite_info("happy_face",((float(config_array[0])/2.0f) *32) - 32, 32 * (float(config_array[1]) + 0.5f));

            sf::Sprite lose_sprite;
            lose_sprite = generate_texture.Sprite_info("sad_face",((float(config_array[0])/2.0f) *32) - 32, 32 * (float(config_array[1]) + 0.5f));

            sf::Sprite win_sprite;
            win_sprite = generate_texture.Sprite_info("cool_face",((float(config_array[0])/2.0f) *32) - 32, 32 * (float(config_array[1]) + 0.5f));

            sf::Sprite debug_sprite;
            debug_sprite = generate_texture.Sprite_info("debug_bomb",(float(config_array[0])*32) -304, 32 * (float(config_array[1]) + 0.5f));

            sf::Sprite pause_sprite;
            pause_sprite =  generate_texture.Sprite_info( "pause",(float(config_array[0])*32) - 240, 32 * (float(config_array[1]) + 0.5f));

            sf::Sprite play_sprite;
            play_sprite = generate_texture.Sprite_info("play",(float(config_array[0])*32) - 240, 32 * (float(config_array[1]) + 0.5f));

            sf::Sprite leaderboard_sprite;
            leaderboard_sprite = generate_texture.Sprite_info( "leaderboard",(float(config_array[0])*32) - 176, 32 * (float(config_array[1]) + 0.5f));

            sf::Sprite reveal_tiles;
            reveal_tiles.setTexture(generate_texture.getTexture("tile_revealed"));

            sf::Event event;
            while (game_window.pollEvent(event)) {
                int x_position = event.mouseButton.x/32;
                int y_position = event.mouseButton.y/32;

                if (event.type == sf::Event::Closed) {
                    game_window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        game_window.close();
                        //leaderboard = true;
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left && play_on) {

                        if(win == 1 && x_position < config_array[0] && y_position < config_array[1] && board.getStatus(x_position, y_position) == TileStatus::COVERED){
                            board.recursive_reveal(x_position,y_position);
                            board.setStatus(x_position, y_position, TileStatus::REVEALED);
                        }

                        cout << "X: "<< x_position << " Y: " << y_position << endl;



                        if (happy_sprite.getGlobalBounds().contains({(float)event.mouseButton.x, (float)event.mouseButton.y})){
                            win = 1;
                            for (int i = 0; i < board.tile_vec.size(); i++) {
                                for (int j = 0; j < board.tile_vec[0].size(); j++) {
                                    board.setStatus(i,j, TileStatus::COVERED);
                                }
                            }
                            board.randomize_bombs(config_array, board);
                            flag_count = num_bombs;
                            // working here
                            happy_sprite_time = !happy_sprite_time;
                        }

                        if (win == 1 && debug_sprite.getGlobalBounds().contains({(float)event.mouseButton.x, (float)event.mouseButton.y})) {
                            bombs_show = !bombs_show;
                            cout << "SPRITE CLICKED" << endl;
                        }
                    }
                    // Handles the leaderboard
                    if (leaderboard_sprite.getGlobalBounds().contains({(float)event.mouseButton.x, (float)event.mouseButton.y})) {
                        create_leaderboard(config_array, welcome_font);
                        cout << "SPRITE CLICKED" << endl;
                    }

                    // Handles clicking the pause sprite
                    if (win == 1 && event.mouseButton.button == sf::Mouse::Left && pause_sprite.getGlobalBounds().contains({(float)event.mouseButton.x, (float)event.mouseButton.y})) {
                        play_on = !play_on;

                        // working here
                        pause_time = chrono::high_resolution_clock::now();
                        cout << "SPRITE CLICKED" << endl;
                    }
                    // Handles placing and removing flag
                    if (event.mouseButton.button == sf::Mouse::Right && play_on && win == 1) {
                        // doesnt allow flags on uncovered tiles
                        if(board.getStatus(x_position, y_position) == TileStatus::REVEALED){
                            break;
                        }
                        //takes away flag
                        if(board.getStatus(x_position, y_position) == TileStatus::FLAG) {
                            board.setStatus(x_position, y_position, TileStatus::COVERED);
                            flag_count ++;
                            cout << "Flag needs to disappear" << endl;
                            cout << "Flag count is " << flag_count << endl;
                        }
                        // sets flag
                        else{
                            board.setStatus(x_position, y_position, TileStatus::FLAG);
                            flag_count --;
                            cout << "Flag count is " << flag_count << endl;
                        }
                    }
                    // WORKING HERE
                    win = board.check_flag_bomb(num_bombs);
                }
            }


            // Draw it
            game_window.clear(sf::Color::White);
            //Counter(left side)
            generate_texture.counter(config_array, flag_count, game_window);

            if(win == 1) {
                game_window.draw(happy_sprite);
            }
            if(win == 2){
                game_window.draw(lose_sprite);
            }
            if (win == 3){
                game_window.draw(win_sprite);
            }

            game_window.draw(debug_sprite);


            // working

            map<int, sf::Sprite> timer_sprites = generate_texture.timer(config_array, game_window);


            auto current_time = chrono::high_resolution_clock::now();
            auto reserve_time = chrono::high_resolution_clock::now();
            auto game_duration = std::chrono::duration_cast<std::chrono::seconds>(current_time-start_time);
            total_time = game_duration.count();

            if(happy_sprite_time){
                total_time = 0;

            }
            if(!play_on){
                auto gamepause_duration = std::chrono::duration_cast<std::chrono::seconds>(current_time-pause_time);
                total_time -= gamepause_duration.count();
            }

            int seconds = total_time % 60;
            int minutes = total_time / 60;

            int min_division = minutes / 10;
            int sec_division = seconds / 10;


            int min_place0 = min_division % 10;
            int min_place1 = minutes % 10;

            int sec_place0 = sec_division % 10;
            int sec_place1 = seconds % 10;

            int x_sprite = (config_array[0] * 32);
            int y_sprite = 32 * (float(config_array[1]) + 0.5f) + 16;


            timer_sprites[min_place0].setPosition(x_sprite - 97, y_sprite);
            game_window.draw(timer_sprites[min_place0]);

            timer_sprites[min_place1].setPosition(x_sprite - 76, y_sprite);
            game_window.draw(timer_sprites[min_place1]);

            timer_sprites[sec_place0].setPosition(x_sprite - 54, y_sprite);
            game_window.draw(timer_sprites[sec_place0]);

            timer_sprites[sec_place1].setPosition(x_sprite - 33, y_sprite);
            game_window.draw(timer_sprites[sec_place1]);

            game_window.draw(leaderboard_sprite);

            board.render(game_window, bombs_show);

            if(!play_on){
                game_window.draw(play_sprite);
                for (int i = 0; i < board.tile_vec.size(); i++) {
                    for (int j = 0; j < board.tile_vec[0].size(); j++) {
                        reveal_tiles.setPosition(i* 32,j* 32);
                        game_window.draw(reveal_tiles);
                    }
                }

            }
            else {
                game_window.draw(pause_sprite);
            }

            game_window.display();

            if (win == 3 && prevwon != 3)
                create_leaderboard(config_array, welcome_font);
            prevwon = win;



        }
    }
    return 0;
}