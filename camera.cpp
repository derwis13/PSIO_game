#include <iostream>
#include "world.h"
#include "Character.h"

void camera_setting(const float &mouse_sensitivity,int &temp_mouse_pos_x,
                    sf::Vector2i &mouse_pos,sf::Clock &clock,float &eyex,float &eyey,
                    float &centerx, float &centery)
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

void move_camera(const sf::Clock &clk,float &eyex,float &eyey,
                 float &eyez,float &centerx, float &centery,float  &centerz,
                 Character*ch, world *w)
{
    float speed=3;
    static bool go_s=true,go_d=true,go_l=true,go_r=true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) and go_s and
       !sf::Keyboard::isKeyPressed(sf::Keyboard::D) and
       !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        Hero::rotate_Character(0);
        if(!colission(w,ch))
        {
            eyey+=speed*clk.getElapsedTime().asSeconds();
            centery+=speed*clk.getElapsedTime().asSeconds();
            go_l=true;
            go_r=true;
            go_s=true;
            go_d=true;
        }
        else {
            go_s=false;
            go_d=true;
            go_l=true,
            go_r=true;
            eyey-=speed*clk.getElapsedTime().asSeconds();
            centery-=speed*clk.getElapsedTime().asSeconds();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) and go_d and
      !sf::Keyboard::isKeyPressed(sf::Keyboard::D) and
      !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
         Hero::rotate_Character(180);
        if(!colission(w,ch))
        {
            eyey-=speed*clk.getElapsedTime().asSeconds();
            centery-=speed*clk.getElapsedTime().asSeconds();
            go_l=true;
            go_r=true;
            go_s=true;
            go_d=true;
        }
        else {
            go_s=true;
            go_d=false;
            go_l=true,
            go_r=true;
            eyey+=speed*clk.getElapsedTime().asSeconds();
            centery+=speed*clk.getElapsedTime().asSeconds();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) and go_r)
    {
        Hero::rotate_Character(-90);
        if(!colission(w,ch))
        {
            eyex+=speed*clk.getElapsedTime().asSeconds();
            centerx+=speed*clk.getElapsedTime().asSeconds();
            go_l=true;
            go_r=true;
            go_s=true;
            go_d=true;
        }
        else
        {
            go_s=true;
            go_d=true;
            go_l=true,
            go_r=false;
            eyex-=speed*clk.getElapsedTime().asSeconds();
            centerx-=speed*clk.getElapsedTime().asSeconds();
        }

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) and go_l)
    {
        Hero::rotate_Character(90);
        if(!colission(w,ch))
        {
            eyex-=speed*clk.getElapsedTime().asSeconds();
            centerx-=speed*clk.getElapsedTime().asSeconds();
            go_l=true;
            go_r=true;
            go_s=true;
            go_d=true;
        }
        else
        {
            go_s=true;
            go_d=true;
            go_l=false;
            go_r=true;
            eyex+=speed*clk.getElapsedTime().asSeconds();
            centerx+=speed*clk.getElapsedTime().asSeconds();
        }
    }


//            float gravity=9.81;
//            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//            {
//                eyez+=30*clk.getElapsedTime().asSeconds();
//                centerz+=30*clk.getElapsedTime().asSeconds();
//                eyey+=5*clk.getElapsedTime().asSeconds();
//                centery+=5*clk.getElapsedTime().asSeconds();
//            }
//            if(eyez>3)
//            {
//                eyez-=gravity*clk.getElapsedTime().asSeconds();
//                centerz-=gravity*clk.getElapsedTime().asSeconds();

//            }



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


//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) and
//       sf::Keyboard::isKeyPressed(sf::Keyboard::D) and go_s and go_r)
//    {
//        if(!colission(w,ch))
//        {
//            go_l=true;
//            go_r=true;
//            go_s=true;
//            go_d=true;
//        }
//        else {
//            go_s=false;
//            go_d=true;
//            go_l=true,
//            go_r=false;
//            eyey-=speed*clk.getElapsedTime().asSeconds();
//            centery-=speed*clk.getElapsedTime().asSeconds();
//            eyex-=speed*clk.getElapsedTime().asSeconds();
//            centerx-=speed*clk.getElapsedTime().asSeconds();
//    }}
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) and
//       sf::Keyboard::isKeyPressed(sf::Keyboard::D) and go_r and go_d)
//    {
//        if(!colission(w,ch))
//        {
//            go_l=true;
//            go_r=true;
//            go_s=true;
//            go_d=true;
//        }
//        else {
//            go_s=true;
//            go_d=false;
//            go_l=true,
//            go_r=false;
//            eyey+=speed*clk.getElapsedTime().asSeconds();
//            centery+=speed*clk.getElapsedTime().asSeconds();
//            eyex-=speed*clk.getElapsedTime().asSeconds();
//            centerx-=speed*clk.getElapsedTime().asSeconds();
//    }}

//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) and
//       sf::Keyboard::isKeyPressed(sf::Keyboard::A) and go_d and go_l)
//    {
//        if(!colission(w,ch))
//        {
//            go_l=true;
//            go_r=true;
//            go_s=true;
//            go_d=true;
//        }
//        else {
//            go_s=true;
//            go_d=false;
//            go_l=false,
//            go_r=true;
//            eyey+=speed*clk.getElapsedTime().asSeconds();
//            centery+=speed*clk.getElapsedTime().asSeconds();
//            eyex+=speed*clk.getElapsedTime().asSeconds();
//            centerx+=speed*clk.getElapsedTime().asSeconds();
//    }}

//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) and
//       sf::Keyboard::isKeyPressed(sf::Keyboard::A) and go_s and go_r)
//    {
//        if(!colission(w,ch))
//        {
//            go_l=true;
//            go_r=true;
//            go_s=true;
//            go_d=true;
//        }
//        else {
//            go_s=false;
//            go_d=true;
//            go_l=false,
//            go_r=true;
//            eyey-=speed*clk.getElapsedTime().asSeconds();
//            centery-=speed*clk.getElapsedTime().asSeconds();
//            eyex+=speed*clk.getElapsedTime().asSeconds();
//            centerx+=speed*clk.getElapsedTime().asSeconds();
//    }}


