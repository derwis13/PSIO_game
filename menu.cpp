#include "menu.h"



Menu::Menu(const int &width,const int &height)
{
    if(!font.loadFromFile("arial.ttf"))
    {
    }
    main_menu[0].setFont(font);
    main_menu[0].setColor(sf::Color::Red);
    main_menu[0].setString("Play");
    main_menu[0].setCharacterSize(200);
    main_menu[0].setPosition(sf::Vector2f(width/2-200,height/6));


    main_menu[1].setFont(font);
    main_menu[1].setColor(sf::Color::Yellow);
    main_menu[1].setString("Options");
    main_menu[1].setCharacterSize(100);
    main_menu[1].setPosition(sf::Vector2f(width/2-200,height/2-50));


    main_menu[2].setFont(font);
    main_menu[2].setColor(sf::Color::Yellow);
    main_menu[2].setString("Exit");
    main_menu[2].setCharacterSize(100);
    main_menu[2].setPosition(sf::Vector2f(width/2-100,height/2+50));

    play_menu[0].setFont(font);
    play_menu[0].setColor(sf::Color::Red);
    play_menu[0].setString("Singleplayer");
    play_menu[0].setCharacterSize(160);
    play_menu[0].setPosition(sf::Vector2f(width/2-450,height/2-250));

    play_menu[1].setFont(font);
    play_menu[1].setColor(sf::Color::Yellow);
    play_menu[1].setString("Coop mode");
    play_menu[1].setCharacterSize(160);
    play_menu[1].setPosition(sf::Vector2f(width/2-430,height/2));


    game_over_menu[0].setFont(font);
    game_over_menu[0].setColor(sf::Color::Red);
    game_over_menu[0].setString("Start over");
    game_over_menu[0].setCharacterSize(100);
    game_over_menu[0].setPosition(sf::Vector2f(width/2-210,height/2-150));

    game_over_menu[1].setFont(font);
    game_over_menu[1].setColor(sf::Color::Yellow);
    game_over_menu[1].setString("Exit");
    game_over_menu[1].setCharacterSize(100);
    game_over_menu[1].setPosition(sf::Vector2f(width/2-80,height/2));
    select_it=0;
}

void Menu::main_menu_draw(sf::RenderWindow &window)
{
    for(int i=0; i<number_of_it_main_menu; i++)
    {
        window.draw(main_menu[i]);
    }
}

void Menu::play_menu_draw(sf::RenderWindow &window)
{
    for(int i=0; i<number_of_it_play_menu; i++)
    {
        window.draw(play_menu[i]);
    }
}

void Menu::game_over_menu_draw(sf::RenderWindow &window)
{
    for(int i=0; i<number_of_it_game_over; i++)
    {
        window.draw(game_over_menu[i]);
    }
}

void Menu::MoveUp()
{
    if(actually_menu_==0)
        if(select_it -1>=0)
        {
            main_menu[select_it].setColor(sf::Color::Yellow);
            select_it--;
            main_menu[select_it].setColor(sf::Color::Red);
        }
    if(actually_menu_==1)
        if(select_it -1>=0)
        {
            play_menu[select_it].setColor(sf::Color::Yellow);
            select_it--;
            play_menu[select_it].setColor(sf::Color::Red);
        }
    if(actually_menu_==3)
        if(select_it -1>=0)
        {
            game_over_menu[select_it].setColor(sf::Color::Yellow);
            select_it--;
            game_over_menu[select_it].setColor(sf::Color::Red);
        }
}

void Menu::MoveDown()
{
    if(actually_menu_==0)
        if(select_it +1<number_of_it_main_menu)
        {
            main_menu[select_it].setColor(sf::Color::Yellow);
            select_it++;
            main_menu[select_it].setColor(sf::Color::Red);
        }
   if(actually_menu_==1)
        if(select_it +1<number_of_it_play_menu)
         {
            play_menu[select_it].setColor(sf::Color::Yellow);
            select_it++;
            play_menu[select_it].setColor(sf::Color::Red);
         }
   if(actually_menu_==3)
       if(select_it +1<number_of_it_game_over)
       {
           game_over_menu[select_it].setColor(sf::Color::Yellow);
           select_it++;
           game_over_menu[select_it].setColor(sf::Color::Red);
       }
}

void Menu::setBackground(sf::RenderWindow &window)
{
    sf::Texture texture;
    if(actually_menu_==3)
    {
        texture.loadFromFile("game_over.jpg");
        sf::Sprite menu_s;
        menu_s.setTexture(texture);
        menu_s.setScale(0.65,0.7);
        window.draw(menu_s);
    }
    else
    {
        texture.loadFromFile("menu.jpg");
        sf::Sprite menu_s;
        menu_s.setTexture(texture);
        menu_s.setScale(2,2.7);
        window.draw(menu_s);
    }
}

void Menu::actually_choose(const int &actually_menu)
{
    actually_menu_=actually_menu;
    select_it=0;
}

void Menu::GameOver()
{
    actually_menu_=3;
}
