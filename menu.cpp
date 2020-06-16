#include "menu.h"
#include "iostream"


Menu::Menu(const int &width,const int &height)
{
    if(!font.loadFromFile("font/arial.ttf"))
    {
        std::cerr<<"error to load font";
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

    option_menu[0].setFont(font);
    option_menu[0].setColor(sf::Color::Red);
    option_menu[0].setString("Full-Screen");
    option_menu[0].setCharacterSize(160);
    option_menu[0].setPosition(sf::Vector2f(width/2-450,height/2-250));

    option_menu[1].setFont(font);
    option_menu[1].setColor(sf::Color::Yellow);
    option_menu[1].setString("Windowed-Screen");
    option_menu[1].setCharacterSize(160);
    option_menu[1].setPosition(sf::Vector2f(width/2-680,height/2));


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

    coop_menu[0].setFont(font);
    coop_menu[0].setColor(sf::Color::Red);
    coop_menu[0].setString("Host a game");
    coop_menu[0].setCharacterSize(160);
    coop_menu[0].setPosition(sf::Vector2f(width/2-450,height/2-250));

    coop_menu[1].setFont(font);
    coop_menu[1].setColor(sf::Color::Yellow);
    coop_menu[1].setString("Join a game");
    coop_menu[1].setCharacterSize(160);
    coop_menu[1].setPosition(sf::Vector2f(width/2-430,height/2));

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

void Menu::option_menu_draw(sf::RenderWindow &window)
{
    for(int i=0; i<number_of_it_option; i++)
    {
        window.draw(option_menu[i]);
    }
}

void Menu::game_over_menu_draw(sf::RenderWindow &window)
{
    for(int i=0; i<number_of_it_game_over; i++)
    {
        window.draw(game_over_menu[i]);
    }
}

void Menu::coop_menu_draw(sf::RenderWindow &window)
{
    for(int i=0; i<number_of_it_coop_menu; i++)
    {
        window.draw(coop_menu[i]);
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
    if(actually_menu_==2)
        if(select_it -1>=0)
        {
            option_menu[select_it].setColor(sf::Color::Yellow);
            select_it--;
            option_menu[select_it].setColor(sf::Color::Red);
        }
    if(actually_menu_==3)
        if(select_it -1>=0)
        {
            game_over_menu[select_it].setColor(sf::Color::Yellow);
            select_it--;
            game_over_menu[select_it].setColor(sf::Color::Red);
        }
    if(actually_menu_==4)
        if(select_it -1>=0)
        {
            coop_menu[select_it].setColor(sf::Color::Yellow);
            select_it--;
            coop_menu[select_it].setColor(sf::Color::Red);
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
   if(actually_menu_==2)
        if(select_it +1<number_of_it_option)
         {
            option_menu[select_it].setColor(sf::Color::Yellow);
            select_it++;
            option_menu[select_it].setColor(sf::Color::Red);
         }
   if(actually_menu_==3)
       if(select_it +1<number_of_it_game_over)
       {
           game_over_menu[select_it].setColor(sf::Color::Yellow);
           select_it++;
           game_over_menu[select_it].setColor(sf::Color::Red);
       }
   if(actually_menu_==4)
       if(select_it+1<number_of_it_coop_menu)
       {
           coop_menu[select_it].setColor(sf::Color::Yellow);
           select_it++;
           coop_menu[select_it].setColor(sf::Color::Red);
       }
}

void Menu::refresh()
{
    main_menu[0].setColor(sf::Color::Red);
    main_menu[1].setColor(sf::Color::Yellow);
    main_menu[2].setColor(sf::Color::Yellow);
    play_menu[0].setColor(sf::Color::Red);
    play_menu[1].setColor(sf::Color::Yellow);
    option_menu[0].setColor(sf::Color::Red);
    option_menu[1].setColor(sf::Color::Yellow);
    game_over_menu[0].setColor(sf::Color::Red);
    game_over_menu[1].setColor(sf::Color::Yellow);
    coop_menu[0].setColor(sf::Color::Red);
    coop_menu[1].setColor(sf::Color::Yellow);
}

void Menu::setBackground(sf::RenderWindow &window)
{
    sf::Vector2f texture_size;
    sf::Vector2f windowSize(window.getSize().x,window.getSize().y);

    sf::Texture texture;
    if(actually_menu_==3)
    {
        if(!win)
        {
        texture.loadFromFile("picture/game_over.jpg");
        sf::Sprite menu_s;
        menu_s.setTexture(texture);
        texture_size.x=menu_s.getTextureRect().width;
        texture_size.y=menu_s.getTextureRect().height;

        menu_s.setScale(windowSize.x/texture_size.x,windowSize.y/texture_size.y);
        window.draw(menu_s);
        }
        else
        {
            texture.loadFromFile("picture/win_game.png");
            sf::Sprite menu_s;
            menu_s.setTexture(texture);
            texture_size.x=menu_s.getTextureRect().width;
            texture_size.y=menu_s.getTextureRect().height;

            menu_s.setScale(windowSize.x/texture_size.x,windowSize.y/texture_size.y);
            window.draw(menu_s);
        }
    }
    else
    {
        texture.loadFromFile("picture/menu.jpg");
        sf::Sprite menu_s;
        menu_s.setTexture(texture);
        texture_size.x=menu_s.getTextureRect().width;
        texture_size.y=menu_s.getTextureRect().height;

        menu_s.setScale(windowSize.x/texture_size.x,windowSize.y/texture_size.y);
        window.draw(menu_s);
    }
}

void Menu::actually_choose(const int &actually_menu)
{
    actually_menu_=actually_menu;
    select_it=0;
    refresh();
}

void Menu::GameOver(const bool &win_)
{
    win=win_;
    actually_menu_=3;
}
