#include "world.h"
#include <iostream>
#include <SFML/Graphics.hpp>


void draw_wall(const GLuint &tex);
void create_ground(const float &size_map_x,const float &size_map_y);


world::world(const std::vector<GLuint>&Texture)
{
    tex=Texture;

    set_walls();


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
                           float &size_map_y)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    glColor3d(130.0, 130.0, 130.0);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-15,0,0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-15,size_map_y,0);
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
void world::set_walls()
{
    float entity=10;

    v_wall.emplace_back(-1,-4+entity,0,'r',tex[0],14*entity);
    v_wall.emplace_back(-4-entity,0,0,'s',tex[0],19*entity);
    v_wall.emplace_back(-1,-4,0,'r',tex[0],1*entity-2);
    v_wall.emplace_back(5,0,0,'s',tex[0],2*entity);
    v_wall.emplace_back(-5,0,0,'s',tex[0],3*entity);
    v_wall.emplace_back(-(3*entity)-1,-6,0,'r',tex[0],2*entity);
    v_wall.emplace_back(-(2*entity)+1,6+entity,0,'r',tex[0],2*entity);
    v_wall.emplace_back(-(1*entity)-1,6+entity,0,'r',tex[0],3*entity);
    v_wall.emplace_back(5+entity,entity,0,'s',tex[0],entity);
    v_wall.emplace_back(-1,-4-entity,0,'r',tex[0],8);
    v_wall.emplace_back(3.5*entity,2*entity,0,'s',tex[0],1*entity);
    v_wall.emplace_back(-(3*entity)+1,6+3*entity,0,'r',tex[0],2*entity);
    v_wall.emplace_back(1+4.5*entity,2*entity,0,'s',tex[0],1*entity-2);
    v_wall.emplace_back(-(1*entity)-1,6+5*entity,0,'r',tex[0],1*entity);
    v_wall.emplace_back(-(2*entity)-1,6+5*entity,0,'r',tex[0],1*entity-2);
    v_wall.emplace_back(7+5*entity,1*entity+2,0,'s',tex[0],1*entity-2);
    v_wall.emplace_back(5+6*entity,1*entity+2,0,'s',tex[0],7*entity-2);
    v_wall.emplace_back(5+7*entity,2,0,'s',tex[0],3*entity-2);
    v_wall.emplace_back(-(1*entity)-1,6+8*entity,0,'r',tex[0],5*entity);
    v_wall.emplace_back(-(2*entity)-1,6+8*entity,0,'r',tex[0],5*entity);
    v_wall.emplace_back(7+8*entity,1*entity+2,0,'s',tex[0],1*entity-2);
    v_wall.emplace_back(7+13*entity,2*entity,0,'s',tex[0],5*entity-2);
    v_wall.emplace_back(-(3*entity)+1,6+7*entity,0,'r',tex[0],5*entity);
    v_wall.emplace_back(-(4*entity)+1,6+7*entity,0,'r',tex[0],6*entity);
    v_wall.emplace_back(-(5*entity)+1,6+7*entity,0,'r',tex[0],4*entity);
    v_wall.emplace_back(7+11*entity-2,5*entity,0,'s',tex[0],1*entity-2);
    v_wall.emplace_back(7+12*entity-2,5*entity,0,'s',tex[0],1*entity-2);
    v_wall.emplace_back(-(6*entity)+1,4+11*entity,0,'r',tex[0],1*entity+2);
    v_wall.emplace_back(-(5*entity)+1,4+12*entity,0,'r',tex[0],1*entity+2);
    v_wall.emplace_back(-(7*entity)+1,4+10*entity,0,'r',tex[0],3*entity+4);
    v_wall.emplace_back(-(4*entity)+1,-6,0,'r',tex[0],1*entity);
    v_wall.emplace_back(-5+entity,4*entity-2,0,'s',tex[0],1*entity);
    v_wall.emplace_back(-(5*entity)+1,-6,0,'r',tex[0],1*entity+2);
    v_wall.emplace_back(-(4*entity)+1,-6+2*entity,0,'r',tex[0],3*entity);
    v_wall.emplace_back(-5+3*entity,4*entity,0,'s',tex[0],1*entity-2);
    v_wall.emplace_back(-5+3*entity,3*entity,0,'s',tex[0],1*entity-2);
    v_wall.emplace_back(-(5*entity)+1,-6+3*entity,0,'r',tex[0],1*entity+2);
    v_wall.emplace_back(-5+5*entity,4*entity-2,0,'s',tex[0],3*entity);
    v_wall.emplace_back(-5+4*entity,5*entity,0,'s',tex[0],2*entity-2);
    v_wall.emplace_back(-(7*entity)+1,-6+4*entity,0,'r',tex[0],1*entity+2);
    v_wall.emplace_back(-5+6*entity,3*entity,0,'s',tex[0],4*entity);
    v_wall.emplace_back(-5+2*entity,5*entity-2,0,'s',tex[0],4*entity);
    v_wall.emplace_back(-(6*entity)+1,-6+1*entity,0,'r',tex[0],2*entity);
    v_wall.emplace_back(-5+1*entity,6*entity,0,'s',tex[0],4*entity-2);
    v_wall.emplace_back(-5+3*entity,6*entity-2,0,'s',tex[0],2*entity);
    v_wall.emplace_back(-5+0*entity,5*entity,0,'s',tex[0],6*entity-2);
    v_wall.emplace_back(-(8*entity)+1,-6+3*entity,0,'r',tex[0],4*entity);
    v_wall.emplace_back(-(9*entity)+1,-6+2*entity,0,'r',tex[0],5*entity);
    v_wall.emplace_back(-(10*entity)+1,-6+1*entity,0,'r',tex[0],5*entity);
    v_wall.emplace_back(-(11*entity)+1,-6+0*entity,0,'r',tex[0],4*entity);
    v_wall.emplace_back(-5+7*entity,9*entity-2,0,'s',tex[0],1*entity);
    v_wall.emplace_back(-(10*entity)+1,-6+7*entity,0,'r',tex[0],2*entity);
    v_wall.emplace_back(-5+8*entity,7*entity-2,0,'s',tex[0],4*entity);
    v_wall.emplace_back(-(6*entity)+1,-4+7*entity,0,'r',tex[0],4*entity-2);
    v_wall.emplace_back(-5+11*entity,6*entity-2,0,'s',tex[0],1*entity);
    v_wall.emplace_back(-5+9*entity,7*entity-2,0,'s',tex[0],2*entity);
    v_wall.emplace_back(-5+10*entity,7*entity-2,0,'s',tex[0],1*entity);
    v_wall.emplace_back(-(9*entity)+1,-6+9*entity,0,'r',tex[0],1*entity);
    v_wall.emplace_back(-(8*entity)+1,-6+10*entity,0,'r',tex[0],4*entity+2);
    v_wall.emplace_back(-3+14*entity,8*entity-2,0,'s',tex[0],2*entity);
    v_wall.emplace_back(-(9*entity)+1,-6+11*entity,0,'r',tex[0],1*entity+2);
    v_wall.emplace_back(-(9*entity)+1,-6+13*entity,0,'r',tex[0],1*entity+2);
    v_wall.emplace_back(-5+13*entity,9*entity,0,'s',tex[0],2*entity);
    v_wall.emplace_back(-5+12*entity,9*entity,0,'s',tex[0],3*entity);
    v_wall.emplace_back(-5+11*entity,9*entity,0,'s',tex[0],4*entity);
    v_wall.emplace_back(-5+10*entity,9*entity-2,0,'s',tex[0],2*entity+2);
    v_wall.emplace_back(-(11*entity)+1,-4+13*entity,0,'r',tex[0],2*entity);
    v_wall.emplace_back(-(12*entity)+1,-4+12*entity,0,'r',tex[0],1*entity);
    v_wall.emplace_back(-(13*entity)+1,-4+11*entity,0,'r',tex[0],2*entity);
    v_wall.emplace_back(-(14*entity)+1,-4+8*entity,0,'r',tex[0],3*entity);
    v_wall.emplace_back(-(12*entity)+1,-4+8*entity,0,'r',tex[0],2*entity);
    v_wall.emplace_back(-(13*entity)+1,-4+4*entity,0,'r',tex[0],3*entity-2);
    v_wall.emplace_back(-(11*entity)+1,-4+9*entity,0,'r',tex[0],1*entity-2);
    v_wall.emplace_back(-(11*entity)+1,-4+5*entity,0,'r',tex[0],1*entity-2);
    v_wall.emplace_back(-5+9*entity,11*entity-2,0,'s',tex[0],2*entity+2);
    v_wall.emplace_back(-5+8*entity,12*entity-2,0,'s',tex[0],2*entity+2);
    v_wall.emplace_back(-5+7*entity,11*entity-2,0,'s',tex[0],2*entity+2);
    v_wall.emplace_back(-5+6*entity,10*entity-2,0,'s',tex[0],3*entity);
    v_wall.emplace_back(-5+5*entity,11*entity-2,0,'s',tex[0],1*entity);
    v_wall.emplace_back(-5+4*entity,11*entity-2,0,'s',tex[0],2*entity+2);
    v_wall.emplace_back(-5+3*entity,12*entity-2,0,'s',tex[0],3*entity+2);
    v_wall.emplace_back(-5+2*entity,13*entity-2,0,'s',tex[0],2*entity+2);
    v_wall.emplace_back(-5+1*entity,12*entity-2,0,'s',tex[0],2*entity+2);
    v_wall.emplace_back(-5+0*entity,11*entity,0,'s',tex[0],2*entity);
    v_wall.emplace_back(-3+14*entity,12*entity,0,'s',tex[0],3*entity);
    v_wall.emplace_back(-5+12*entity,14*entity,0,'s',tex[0],1*entity);
    v_wall.emplace_back(-5+11*entity,13*entity,0,'s',tex[0],1*entity-2);
    v_wall.emplace_back(-5+10*entity,13*entity,0,'s',tex[0],2*entity);
    v_wall.emplace_back(-5+7*entity,14*entity,0,'s',tex[0],1*entity);
    v_wall.emplace_back(-5+6*entity,14*entity,0,'s',tex[0],2*entity);
    v_wall.emplace_back(-5+0*entity,14*entity,0,'s',tex[0],1*entity);
    v_wall.emplace_back(-5+1*entity,15*entity,0,'s',tex[0],1*entity);
    v_wall.emplace_back(-(16*entity)-1,-4+4*entity,0,'r',tex[0],4*entity-2);
    v_wall.emplace_back(-(17*entity)-1,-4+3*entity,0,'r',tex[0],5*entity-2);
    v_wall.emplace_back(-(16*entity)-1,-6+1*entity,0,'r',tex[0],2*entity);
    v_wall.emplace_back(-(15*entity)-1,-6+0*entity,0,'r',tex[0],1*entity);
    v_wall.emplace_back(-(14*entity)+1,-3-1*entity,0,'r',tex[0],1*entity-1);//
    v_wall.emplace_back(-(14*entity)+1,-4+0*entity,0,'r',tex[0],1*entity-2);//
    v_wall.emplace_back(-(13*entity)+1,-4+0*entity,0,'r',tex[0],1*entity-2);
    v_wall.emplace_back(-(13*entity)+1,-4+1*entity,0,'r',tex[0],1*entity-2);
    v_wall.emplace_back(-(12*entity)+1,-4+2*entity,0,'r',tex[0],1*entity-2);
    v_wall.emplace_back(-(14*entity)+1,-4+3*entity,0,'r',tex[0],4*entity);
    v_wall.emplace_back(-(15*entity)+1,-4+4*entity,0,'r',tex[0],2*entity-2);
    v_wall.emplace_back(-(15*entity)+1,-4+7*entity,0,'r',tex[0],3*entity-2);
    v_wall.emplace_back(-(15*entity)+1,-6+11*entity,0,'r',tex[0],1*entity);
    v_wall.emplace_back(-(15*entity)+1,-4+12*entity,0,'r',tex[0],2*entity);
    v_wall.emplace_back(-(14*entity)+1,-6+12*entity,0,'r',tex[0],1*entity+2);
    v_wall.emplace_back(-(16*entity)-1,-6+10*entity,0,'r',tex[0],5*entity+2);
    v_wall.emplace_back(-(17*entity)-1,-6+12*entity,0,'r',tex[0],3*entity+2);
    v_wall.emplace_back(-(17*entity)-1,-6+9*entity,0,'r',tex[0],1*entity+2);
    v_wall.emplace_back(-(17*entity)-1,-6+0*entity,0,'r',tex[0],1*entity+2);
    v_wall.emplace_back(-(18*entity)-1,-6+0*entity,0,'r',tex[0],15*entity+2);
    v_wall.emplace_back(-(19*entity)-1,-5-1*entity,0,'r',tex[0],15*entity+2);
    v_wall.emplace_back(15*entity-3,0,0,'s',tex[0],19*entity+2);
    v_wall.emplace_back(-5+1*entity,17*entity+2,0,'s',tex[0],1*entity-2);
    v_wall.emplace_back(-5+2*entity,17*entity,0,'s',tex[0],1*entity);
    v_wall.emplace_back(-5+3*entity,16*entity,0,'s',tex[0],1*entity+2);
    v_wall.emplace_back(-5+8*entity,16*entity,0,'s',tex[0],1*entity+2);
    v_wall.emplace_back(-5+9*entity,15*entity,0,'s',tex[0],2*entity);
    v_wall.emplace_back(-5+11*entity,15*entity,0,'s',tex[0],2*entity);
}


