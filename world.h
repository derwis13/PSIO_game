#ifndef CREATE_WORLD_H
#define CREATE_WORLD_H

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glu.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Character;

class world
{
    void set_walls();
    void create_ground(const float &size_map_x, float &size_map_y);
public:
    float size_map_x=150,size_map_y=190;
    std::vector<sf::FloatRect> rect;
    std::vector<GLuint>tex;
    world(const std::vector<GLuint>&Texture);
    std::vector<class walls> v_wall;

    friend bool collision(const world*, const Character*);
    friend bool collision_path(const world*,const int &pos_e_x,const int &pos_e_y);

};

class walls
{

    float delta_wall_;
    const float width_=1,height_=5;
    float pos_x_,pos_y_,pos_z_;
    float length_;
public:
    char direction_;
    walls(const float &pos_x,const float &pos_y,const float &pos_z,
                const char &direction,const GLint &tex,const float &length);
    sf::FloatRect get_parameters(const char &direction);
};

void move_camera(const sf::Clock &clk,float &eyex,float &eyey,
                 float &eyez,float &centerx, float &centery,float &centerz ,
                 Character*ch, world *w,float &temp_centerx,
                 float &temp_centery,float &alpha_radius);
void set_viewport(const int &width, const int &height,float &eyex,
                  float &eyey, float &eyez,float &centerx, float &centery,
                  float &centerz);

void camera_setting(const float &mouse_sensitivity,
                    int &temp_mouse_pos_x,sf::Vector2i &mouse_pos,
                    sf::Clock &clock,float &eyex,float &eyey,
                    float &centerx, float &centery,const float &temp_centerx,
                    const float &temp_centery,float &alpha_radius);
bool collision(const world*w, const Character*h);

void find_path(const int &pos_h_x,const int &pos_h_y,int &pos_e_x,
               int &pos_e_y, std::vector<char> &list_of_move,
               const world*w,bool &colission_Enemy_Hero);


#endif // CREATE_WORLD_H
