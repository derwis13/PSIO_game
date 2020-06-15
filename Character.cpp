#include "Character.h"
#include <iostream>


Hero::Hero(const float &pos_x, const float &pos_y, const float &pos_z,
           const GLint &tex, float &rot)
{
    pos_x_=pos_x;
    pos_y_=pos_y;
    pos_z_=pos_z;
    sf::Rect rect(pos_x_-1,pos_y_-1,width+1,length+1);
    rect_=rect;
    glPushMatrix();
    draw_hero(tex,rot);
    glPopMatrix();

}

void Hero::draw_hero(const GLint &tex, float &rot)
{

    glTranslated(pos_x_,pos_y_,pos_z_);
    //glRotated(0,0,0,1);
    glRotated(rot,0,0,1);
    glRotated(180,1,0,0);
    gluQuadricDrawStyle(sphere, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, tex);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere,1,25,25);
}



Enemy::Enemy(const sf::Vector3f &pos_e, const GLint &tex, float &rot)
{
    pos_x_=pos_e.x;
    pos_y_=pos_e.y;
    pos_z_=pos_e.z;
    glPushMatrix();
    draw_hero(tex,rot);
    glPopMatrix();
}

void Enemy::draw_hero(const GLint &tex, float &rot)
{
    glTranslated(pos_x_,pos_y_,pos_z_);
   // glRotated(180,0,0,1);
    glRotated(rot,0,0,1);
    glRotated(180,1,0,0);
    gluQuadricDrawStyle(sphere, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, tex);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere,1,25,25);

}


