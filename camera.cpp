#include <iostream>
#include "world.h"
#include "Character.h"
#include <cmath>

void camera_setting(const float &mouse_sensitivity,
                    int &temp_mouse_pos_x,sf::Vector2i &mouse_pos,
                    sf::Clock &clock,sf::Vector3f &eye,sf::Vector3f &center,
                    const sf::Vector2f &temp_center,float &alpha_radius)
{
    float dl_b=sqrt(pow(temp_center.x-eye.x,2)+pow(temp_center.y-eye.y,2));
    float stopnie=0;
    bool minus=false,plus=false;
    if(temp_mouse_pos_x<mouse_pos.x)
    {
        minus=false;
        plus=true;
        bool error=true;
        if(center.y<=eye.y+1 and center.x>=eye.x)
        {
            if(center.y>eye.y)
            {
                center.x+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                center.y-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            else
            {
                center.x-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                center.y-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            error=false;
        }
        if(center.y<=eye.y+1 and center.x<eye.x)
        {
            if(center.y>eye.y)
            {
                center.x+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                center.y+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            else
            {
                center.x-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                center.y+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            error=false;
        }
        if(error)
        {
            center.y=eye.y+1;
            center.x=eye.x;
        }
    }
    if(temp_mouse_pos_x>mouse_pos.x)
    {
        minus=true;
        plus=false;

        bool error=true;
        if(center.y<=eye.y+1 and center.x<=eye.x)
        {
            if(center.y>eye.y)
            {
                center.x-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                center.y-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            else
            {
                center.x+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                center.y-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            error=false;
        }
        if(center.y<=eye.y+1 and center.x>eye.x)
        {
            if(center.y>eye.y)
            {
                center.x-=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                center.y+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            else
            {
                center.x+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
                center.y+=mouse_sensitivity*clock.getElapsedTime().asSeconds();
            }
            error=false;
        }
        if(error)
        {
            center.y=eye.y+1;
            center.x=eye.x;
        }  
    }
    float dl_a=sqrt(pow(temp_center.x-center.x,2)+pow(temp_center.y-center.y,2));
    float dl_c=sqrt(pow(center.x-eye.x,2)+pow(center.y-eye.y,2));
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

void move_camera(const sf::Clock &clk,sf::Vector3f &eye,sf::Vector3f &center,
                 Character*ch, world *w,sf::Vector2f &temp_center,float &alpha_radius)
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
            eye.y+=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();
            center.y+=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();

            eye.x+=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
            center.x+=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
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
            eye.y-=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();
            center.y-=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();

            eye.x-=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
            center.x-=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) and go_d and
      !sf::Keyboard::isKeyPressed(sf::Keyboard::D) and
      !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
         Hero::rotate_Character(-(alpha_radius*180/M_PI)-180);
        if(!collision(w,ch))
        {
            eye.y-=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();
            center.y-=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();

            eye.x-=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
            center.x-=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
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
            eye.y+=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();
            center.y+=speed*cos(alpha_radius)*clk.getElapsedTime().asSeconds();

            eye.x+=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
            center.x+=speed*sin(alpha_radius)*clk.getElapsedTime().asSeconds();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) and go_r)
    {
       Hero::rotate_Character(-(alpha_radius*180/M_PI)-90);
        if(!collision(w,ch))
        {
            eye.y-=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            center.y-=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();

            eye.x-=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            center.x-=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
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
            eye.y+=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            center.y+=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();

            eye.x+=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            center.x+=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
        }

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) and go_l)
    {
        Hero::rotate_Character(-(alpha_radius*180/M_PI)+90);
        if(!collision(w,ch))
        {
            eye.y+=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            center.y+=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();

            eye.x+=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            center.x+=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
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
            eye.y-=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            center.y-=speed*cos(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();

            eye.x-=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
            center.x-=speed*sin(alpha_radius-M_PI/2)*clk.getElapsedTime().asSeconds();
        }
    }
    temp_center.x=eye.x;
    temp_center.y=eye.y+1;
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

void set_viewport(const sf::Vector2i &window_size, sf::Vector3f &eye,sf::Vector3f &center)
{
    float ar = window_size.x / window_size.y;

    glViewport(0,0,window_size.x,window_size.y);

    glMatrixMode(GL_MODULATE);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 1.0, 100.0);
    gluLookAt(eye.x,eye.y,eye.z,center.x,center.y,center.z, 0, 0, 1);
}





