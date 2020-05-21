#include "create_world.h"
#include <iostream>


void draw_wall(const GLuint &tex);
void create_ground(const float &size_map_x,const float &size_map_y);
//void draw_b_cube(double size);


create_world::create_world(const std::vector<GLuint>&Texture)
{
    tex=Texture;
//    class create_wall wall(7,0,0,'s',tex[0],40);
//    class create_wall wall1(-7,0,0,'s',tex[0],40);
//    class create_wall wall2(-39,8,0,'r',tex[0],40); //-(len-1),y+1,z,dorection,text_id,len
//    class create_wall wall3(39,8,0,'l',tex[0],40);
    walls.emplace_back(0,0,0,'l',tex[0],6);
    walls.emplace_back(0,0,0,'r',tex[0],6);
    walls.emplace_back(7,0,0,'s',tex[0],40);
    walls.emplace_back(-7,0,0,'s',tex[0],40);
    walls.emplace_back(-39,8,0,'r',tex[0],40); //-(len-1),y+1,z,dorection,text_id,len
    walls.emplace_back(39,8,0,'l',tex[0],40);

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

void create_world::create_ground(const float &size_map_x,
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



create_wall::create_wall(const float &pos_x,const float &pos_y,
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

//void draw_b_cube(double size)
//{
//    float val=100;
//    // back
//    glBegin(GL_POLYGON);
//    glVertex3d(-val,0,0);
//    glVertex3d(val,0,0);
//    glVertex3d(val,val,0);
//    glVertex3d(-val,val,0);
//    glEnd();

//    // front

//    glBegin(GL_POLYGON);
//    glVertex3d(-val,0,val);
//    glVertex3d(val,0,val);
//    glVertex3d(val,val,val);
//    glVertex3d(-val,val,val);
//    glEnd();

//    //left
//    glBegin(GL_POLYGON);
//    glVertex3d(-val,val,val);
//    glVertex3d(-val,val,0);
//    glVertex3d(-val,0,0);
//    glVertex3d(-val,0,val);
//    glEnd();

//    //right
//    glBegin(GL_POLYGON);
//    glVertex3d(val,val,val);
//    glVertex3d(val,val,0);
//    glVertex3d(val,0,0);
//    glVertex3d(val,0,val);
//    glEnd();

//    //right
//    glBegin(GL_POLYGON);
//    glVertex3d(val,val,val);
//    glVertex3d(val,val,0);
//    glVertex3d(val,0,0);
//    glVertex3d(val,0,val);
//    glEnd();

//    //top
//    glBegin(GL_POLYGON);
//    glVertex3d(val,val,val);
//    glVertex3d(val,val,0);
//    glVertex3d(-val,val,0);
//    glVertex3d(-val,val,val);
//    glEnd();

//    //bottom
//    glBegin(GL_POLYGON);
//    glVertex3d(-val,0,val);
//    glVertex3d(val,0,val);
//    glVertex3d(val,0,0);
//    glVertex3d(-val,0,0);
//    glEnd();
//    glDisable(GL_TEXTURE_2D);

//}
