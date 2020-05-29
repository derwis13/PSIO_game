#define GL_SILENCE_DEPRECATION


#include <iostream>
#include <math.h>
#include <queue>
#include <string>

#include "world.h"
#include "Character.h"


void find_path(const int &pos_h_x,const int &pos_h_y,int &pos_e_x,int &pos_e_y,sf::Clock&clock, std::vector<char> &list_of_move);
void Load_Texture(const std::string &nazwa,std::vector<GLuint> &Texturs,unsigned int i);
float Hero::rot;

int main() {
    float eyex=0;
    float eyey=5;
    float eyez=3;

    float pos_e_x=0;
    float pos_e_y=5;
    float pos_e_z=1;

    float centerx=eyex;
    float centery=eyey+1;
    float centerz=eyez;
    sf::Window window(sf::VideoMode(1024, 768), "Try to get out", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    window.setActive(true);
    std::vector<GLuint>Texturs;

    Load_Texture("wall.png",Texturs,Texturs.size());
    Load_Texture("grass.png",Texturs,Texturs.size());
    Load_Texture("my_head1.jpg",Texturs,Texturs.size());
    Load_Texture("devil.jpg",Texturs,Texturs.size());

    glClearColor(0.3,0,0,0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SMOOTH);
    glShadeModel(GL_SMOOTH);



    GLfloat light_position[] = { 2.0, 0.0, 2.0, 1.0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };

    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    GLfloat global_ambient[] = {0.3, 0.3, 0.3, 0.1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glEnable(GL_NORMALIZE) ;
    bool running = true;

    world *map;
    Character *character1,*character2;

    sf::Clock clock;
    sf::Clock time_of_game;
    set_viewport(window.getSize().x, window.getSize().y,eyex,eyey,eyez,centerx,centery,centerz);
    while (running) {
        sf::Event event;
        window.setFramerateLimit(60);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }

            if(event.mouseWheelScroll.delta==-1)
            {
                eyez-=1;
            }
            if(event.mouseWheelScroll.delta==1)
            {
                eyez+=1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                Hero::rotate_Character(0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                Hero::rotate_Character(90);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                Hero::rotate_Character(-90);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                Hero::rotate_Character(180);
            static sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            unsigned int temp_mouse_pos_x=mouse_pos.x;
            mouse_pos = sf::Mouse::getPosition(window);
            float mouse_sensitivity=2;
            camera_setting(mouse_sensitivity,temp_mouse_pos_x,mouse_pos,clock,
                           eyex,eyey,eyez,centerx,centery,centerz);

            set_viewport(window.getSize().x, window.getSize().y,
                         eyex,eyey,eyez,centerx,centery,centerz);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
        glEnable (GL_COLOR_MATERIAL);

        map=new world(Texturs);
        character1 =new Hero(eyex,eyey+3,1,Texturs[2]);
        std::vector<char> list_of_move;
        if(time_of_game.getElapsedTime().asSeconds()>=5)
        {
            character2 =new Enemy(pos_e_x,pos_e_y,pos_e_z,Texturs[3]);
            int temp_pos_e_x=ceil(pos_e_x);
            int temp_pos_e_y=ceil(pos_e_y);
            find_path(eyex,eyey+3,temp_pos_e_x,temp_pos_e_y,clock,list_of_move);
            pos_e_x=temp_pos_e_x;
            pos_e_y=temp_pos_e_y;


            if(list_of_move.size()!=0)
            {
            if(list_of_move[0]=='r')
                pos_e_x+=1*clock.getElapsedTime().asSeconds();
            if(list_of_move[0]=='l')
                pos_e_x-=1*clock.getElapsedTime().asSeconds();
            if(list_of_move[0]=='d')
                pos_e_y-=1*clock.getElapsedTime().asSeconds();
            if(list_of_move[0]=='u')
                pos_e_x+=1*clock.getElapsedTime().asSeconds();
            }
        }

        move_camera(clock,character1->pos_y_,character1->pos_z_,
                    eyex,eyey,eyez,centerx,centery,centerz,character1,map);
        set_viewport(window.getSize().x, window.getSize().y,
                     eyex,eyey,eyez,centerx,centery,centerz);


        clock.restart();
        window.display();

    }
    delete(map);
    //delete(character1);
    //delete(character2);

    return 0;
}


void Load_Texture(const std::string &nazwa,std::vector<GLuint> &Texturs,unsigned int i)
{
    Texturs.emplace_back(i);
    sf::Image Image;
    if (!Image.loadFromFile(nazwa))
        std::cout<<"ERROR"<<std::endl;

    glGenTextures(1, &Texturs[i]);
    glBindTexture(GL_TEXTURE_2D, Texturs[i]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Image.getSize().x, Image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, Image.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
}

void find_path(const int &pos_h_x,const int &pos_h_y,int &pos_e_x,int &pos_e_y,sf::Clock&clock,std::vector<char> &list_of_move)
{
    unsigned int i=0;
    float board[450][590];
    bool find_p=false;

    std::queue<std::pair<int,int>> q;
    q.emplace(pos_h_x,pos_h_y);

    for(long w=0; w!=450; w++)
        for(long j=0; j!=590; j++)
            board[w][j]=0;
    long number=1;

    board[pos_h_x][pos_h_y]=-1;

    do
    {
        long temp=number;
        number=0;
        i++;
        for(long j=0; j!=temp; j++)
        {
            if(board[q.front().first+1][q.front().second]==0)
            {
                q.emplace(q.front().first+1,q.front().second);
                board[q.front().first+1][q.front().second]=i;
                number++;
            }

            if(board[q.front().first-1][q.front().second]==0 and q.front().first!=0)
            {
                q.emplace(q.front().first-1,q.front().second);
                board[q.front().first-1][q.front().second]=i;
                number++;
            }

            if(board[q.front().first][q.front().second+1]==0)
            {
                q.emplace(q.front().first,q.front().second+1);
                board[q.front().first][q.front().second+1]=i;
                number++;
            }

            if(board[q.front().first][q.front().second-1]==0 and q.front().second!=0)
            {
                q.emplace(q.front().first,q.front().second-1);
                board[q.front().first][q.front().second-1]=i;
                number++;
            }
            q.pop();
        }
        if(board[pos_e_x][pos_e_y]!=0)
            break;
    }while(!find_p);

    long temp_pos_e_x=pos_e_x;
    long temp_pos_e_y=pos_e_y;
    list_of_move.clear();
    do
    {
        if((board[temp_pos_e_x+1][temp_pos_e_y]<board[temp_pos_e_x][temp_pos_e_y] and board[temp_pos_e_x+1][temp_pos_e_y]!=0) or temp_pos_e_x+1==pos_h_x)
        {
            temp_pos_e_x=temp_pos_e_x+1;
            list_of_move.emplace_back('r');
        }
        if((board[temp_pos_e_x-1][temp_pos_e_y]<board[temp_pos_e_x][temp_pos_e_y] and board[temp_pos_e_x-1][temp_pos_e_y]!=0) or temp_pos_e_x-1==pos_h_x)
        {
            temp_pos_e_x=temp_pos_e_x-1;
            list_of_move.emplace_back('l');
        }
        if((board[temp_pos_e_x][temp_pos_e_y+1]<board[temp_pos_e_x][temp_pos_e_y] and board[temp_pos_e_x][temp_pos_e_y+1]!=0) or temp_pos_e_y+1==pos_h_y)
        {
            temp_pos_e_y=temp_pos_e_y+1;
            list_of_move.emplace_back('u');
        }
        if((board[temp_pos_e_x][temp_pos_e_y-1]<board[temp_pos_e_x][temp_pos_e_y] and board[temp_pos_e_x][temp_pos_e_y-1]!=0) or temp_pos_e_y-1==pos_h_y)
        {
            temp_pos_e_y=temp_pos_e_y-1;
            list_of_move.emplace_back('d');
        }

        if(temp_pos_e_x==pos_h_x and temp_pos_e_y==pos_h_y)
            break;
    }while(true);
}
