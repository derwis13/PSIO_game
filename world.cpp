#include "world.h"
#include <iostream>
#include <SFML/Graphics.hpp>


void draw_wall(const GLuint &tex);
void create_ground(const float &size_map_x,const float &size_map_y);


world::world(const std::vector<GLuint>&Texture)
{
    tex=Texture;

    float kratka=10;

    v_wall.emplace_back(-1,-4+kratka,0,'r',tex[0],14*kratka);
    v_wall.emplace_back(-4-kratka,0,0,'s',tex[0],14*kratka);
    v_wall.emplace_back(-1,-4,0,'r',tex[0],1*kratka-2);
    v_wall.emplace_back(5,0,0,'s',tex[0],2*kratka);
    v_wall.emplace_back(-5,0,0,'s',tex[0],3*kratka);
    v_wall.emplace_back(-(3*kratka)-1,-6,0,'r',tex[0],2*kratka);
    v_wall.emplace_back(-(2*kratka)+1,6+kratka,0,'r',tex[0],2*kratka);
    v_wall.emplace_back(-(1*kratka)-1,6+kratka,0,'r',tex[0],3*kratka);
    v_wall.emplace_back(5+kratka,kratka,0,'s',tex[0],kratka);
    v_wall.emplace_back(-1,-4-kratka,0,'r',tex[0],8);
    v_wall.emplace_back(3.5*kratka,2*kratka,0,'s',tex[0],1*kratka);
    v_wall.emplace_back(-(3*kratka)+1,6+3*kratka,0,'r',tex[0],2*kratka);
    v_wall.emplace_back(1+4.5*kratka,2*kratka,0,'s',tex[0],1*kratka-2);
    v_wall.emplace_back(-(1*kratka)-1,6+5*kratka,0,'r',tex[0],1*kratka);
    v_wall.emplace_back(-(2*kratka)-1,6+5*kratka,0,'r',tex[0],1*kratka-2);
    v_wall.emplace_back(7+5*kratka,1*kratka+2,0,'s',tex[0],1*kratka-2);
    v_wall.emplace_back(5+6*kratka,1*kratka+2,0,'s',tex[0],7*kratka-2);
    v_wall.emplace_back(5+7*kratka,2,0,'s',tex[0],3*kratka-2);
    v_wall.emplace_back(-(1*kratka)-1,6+8*kratka,0,'r',tex[0],5*kratka);
    v_wall.emplace_back(-(2*kratka)-1,6+8*kratka,0,'r',tex[0],5*kratka);
    v_wall.emplace_back(7+8*kratka,1*kratka+2,0,'s',tex[0],1*kratka-2);
    v_wall.emplace_back(7+13*kratka,2*kratka,0,'s',tex[0],5*kratka-2);
    v_wall.emplace_back(-(3*kratka)+1,6+7*kratka,0,'r',tex[0],5*kratka);
    v_wall.emplace_back(-(4*kratka)+1,6+7*kratka,0,'r',tex[0],6*kratka);
    v_wall.emplace_back(-(5*kratka)+1,6+7*kratka,0,'r',tex[0],4*kratka);
    v_wall.emplace_back(7+11*kratka-2,5*kratka,0,'s',tex[0],1*kratka-2); //kwadrat
    v_wall.emplace_back(7+12*kratka-2,5*kratka,0,'s',tex[0],1*kratka-2);  //kwadrat
    v_wall.emplace_back(-(6*kratka)+1,4+11*kratka,0,'r',tex[0],1*kratka+2); //kwadrat
    v_wall.emplace_back(-(5*kratka)+1,4+12*kratka,0,'r',tex[0],1*kratka+2);
    v_wall.emplace_back(-(7*kratka)+1,4+10*kratka,0,'r',tex[0],3*kratka+4);
    //lewa czesc
    v_wall.emplace_back(-(4*kratka)+1,-6,0,'r',tex[0],1*kratka);
    v_wall.emplace_back(-5+kratka,4*kratka-2,0,'s',tex[0],1*kratka);
    v_wall.emplace_back(-(5*kratka)+1,-6,0,'r',tex[0],1*kratka+2);
    v_wall.emplace_back(-(4*kratka)+1,-6+2*kratka,0,'r',tex[0],3*kratka);
    v_wall.emplace_back(-5+3*kratka,4*kratka,0,'s',tex[0],1*kratka-2);
    v_wall.emplace_back(-5+3*kratka,3*kratka,0,'s',tex[0],1*kratka-2);
    v_wall.emplace_back(-(5*kratka)+1,-6+3*kratka,0,'r',tex[0],1*kratka+2);
    v_wall.emplace_back(-5+5*kratka,4*kratka-2,0,'s',tex[0],3*kratka);
    v_wall.emplace_back(-5+4*kratka,5*kratka,0,'s',tex[0],2*kratka-2);
    v_wall.emplace_back(-(7*kratka)+1,-6+4*kratka,0,'r',tex[0],1*kratka+2);
    v_wall.emplace_back(-5+6*kratka,3*kratka,0,'s',tex[0],4*kratka);


    for(auto it=v_wall.begin(); it!=v_wall.end(); it++)
    {
       rect.emplace_back(it->get_parameters(it->direction_));
    }
    create_ground(size_map_x,size_map_y);

}


void draw_wall(const GLuint &tex)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    glColor3d(1,1,1);
    float val=1;
    // back
    glBegin(GL_POLYGON);
    glVertex3d(-val,0,0);
    glVertex3d(val,0,0);
    glVertex3d(val,val,0);
    glVertex3d(-val,val,0);
    glEnd();

    // front

    glBegin(GL_POLYGON);
    glVertex3d(-val,0,val);
    glVertex3d(val,0,val);
    glVertex3d(val,val,val);
    glVertex3d(-val,val,val);
    glEnd();

    //left
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0, 0.0);
    glVertex3d(-val,val,val);
    glTexCoord2f(1.0, 1.0);
    glVertex3d(-val,val,0);
    glTexCoord2f(0.0, 1.0);
    glVertex3d(-val,0,0);
    glTexCoord2f(0.0, 0.0);
    glVertex3d(-val,0,val);
    glEnd();

    //right
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(val,val,val);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(val,val,0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(val,0,0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(val,0,val);
    glEnd();

    //right
    glBegin(GL_POLYGON);
    glVertex3d(val,val,val);
    glVertex3d(val,val,0);
    glVertex3d(val,0,0);
    glVertex3d(val,0,val);
    glEnd();

    //top
    glBegin(GL_POLYGON);
    glVertex3d(val,val,val);
    glVertex3d(val,val,0);
    glVertex3d(-val,val,0);
    glVertex3d(-val,val,val);
    glEnd();

    //bottom
    glBegin(GL_POLYGON);
    glVertex3d(-val,0,val);
    glVertex3d(val,0,val);
    glVertex3d(val,0,0);
    glVertex3d(-val,0,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void world::create_ground(const float &size_map_x,
                                 const float &size_map_y)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    glColor3d(130.0, 130.0, 130.0);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-size_map_x,0,0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-size_map_x,size_map_y,0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(size_map_x,size_map_y,0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3d(size_map_x,0,0);
    glEnd();
}



walls::walls(const float &pos_x,const float &pos_y,
                         const float &pos_z,const char &direction,
                         const GLint &tex,const float &length)
                         :pos_x_(pos_x),pos_y_(pos_y),pos_z_(pos_z),
                         direction_(direction),length_(length)
{
   glPushMatrix();
   if(direction_=='r')
   glRotated(-90,0,0,1);
   if(direction_=='l')
   glRotated(90,0,0,1);
   glTranslated(pos_x_,pos_y_,pos_z_);
   glScaled(width_,length_,height_);
   draw_wall(tex);
   glPopMatrix();
}

sf::FloatRect walls::get_parameters(const char &direction)
{
    if(direction=='s')
    {
    sf::Rect rect(pos_x_,pos_y_,width_,length_);
    return rect;
    }
    if(direction=='r')
    {
    sf::Rect rect(pos_y_,abs(pos_x_),length_,width_);
    return rect;
    }

}


