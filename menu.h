#pragma once
#include <SFML/Graphics.hpp>

#define number_of_it_main_menu 3
#define number_of_it_play_menu 2
#define number_of_it_game_over 2
#define number_of_it_coop_menu 2
#define number_of_it_option 2
class Menu
{
public:
    Menu(const int &width,const int &height);

    int actually_menu_=0;
    void main_menu_draw(sf::RenderWindow &window);
    void option_menu_draw(sf::RenderWindow &window);
    void play_menu_draw(sf::RenderWindow &window);
    void game_over_menu_draw(sf::RenderWindow &window);
    void coop_menu_draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    void setBackground(sf::RenderWindow &window);
    void actually_choose(const int &actually_menu);
    int  getItem(){return select_it;}
    void GameOver(const bool &win_);
private:
    bool win=true;
    int select_it;
    sf::Font font;
    sf::Text main_menu[number_of_it_main_menu];
    sf::Text play_menu[number_of_it_play_menu];
    sf::Text game_over_menu[number_of_it_game_over];
    sf::Text coop_menu[number_of_it_coop_menu];
    sf::Text option_menu[number_of_it_option];
    void refresh();



};

