#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <math.h>
#include <string>

#include "world.h"
#include "Character.h"
#include "menu.h"


void Load_Texture(const std::string &nazwa,std::vector<GLuint> &Texturs,
                  unsigned int i);

float Hero::rot;

int main() {
    float eyex=0;
    float eyey=5;
    float eyez=3;

    float pos_e_x=0;
    float pos_e_y=5;
    float pos_e_z=1;

    float centerx=eyex;
    float centery=eyey+1;
    float centerz=eyez;

    sf::RenderWindow window1(sf::VideoMode(1024, 768), "Try to get out");
    Menu menu(window1.getSize().x, window1.getSize().y);
    while (window1.isOpen())
    {
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window1.close();
            }
            if(event.type==sf::Event::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::Up or
                        event.key.code==sf::Keyboard::W)
                    menu.MoveUp();
                if(event.key.code==sf::Keyboard::Down or
                        event.key.code==sf::Keyboard::S)
                    menu.MoveDown();
                if(event.key.code==sf::Keyboard::Escape)
                    menu.actually_choose(0);
                if(event.key.code==sf::Keyboard::Enter and menu.actually_menu_==0)
                {
                    switch (menu.getItem())
                    {
                    case 0:
                        std::cout<<"Play is pressed"<<std::endl;
                        menu.actually_choose(1);
                        break;
                    case 1:
                        std::cout<<"Option is pressed"<<std::endl;
                        break;
                    case 2:
                        std::cout<<"Exit is pressed"<<std::endl;
                        window1.close();
                        exit(0);
                        break;
                    }
                    break;
                }
                if(event.key.code==sf::Keyboard::Enter and menu.actually_menu_==1)
                        switch (menu.getItem())
                        {
                        case 0:
                            std::cout<<"Singleplayer is pressed"<<std::endl;
                            window1.close();
                            break;
                        case 1:
                            std::cout<<"Coop mode is pressed, but option not available"<<std::endl;
                            break;
                        }
            }
        }
        window1.clear();
        menu.setBackground(window1);
        if(menu.actually_menu_==0)
        {
            menu.main_menu_draw(window1);
        }
        if(menu.actually_menu_==1)
        {
            menu.play_menu_draw(window1);
        }
        window1.display();

    }
    Character *character1,*character2;
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Try to get out", sf::Style::Default, sf::ContextSettings(32));

    window.setVerticalSyncEnabled(true);

    window.setActive(true);
    std::vector<GLuint>Texturs;

    Load_Texture("wall.png",Texturs,Texturs.size());
    Load_Texture("grass.png",Texturs,Texturs.size());
    Load_Texture("my_head1.jpg",Texturs,Texturs.size());
    Load_Texture("devil.jpg",Texturs,Texturs.size());

    glClearColor(0.3,0,0,0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SMOOTH);
    glShadeModel(GL_SMOOTH);



    GLfloat light_position[] = { 2.0, 0.0, 2.0, 1.0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };

    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    GLfloat global_ambient[] = {0.3, 0.3, 0.3, 0.1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glEnable(GL_NORMALIZE) ;
    bool running = true;

    world *map;

    sf::Clock clock;
    sf::Clock time_of_game;
    set_viewport(window.getSize().x, window.getSize().y,eyex,eyey,eyez,centerx,centery,centerz);

    while (running) {
        sf::Event event;
        window.setFramerateLimit(60);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }

            if(event.mouseWheelScroll.delta==-1)
            {
                eyez-=1;
            }
            if(event.mouseWheelScroll.delta==1)
            {
                eyez+=1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                Hero::rotate_Character(0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                Hero::rotate_Character(90);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                Hero::rotate_Character(-90);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                Hero::rotate_Character(180);
            static sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            int temp_mouse_pos_x=mouse_pos.x;
            mouse_pos = sf::Mouse::getPosition(window);
            float mouse_sensitivity=2;
            camera_setting(mouse_sensitivity,temp_mouse_pos_x,mouse_pos,clock,
                           eyex,eyey,centerx,centery);

            set_viewport(window.getSize().x, window.getSize().y,
                         eyex,eyey,eyez,centerx,centery,centerz);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
        glEnable (GL_COLOR_MATERIAL);


        map=new world(Texturs);
        character1 =new Hero(eyex,eyey+3,1,Texturs[2]);
        std::vector<char> list_of_move;
        if(time_of_game.getElapsedTime().asSeconds()>=15)
        {
            character2 =new Enemy(pos_e_x,pos_e_y,pos_e_z,Texturs[3]);
            int temp_pos_e_x=ceil(pos_e_x);
            int temp_pos_e_y=ceil(pos_e_y);
            find_path(eyex,eyey+5,temp_pos_e_x,temp_pos_e_y,list_of_move,map);
            int speed_e=2;
            if(list_of_move.size()!=0)
            {
                if(list_of_move[0]=='r')
                    pos_e_x+=speed_e*clock.getElapsedTime().asSeconds();
                if(list_of_move[0]=='l')
                    pos_e_x-=speed_e*clock.getElapsedTime().asSeconds();
                if(list_of_move[0]=='d')
                    pos_e_y-=speed_e*clock.getElapsedTime().asSeconds();
                if(list_of_move[0]=='u')
                    pos_e_y+=speed_e*clock.getElapsedTime().asSeconds();
                //     std::cout<<"e x: "<<pos_e_x<<" y: "<<pos_e_y<<std::endl;
                //     std::cout<<"h x: "<<eyex<<" y: "<<eyey+5<<std::endl;
            }

        }

        move_camera(clock,character1->pos_y_,character1->pos_z_,
                    eyex,eyey,centerx,centery,character1,map);
        set_viewport(window.getSize().x, window.getSize().y,
                     eyex,eyey,eyez,centerx,centery,centerz);


        clock.restart();
        window.display();

    }
    delete(map);

    for(int i=0; i!=Texturs.size(); i++)
    {
        glDeleteTextures(1,&Texturs[i]);
    }
    return 0;
}


void Load_Texture(const std::string &nazwa,std::vector<GLuint> &Texturs,unsigned int i)
{
    Texturs.emplace_back(i);
    sf::Image Image;
    if (!Image.loadFromFile(nazwa))
        std::cout<<"ERROR"<<std::endl;

    glGenTextures(1, &Texturs[i]);
    glBindTexture(GL_TEXTURE_2D, Texturs[i]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Image.getSize().x, Image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, Image.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
}


