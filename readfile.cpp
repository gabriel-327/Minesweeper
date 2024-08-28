#include <fstream>
#include "readfile.h"
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
using namespace std;

void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

string checkTypedVal(int key_num) {
    map<int, string> letter_map;

    for(int i = 0; i < 26; i++){
        letter_map[i] = 'A' + i;
    }
    string return_str;
    map<int, string>::iterator iter;
    iter = letter_map.begin();
    for(; iter!= letter_map.end(); iter++){
        if(key_num == iter->first){
            return_str = iter->second;
        }
    }
    return return_str;
}

void readConfig(array<int, 3> &info) {
    ifstream readconfig;
    readconfig.open("files/config.cfg");
    int col_count;
    int row_count;
    int mine_count;

    try {
        string temp;
        getline(readconfig, temp);
        col_count = stoi(temp);
        getline(readconfig, temp);
        row_count = stoi(temp);
        getline(readconfig, temp);
        mine_count = stoi(temp);
        readconfig.close();
        info[0] = col_count;
        info[1] = row_count;
        info[2] = mine_count;
    }
    catch(exception &e){
        cout << "here is the problem" << endl;
    }
}

vector<string> readLeaderboard() {
    ifstream readleaderboard;
    readleaderboard.open("files/leaderboard.txt");

    string temp;
    vector<string> leaderboard_vec;
    while(readleaderboard) {
        getline(readleaderboard, temp, ',');
        leaderboard_vec.push_back(temp);
        getline(readleaderboard, temp, '\n');
        leaderboard_vec.push_back(temp);
    }
    readleaderboard.close();
    for (const auto& element : leaderboard_vec) {
        // Print the current element
        std::cout << element << std::endl;
    }
    return leaderboard_vec;
}

void create_leaderboard(array<int, 3> &config_array, sf::Font welcome_font) {
    sf::RenderWindow leaderboard_window(sf::VideoMode(config_array[0]*16,(config_array[1]*16) + 50), "Leaderboard");

    sf::Text leaderboard_text("LEADERBOARD", welcome_font, 20);
    leaderboard_text.setFillColor(sf::Color::White);
    leaderboard_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(leaderboard_text, (config_array[0] * 16) / 2, ( ((config_array[1] * 16) + 50) / 2) - 120);

    string all_names;
    vector<string> leaderboard_vec;
    leaderboard_vec = readLeaderboard();
    string first = "1.\t" + leaderboard_vec[0] + "\t" + leaderboard_vec[1] + "\n\n";
    string second = "2.\t" + leaderboard_vec[2] + "\t" + leaderboard_vec[3] + "\n\n";
    string third = "3.\t" + leaderboard_vec[4] + "\t" + leaderboard_vec[5] + "\n\n";
    string four = "4.\t" + leaderboard_vec[6] + "\t" + leaderboard_vec[7] + "\n\n";
    string five = "2.\t" + leaderboard_vec[8] + "\t" + leaderboard_vec[9] + "\n\n";

    all_names = first + second + third + four + five;

    sf::Text player_data;
    player_data.setString(all_names);
    player_data.setFont(welcome_font);
    player_data.setCharacterSize(18);
    player_data.setFillColor(sf::Color::White);
    player_data.setStyle(sf::Text::Bold);
    setText(player_data, (config_array[0] * 16) / 2, ( ((config_array[1] * 16) + 50) / 2) + 20);




    while (leaderboard_window.isOpen()) {
        sf::Event event;
        while (leaderboard_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderboard_window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
            }
        }
        leaderboard_window.clear(sf::Color::Blue);
        leaderboard_window.draw(leaderboard_text);
        leaderboard_window.draw(player_data);
        leaderboard_window.display();

    }
}

int create_welcome(int width, int height, sf::Font welcome_font) {
    sf::RenderWindow welcome_window(sf::VideoMode(width, height), "Minesweeper");

    // creates welcome welcome_window welcome_text
    sf::Text welcome_text("WELCOME TO MINESWEEPER!", welcome_font, 24);
    welcome_text.setFillColor(sf::Color::White);
    welcome_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(welcome_text, width / 2, height / 2 - 150);

    sf::Text name_text("Enter your name:", welcome_font, 20);
    name_text.setFillColor(sf::Color::White);
    name_text.setStyle(sf::Text::Bold);
    setText(name_text, width / 2, height / 2 - 75);

    string whole_word = "";
    string buffer = "";
    string bar = "|";

    while (welcome_window.isOpen()) {
        sf::Text typed_text(buffer, welcome_font, 18);
        typed_text.setFillColor(sf::Color::Yellow);
        typed_text.setStyle(sf::Text::Bold);
        setText(typed_text, width / 2, height / 2 - 45);

        sf::Event event;
        while (welcome_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                welcome_window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                string letter_typed = checkTypedVal(event.key.code);
                if (event.key.code == sf::Keyboard::Backspace) {
                    if (!whole_word.empty()) {
                        whole_word.pop_back();
                    }
                }
                if (event.key.code == sf::Keyboard::Enter && whole_word.size()!= 0) {
                    welcome_window.close();
                    Player newplayer(whole_word);
                    return 1;
                }
                if (event.key.code >= 0 && event.key.code <= 25) {
                    if (whole_word.size() < 10) {
                        if (whole_word == "") {
                            whole_word += letter_typed;
                        }
                        else {
                            char lowercase;
                            lowercase = tolower(letter_typed[0]);
                            whole_word += lowercase;
                        }
                    }
                }
            }
        }
        //three-step showing process, clear welcome_window, draw what you want to draw, finally display
        welcome_window.clear(sf::Color::Blue);
        welcome_window.draw(welcome_text);
        welcome_window.draw(name_text);
        welcome_window.draw(typed_text);
        buffer = whole_word;
        buffer += bar;
        welcome_window.display();
    }
}


Player::Player(string &name, int time) {
    this->name = name;
    this->time = time;
}


