#define GL_SILENCE_DEPRECATION


//#include <SFML/Window.hpp>
#include <iostream>
#include <math.h>

#include "create_world.h"
#include "Character.h"

void Load_Texture(const std::string &nazwa,std::vector<GLuint> &Texturs,unsigned int i);
float Hero::rot;

int main() {
    float eyex=0;
    float eyey=5;
    float eyez=3;

    float centerx=eyex;
    float centery=eyey+1;
    float centerz=eyez;
    sf::Window window(sf::VideoMode(1024, 768), "Try to get out", sf::Style::Default, sf::ContextSettings(32));
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

    create_world *world;
    Character *character1,*character2;

    sf::Clock clock;
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
            unsigned int temp_mouse_pos_x=mouse_pos.x;
            mouse_pos = sf::Mouse::getPosition(window);
            float mouse_sensitivity=2;
            camera_setting(mouse_sensitivity,temp_mouse_pos_x,mouse_pos,clock,
                           eyex,eyey,eyez,centerx,centery,centerz);

            set_viewport(window.getSize().x, window.getSize().y,
                         eyex,eyey,eyez,centerx,centery,centerz);
            // std::cout<<"Look at: x->"<<centerx<<" y->"<<centery<<" z->"<<centerz<<std::endl;
            // std::cout<<"Stand at: x->"<<eyex<<" y->"<<eyey<<" z->"<<eyez<<std::endl;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
        glEnable (GL_COLOR_MATERIAL);

        world=new create_world(Texturs);
        character1 =new Hero(centerx+1,centery+3,1,Texturs[2]);
        character2 =new Enemy(Texturs[3]);



        move_camera(clock,character1->pos_y_,character1->pos_z_,
                    eyex,eyey,eyez,centerx,centery,centerz);
        set_viewport(window.getSize().x, window.getSize().y,
                     eyex,eyey,eyez,centerx,centery,centerz);

        clock.restart();
        window.display();

    }
    delete(world);
    delete(character1);
    delete(character2);

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


