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
    void  create_ground_finish(const sf::FloatRect &);
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

void move_camera(const sf::Clock &clk,sf::Vector3f &eye,sf::Vector3f &center,
                 Character*ch, world *w,sf::Vector2f &temp_center,float &alpha_radius);

void set_viewport(const sf::Vector2i &window_size, sf::Vector3f &eye,sf::Vector3f &center);

void camera_setting(const float &mouse_sensitivity,
                    int &temp_mouse_pos_x,sf::Vector2i &mouse_pos,
                    sf::Clock &clock,sf::Vector3f &eye,sf::Vector3f &center,
                    const sf::Vector2f &temp_center,float &alpha_radius);

bool collision(const world*w, const Character*h);

void find_path(const sf::Vector2i &temp_eye, sf::Vector2i &temp_pos_e,
               std::vector<char> &list_of_move, const world*w, bool &collision_Enemy_Hero,
               int &distance, char **board, const sf::Vector2i &map_size, int &receive_distance,
               bool &coop_mode);


#endif // CREATE_WORLD_H
