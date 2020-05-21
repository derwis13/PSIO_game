#ifndef CREATE_WORLD_H
#define CREATE_WORLD_H

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glu.h>
#include <vector>
#include <string>


class create_world
{
    const float size_map_x=100,size_map_y=100;
    void create_wall();
    void create_ground(const float &size_map_x,const float &size_map_y);
public:
    std::vector<GLuint>tex;
    create_world(const std::vector<GLuint>&Texture);
    std::vector<class create_wall> walls;
};

class create_wall
{
    char direction_;
    float delta_wall_;
    const float width_=1,height_=5;
    float length_;
    float pos_x_,pos_y_,pos_z_;
public:
    create_wall(const float &pos_x,const float &pos_y,const float &pos_z,
                const char &direction,const GLint &tex,const float &length);
};

void move_camera(const sf::Clock &clk,float &pos_y,float &pos_z,float &eyex,
                 float &eyey,float &eyez,float &centerx, float &centery,
                 float &centerz);
void set_viewport(const int &width, const int &height,float &eyex,
                  float &eyey, float &eyez,float &centerx, float &centery,
                  float &centerz);

void camera_setting(const float &mouse_sensitivity,
                    unsigned int &temp_mouse_pos_x,sf::Vector2i &mouse_pos,
                    sf::Clock &clock,float &eyex,float &eyey,float &eyez,
                    float &centerx, float &centery, float &centerz);


#endif // CREATE_WORLD_H
