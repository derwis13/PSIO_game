#ifndef HERO_H
#define HERO_H

#include <SFML/OpenGL.hpp>
#include <GL/glu.h>

class Character
{
public:
    GLUquadric* sphere=gluNewQuadric();
    float pos_x_,pos_y_,pos_z_;
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
};

class Enemy:public Character
{
private:
    float pos_x_=0,pos_y_=5,pos_z_=1;
public:
    Enemy(const GLint &tex);
    void draw_hero(const GLint &tex);
};

#endif // HERO_H
