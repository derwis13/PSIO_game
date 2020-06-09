#include <iostream>
#include "world.h"
#include "Character.h"
#include <cmath>

void camera_setting(const float &mouse_sensitivity,int &temp_mouse_pos_x,
                    sf::Vector2i &mouse_pos,sf::Clock &clock,float &eyex,float &eyey,
                    float &centerx, float &centery,const float &temp_centerx,
                    const float &temp_centery,float &alpha_radius)
{
    float dl_b=sqrt(pow(temp_centerx-eyex,2)+pow(temp_centery-eyey,2));
    float stopnie=0;
    bool minus=false,plus=false;
    if(temp_mouse_pos_x<mouse_pos.x)
    {
        minus=false;
        plus=true;
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
        minus=true;
        plus=false;

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
    float dl_a=sqrt(pow(temp_centerx-centerx,2)+pow(temp_centery-centery,2));
    float dl_c=sqrt(pow(centerx-eyex,2)+pow(centery-eyey,2));
    float cos_a=(pow(dl_b,2)+pow(dl_c,2)-pow(dl_a,2))/(2*dl_b*dl_c);
    float a=acos(cos_a);


    float delta=abs(a-abs(alpha_radius));

    if(plus)
        alpha_radius+=delta;

    if(minus)
        alpha_radius-=delta;


    if(alpha_radius>M_PI)
        alpha_radius=-abs(M_PI-abs(M_PI-alpha_radius));

    if(alpha_radius<-M_PI)
       alpha_radius=abs(M_PI-(M_PI-alpha_radius));

}

void move_camera(const sf::Clock &clk,float &eyex,float &eyey,
                 float &eyez,float &centerx, float &centery,float  &centerz,
                 Character*ch, world *w,float &temp_centerx,float &temp_centery,
                 float &alpha_radius)
{
    float speed=3;

    static bool go_s=true,go_d=true,go_l=true,go_r=true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) or
            sf::Keyboard::isKeyPressed(sf::Keyboard::S) or
            sf::Keyboard::isKeyPressed(sf::Keyboard::D) or
            sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) and go_s and
       !sf::Keyboard::isKeyPressed(sf::Keyboard::D) and
       !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        Hero::rotate_Character(-(alpha_radius*180/M_PI));
        if(!collision(w,ch))
        {
            eyey+=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();
            centery+=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();

            eyex+=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
            centerx+=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
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
            eyey-=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();
            centery-=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();

            eyex-=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
            centerx-=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) and go_d and
      !sf::Keyboard::isKeyPressed(sf::Keyboard::D) and
      !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
         Hero::rotate_Character(-(alpha_radius*180/M_PI)-180);
        if(!collision(w,ch))
        {
            eyey-=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();
            centery-=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();

            eyex-=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
            centerx-=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
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
            eyey+=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();
            centery+=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();

            eyex+=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
            centerx+=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) and go_r)
    {
        Hero::rotate_Character(-(alpha_radius*180/M_PI)-90);
        if(!collision(w,ch))
        {
            eyey-=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            centery-=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();

            eyex-=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            centerx-=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
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
            eyey+=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            centery+=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();

            eyex+=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            centerx+=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
        }

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) and go_l)
    {
        Hero::rotate_Character(-(alpha_radius*180/M_PI)+90);
        if(!collision(w,ch))
        {
            eyey+=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            centery+=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();

            eyex+=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            centerx+=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
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
            eyey-=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            centery-=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();

            eyex-=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            centerx-=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
        }
    }
    temp_centerx=eyex;
    temp_centery=eyey+1;
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





