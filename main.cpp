#define GL_SILENCE_DEPRECATION


//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "create_world.h"

void move_camera(const sf::Clock &clk);
void set_viewport(const int &width, const int &height);
void Load_Texture(const std::string &nazwa,std::vector<GLuint> &Texturs,unsigned int i);

float eyex=0;
float eyey=1;
float eyez=3;

float centerx=0;
float centery=2;
float centerz=3;
bool change_l=false;
bool change_r=false;

int main() {
    sf::Window window(sf::VideoMode(1024, 768), "Try to get out", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    window.setActive(true);
    std::vector<GLuint>Texturs;

    Load_Texture("wall.png",Texturs,Texturs.size());
    Load_Texture("grass.png",Texturs,Texturs.size());

    glClearColor(0, 0, 0, 1);

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

    sf::Clock clock;
    set_viewport(window.getSize().x, window.getSize().y);
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
            static sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            int temp_mouse_pos_x=mouse_pos.x;
            mouse_pos = sf::Mouse::getPosition(window);
            float speed=1;
            if(temp_mouse_pos_x<mouse_pos.x)
            {
              //  std::cout<<"Obroc w prawo"<<std::endl;
                centerx+=speed*clock.getElapsedTime().asSeconds();
                change_r=true;
                change_l=false;

            }
            if(temp_mouse_pos_x>mouse_pos.x)
            {
              //  std::cout<<"Obroc w lewo"<<std::endl;

              centerx-=speed*clock.getElapsedTime().asSeconds();
              change_l=true;
              change_r=false;

             }

            set_viewport(window.getSize().x, window.getSize().y);
            std::cout<<"Look at: x->"<<centerx<<" y->"<<centery<<" z->"<<centerz<<std::endl;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
        glEnable (GL_COLOR_MATERIAL);

        move_camera(clock);
        set_viewport(window.getSize().x, window.getSize().y);
//        if(change_r)
//        glRotated(13*clock.getElapsedTime().asSeconds(),0,0,1);
//        if(change_l)
//        glRotated(-13*clock.getElapsedTime().asSeconds(),0,0,1);
        create_world *world;
        world=new create_world(Texturs);

        clock.restart();
        window.display();
        delete(world);
    }

    return 0;
}


void move_camera(const sf::Clock &clk)
{
    float speed=5;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        eyey+=speed*clk.getElapsedTime().asSeconds();
        centery+=speed*clk.getElapsedTime().asSeconds();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        eyey-=speed*clk.getElapsedTime().asSeconds();
        centery-=speed*clk.getElapsedTime().asSeconds();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        eyex+=speed*clk.getElapsedTime().asSeconds();
        centerx+=speed*clk.getElapsedTime().asSeconds();

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        eyex-=speed*clk.getElapsedTime().asSeconds();
        centerx-=speed*clk.getElapsedTime().asSeconds();
    }
}

void set_viewport(const int &width,const int &height)
{
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_MODULATE);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 1.0, 100.0);
    gluLookAt(eyex,eyey, eyez, centerx,centery,centerz, 0, 0, 1);
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
}
