#ifndef HERO_H
#define HERO_H

#include <SFML/OpenGL.hpp>
#include <GL/glu.h>

class Hero
{
    float pos_x_,pos_y_,pos_z_;
    void draw_hero(const GLint &tex);
public:
    Hero(const float &pos_x,const float &pos_y,const float &pos_z,
         const GLint &tex);

};

#endif // HERO_H
