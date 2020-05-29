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
    virtual void draw_hero(const GLint &tex)=0;


};

class Hero:public Character
{

public:
    static float rot;
    Hero(const float &pos_x,const float &pos_y,const float &pos_z,
         const GLint &tex);
    void draw_hero(const GLint &tex);

    static void rotate_Character(float rotate){rot=rotate;}
    friend bool colission(const world*, const Character*);
};

class Enemy:public Character
{

public:
    Enemy(const float &pos_x,const float &pos_y,const float &pos_z,
          const GLint &tex);
    void draw_hero(const GLint &tex);
    friend bool colission(const world*, const Character*);
};

#endif // HERO_H
