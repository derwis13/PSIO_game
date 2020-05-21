#include "create_world.h"

void camera_setting(const float &mouse_sensitivity,unsigned int &temp_mouse_pos_x,
                    sf::Vector2i &mouse_pos,sf::Clock &clock,float &eyex,float &eyey,
                    float &eyez,float &centerx, float &centery, float &centerz)
{
    if(temp_mouse_pos_x<mouse_pos.x)
    {
        bool error=true;
        if(centery<=eyey+1 and centerx>=eyex)
        {
            if(centery>eyey)
            {
                centerx+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                centery-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            else
            {
                centerx-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                centery-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            error=false;
        }
        if(centery<=eyey+1 and centerx<eyex)
        {
            if(centery>eyey)
            {
                centerx+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                centery+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            else
            {
                centerx-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                centery+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            error=false;
        }
        if(error)
        {
            centery=eyey+1;
            centerx=eyex;
        }
    }
    if(temp_mouse_pos_x>mouse_pos.x)
    {
        bool error=true;
        if(centery<=eyey+1 and centerx<=eyex)
        {
            if(centery>eyey)
            {
                centerx-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                centery-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            else
            {
                centerx+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                centery-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            error=false;
        }
        if(centery<=eyey+1 and centerx>eyex)
        {
            if(centery>eyey)
            {
                centerx-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                centery+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            else
            {
                centerx+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                centery+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            error=false;
        }
        if(error)
        {
            centery=eyey+1;
            centerx=eyex;
        }
    }
}

void move_camera(const sf::Clock &clk,float &pos_y,float &pos_z,float &eyex,
                 float &eyey,float &eyez,float &centerx, float &centery, float &centerz)
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        float gravity=9.81;
        float velocity_y=1,velocity_z=1;
        pos_y+=velocity_y*clk.getElapsedTime().asSeconds();
        pos_z+=velocity_z*clk.getElapsedTime().asSeconds();
        velocity_z+=gravity*clk.getElapsedTime().asSeconds();

    }
}

void set_viewport(const int &width,const int &height,float &eyex,float &eyey,
                  float &eyez,float &centerx, float &centery, float &centerz)
{
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_MODULATE);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 1.0, 100.0);
    gluLookAt(eyex,eyey, eyez, centerx,centery,centerz, 0, 0, 1);
}