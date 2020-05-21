#include "Character.h"

Hero::Hero(const float &pos_x,const float &pos_y,const float &pos_z,
           const GLint &tex)//:pos_x_(pos_x),pos_y_(pos_y),pos_z_(pos_z)
{
    pos_x_=pos_x;
    pos_y_=pos_y;
    pos_z_=pos_z;
    glPushMatrix();
    draw_hero(tex);
    glPopMatrix();

}

void Hero::draw_hero(const GLint &tex)
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

Enemy::Enemy(const GLint &tex)
{
    glPushMatrix();
    draw_hero(tex);
    glPopMatrix();
}

void Enemy::draw_hero(const GLint &tex)
{
    glTranslated(pos_x_,pos_y_,pos_z_);
    glRotated(180,0,0,1);
   // glRotated(0,0,0,1);
    glRotated(180,1,0,0);
    gluQuadricDrawStyle(sphere, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, tex);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere,1,25,25);

}