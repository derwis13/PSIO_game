#ifndef HERO_H
#define HERO_H

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glu.h>
#include <iostream>

class world;

class Character
{

public:
    GLUquadric* sphere=gluNewQuadric();
    sf::FloatRect rect_;
    float pos_x_,pos_y_,pos_z_;
    float width=2,length=width;

protected:
    virtual void draw_hero(const GLint &tex,float &rot)=0;


};

class Hero:public Character
{

public:
    static float rot;
    Hero(const float &pos_x,const float &pos_y,const float &pos_z,
         const GLint &tex,float &rot);
    void draw_hero(const GLint &tex,float &rot);

    static void rotate_Character(float rotate){rot=rotate;}
    friend bool collision(const world*, const Character*);
};

class Enemy:public Character
{

public:
    static float rot;
    Enemy(const sf::Vector3f &pos_e, const GLint &tex,float &rot);
    void draw_hero(const GLint &tex,float &rot);
    static void rotate_Character(float rotate){rot=rotate;}
};

#endif // HERO_H
