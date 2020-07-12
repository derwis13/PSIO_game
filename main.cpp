#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <math.h>
#include <string>
#include <time.h>

#include "world.h"
#include "Character.h"
#include "menu.h"
#include "network.h"
#include "sound.h"
void Load_Texture(const std::string &nazwa,std::vector<GLuint> &Texturs,
                  unsigned int i);
void set_light();

void set_finish_square(const int &option,world *map,const sf::Vector3f &eye,
                       Sound *sound1,Sound *sound2,Sound *sound0,bool &running,Menu &menu,
                       int &game_status,sf::Vector3f &fr_eye);
float Hero::rot;
float Enemy::rot;



int main() {


    Network net;

    sf::Vector2i window_size(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height);
    Sound *sound1,*sound2,*sound0,*sound3;
    std::string r1="sound/run_1.ogg",r2="sound/run_2.wav",r0="sound/run_0.wav",r3="sound/fear_sound.wav";

    sound1 = new Sound(r1);
    sound2 = new Sound(r2);
    sound0 = new Sound(r0);
    sound3= new Sound(r3);

    bool coop_mode=false;
    bool host=false;
    bool fullscreen=false;

    //\\\\\\\\\\\\\\\\\\\\#############MENU#######################\\\\\\\\//

    sf::RenderWindow window1(sf::VideoMode(window_size.x, window_size.y), "Try to get out",sf::Style::Default);
    Menu menu(window1.getSize().x, window1.getSize().y);

    sound3->Play_Sound();
    sound3->music.setLoop(true);


    while (window1.isOpen())
    {
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                exit(0);
                window1.close();
            }
            if(event.type==sf::Event::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::Up or
                        event.key.code==sf::Keyboard::W)
                    menu.MoveUp();
                if(event.key.code==sf::Keyboard::Down or
                        event.key.code==sf::Keyboard::S)
                    menu.MoveDown();
                if(event.key.code==sf::Keyboard::Escape)
                    menu.actually_choose(0);
                if(event.key.code==sf::Keyboard::Enter and menu.actually_menu_==0)
                {
                    switch (menu.getItem())
                    {
                    case 0:
                        std::cout<<"Play is pressed"<<std::endl;
                        menu.actually_choose(1);
                        break;
                    case 1:
                        std::cout<<"Option is pressed"<<std::endl;
                        menu.actually_choose(2);
                        break;
                    case 2:
                        std::cout<<"Exit is pressed"<<std::endl;
                        window1.close();
                        exit(0);
                        break;
                    }
                    break;
                }
                if(event.key.code==sf::Keyboard::Enter and menu.actually_menu_==1)
                {
                    switch (menu.getItem())
                    {
                    case 0:
                        std::cout<<"Singleplayer is pressed"<<std::endl;
                        window1.close();
                        break;
                    case 1:
                        std::cout<<"Coop mode is pressed"<<std::endl;
                        menu.actually_choose(4);
                        break;
                    }
                    break;
                }
                if(event.key.code==sf::Keyboard::Enter and menu.actually_menu_==2)
                {
                    switch (menu.getItem())
                    {
                    case 0:
                        std::cout<<"Fullscreen is pressed"<<std::endl;
                        if(!fullscreen)
                        {
                        fullscreen=true;
                        window1.create(sf::VideoMode(window_size.x, window_size.y), "Try to get out",sf::Style::Fullscreen);
                        menu.actually_choose(0);
                        }
                        break;
                    case 1:
                        std::cout<<"Windowed screen is pressed"<<std::endl;
                        if(fullscreen)
                        {
                        fullscreen=false;
                        window1.create(sf::VideoMode(window_size.x, window_size.y), "Try to get out",sf::Style::Default);
                        menu.actually_choose(0);
                        }
                        break;
                    }
                    break;
                }
                if(event.key.code==sf::Keyboard::Enter and menu.actually_menu_==4)
                {
                    switch (menu.getItem())
                    {
                    case 0:
                        std::cout<<"Host a game is pressed"<<std::endl;
                        coop_mode=true;
                        host=true;
                        window1.close();
                        break;
                    case 1:
                        std::cout<<"Join a game is pressed"<<std::endl;
                        coop_mode=true;
                        window1.close();
                        break;
                    }
                }
            }
        }
        window1.clear();
        menu.setBackground(window1);
        if(menu.actually_menu_==0)
        {
            menu.main_menu_draw(window1);
        }
        if(menu.actually_menu_==1)
        {
            menu.play_menu_draw(window1);
        }
        if(menu.actually_menu_==2)
        {
            menu.option_menu_draw(window1);
        }
        if(menu.actually_menu_==4)
        {
            menu.coop_menu_draw(window1);
        }
        window1.display();

    }

    //\\\\\\\\\\\\\\\\\\\\#############GAME#######################\\\\\\\\//

    do
    {
        sound3->Stop_Sound();
        int game_status=0;
        int option;

        if(coop_mode)
            if(!net.conection)
                net.set_ip();

        sf::Vector3f eye(2,5,3);
        sf::Vector3f pos_e(2,5,1);
        sf::Vector3f center(eye.x,eye.y+1,eye.z);
        sf::Vector3f fr_eye=eye;

        sf::Vector2i map_size(150,190);

        bool colission_Enemy_Hero=false;

        char **board = new char *[map_size.x];
        for (unsigned int w = 0; w<map_size.x; w++)
            board[w] = new char [map_size.y];


        bool running = true;

        std::vector<GLuint>Texturs;
        Character *character1,*character2,*character3;

        world *map;

        if(coop_mode)
        {
            if(host)
            {
                net.seting_host();
                net.Receive(option);
                net.Send(option);

            }
            else
            {
                srand (time(NULL));
                net.Send(rand()%5+1);
                net.Receive(option);
            }
        }
        else
        {
            srand (time(NULL));
            option=rand()%5+1;
        }

        std::cout<<option<<std::endl;



        sf::Clock clock;
        sf::Clock time_of_game;
        clock.restart();
        time_of_game.restart();

        sf::Window window(sf::VideoMode(window_size.x,window_size.y),"try to get out", sf::Style::Default,sf::ContextSettings(32));

        if(fullscreen)
            window.create(sf::VideoMode(window_size.x,window_size.y),"try to get out", sf::Style::Fullscreen,sf::ContextSettings(32));

        window.setVerticalSyncEnabled(true);
        window.setActive(true);

        Load_Texture("picture/wall.png",Texturs,Texturs.size());
        Load_Texture("picture/grass.png",Texturs,Texturs.size());
        Load_Texture("picture/iron.png",Texturs,Texturs.size());
        Load_Texture("picture/devil.jpg",Texturs,Texturs.size());
        Load_Texture("picture/finish.jpg",Texturs,Texturs.size());

        glClearColor(0.3,0,0,0);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_SMOOTH);
        glShadeModel(GL_SMOOTH);

        set_light();
        set_viewport(window_size,eye,center);

        sf::Vector2f temp_center(center.x,center.y);
        float alpha_radius=0;

        while (running) {
            sf::Event event;

            window.setFramerateLimit(60);
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    running = false;
                    exit(0);
                }
                if(event.mouseWheelScroll.delta==-1)
                {
                    eye.z-=1;
                }
                if(event.mouseWheelScroll.delta==1)
                {
                    eye.z+=1;
                }
                static sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                int temp_mouse_pos_x=mouse_pos.x;
                mouse_pos = sf::Mouse::getPosition(window);

                float mouse_sensitivity=2;
                camera_setting(mouse_sensitivity,temp_mouse_pos_x,mouse_pos,clock,
                               eye,center,temp_center,alpha_radius);

                set_viewport(window_size,eye,center);
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
            glEnable (GL_COLOR_MATERIAL);

            static float rot=0;
            static int distance=0;
            static int receive_distance=map_size.x*map_size.y;

            map=new world(Texturs);
            character1 =new Hero(eye.x,eye.y,1,Texturs[2],Hero::rot);

            if(coop_mode)
            {
                if(host)
                {
                fr_eye=net.Receive_pos(fr_eye,rot);
                net.Send_pos(eye,Hero::rot);
                }
                else
                {
                net.Send_pos(eye,Hero::rot);
                fr_eye=net.Receive_pos(fr_eye,rot);
                }
                character3 =new Hero(fr_eye.x,fr_eye.y,1,Texturs[2],rot);
            }

            std::vector<char> list_of_move;

            if(time_of_game.getElapsedTime().asSeconds()<=10 and sound0->music.getStatus()==0)
            {
                sound0->Play_Sound();
                sound0->music.setLoop(true);
            }
            if(time_of_game.getElapsedTime().asSeconds()>=10)
            {
                if(sound1->music.getStatus()==0)
                {
                    sound0->Stop_Sound();
                    sound1->Play_Sound();
                }
                if(sound2->music.getStatus()==0 and time_of_game.getElapsedTime().asSeconds()>=16)
                {
                    sound2->Play_Sound();
                    sound2->music.setLoop(true);
                }

                character2 =new Enemy(pos_e,Texturs[3],Enemy::rot);
                sf::Vector2i temp_pos_e(pos_e.x,pos_e.y);
                sf::Vector2i temp_eye(eye.x,eye.y);
                sf::Vector2i temp_fr_eye(fr_eye.x,fr_eye.y);
                find_path(temp_eye,temp_pos_e,list_of_move,map,colission_Enemy_Hero,distance,board,map_size,
                          receive_distance,coop_mode);
                int speed_e=3;

                sf::Vector3f temp_position_e=pos_e;
                if(coop_mode)
                {
                    net.Send_distance(distance,pos_e,Enemy::rot);
                    net.Receive_distance(temp_position_e,Enemy::rot,receive_distance);
                }

                if(distance<receive_distance or !coop_mode)
                {
                    if(list_of_move.size()!=0)
                    {
                        if(list_of_move[0]=='r')
                        {
                            Enemy::rotate_Character(-90);
                            pos_e.x+=speed_e*clock.getElapsedTime().asSeconds();
                        }
                        if(list_of_move[0]=='l')
                        {
                            Enemy::rotate_Character(90);
                            pos_e.x-=speed_e*clock.getElapsedTime().asSeconds();
                        }
                        if(list_of_move[0]=='d')
                        {
                            Enemy::rotate_Character(180);
                            pos_e.y-=speed_e*clock.getElapsedTime().asSeconds();
                        }
                        if(list_of_move[0]=='u')
                        {
                            Enemy::rotate_Character(0);
                            pos_e.y+=speed_e*clock.getElapsedTime().asSeconds();
                        }
                    }
                }
                else
                {
                    pos_e=temp_position_e;
                }
                if(temp_fr_eye==temp_pos_e and coop_mode)
                    colission_Enemy_Hero=true;
            }

            if(colission_Enemy_Hero)
            {
                net.Send_distance(distance,pos_e,Enemy::rot);
                sound2->Stop_Sound();
                sound1->Stop_Sound();
                running=false;
                menu.GameOver(false);
            }
            set_finish_square(option,map,eye,sound1,sound2,sound0,running,menu,
                              game_status,fr_eye);

            if(running==false and coop_mode)
            {
                net.Send_pos(eye,Hero::rot);
            }
            set_finish_square(option,map,eye,sound1,sound2,sound0,running,menu,
                              game_status,fr_eye);

            move_camera(clock,eye,center,character1,map,temp_center,alpha_radius);
            set_viewport(window_size,eye,center);


            clock.restart();
            window.display();
        }

        delete(map);

        for(int i=0; i!=Texturs.size(); i++)
        {
            glDeleteTextures(1,&Texturs[i]);
        }

        for (unsigned int w = 0; w<map_size.x; w++)
            delete [] board[w];

        delete [] board;


        //\\\\\\\\\\\\\\\\\\\\#############MENU#######################\\\\\\\\//

        window1.create(sf::VideoMode(window_size.x, window_size.y), "Try to get out",sf::Style::Default);

        if(fullscreen)
            window1.create(sf::VideoMode(window_size.x, window_size.y), "Try to get out",sf::Style::Fullscreen);

        while (window1.isOpen())
        {
            sf::Event event;
            while (window1.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    exit(0);
                    window1.close();
                }
                if(event.type==sf::Event::KeyPressed)
                {
                    if(event.key.code==sf::Keyboard::Up or
                            event.key.code==sf::Keyboard::W)
                        menu.MoveUp();
                    if(event.key.code==sf::Keyboard::Down or
                            event.key.code==sf::Keyboard::S)
                        menu.MoveDown();
                    if(event.key.code==sf::Keyboard::Enter and menu.actually_menu_==3)
                        switch (menu.getItem())
                        {
                        case 0:
                            std::cout<<"Start over is pressed"<<std::endl;
                            window1.close();
                            break;
                        case 1:
                            std::cout<<"Exit is pressed"<<std::endl;
                            exit(0);
                            break;
                        }
                }
            }
            window1.clear();
            menu.setBackground(window1);
            if(menu.actually_menu_==3)
            {
                menu.game_over_menu_draw(window1);
            }
            window1.display();
        }
    }while(1==1);
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

void set_light()
{
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

}

void set_finish_square(const int &option, world *map, const sf::Vector3f &eye,
                       Sound *sound1, Sound *sound2, Sound *sound0, bool &running, Menu &menu,
                       int &game_status, sf::Vector3f &fr_eye)
{
    switch (option)
    {
    case 1:
    {
        sf::FloatRect fin(130,180,20,10);
        map->create_ground_finish(fin);
        if(fin.contains(eye.x,eye.y) or game_status==1)
        {
            sound2->Stop_Sound();
            sound1->Stop_Sound();
            sound0->Stop_Sound();
            running=false;
            menu.GameOver(true);
            game_status=1;
        }
        break;
    }
    case 2:
    {
        sf::FloatRect fin(36,138,18,10);
        map->create_ground_finish(fin);
        if(fin.contains(eye.x,eye.y) or fin.contains(fr_eye.x,fr_eye.y))
        {
            sound2->Stop_Sound();
            sound1->Stop_Sound();
            sound0->Stop_Sound();
            running=false;
            menu.GameOver(true);
            game_status=1;
        }
        break;
    }
    case 3:
    {
        sf::FloatRect fin(45,110,9,8);
        map->create_ground_finish(fin);
        if(fin.contains(eye.x,eye.y) or fin.contains(fr_eye.x,fr_eye.y))
        {
            sound2->Stop_Sound();
            sound1->Stop_Sound();
            sound0->Stop_Sound();
            running=false;
            menu.GameOver(true);
            game_status=1;
        }
        break;
    }
    case 4:
    {
        sf::FloatRect fin(115,138,8,10);
        map->create_ground_finish(fin);
        if(fin.contains(eye.x,eye.y) or fin.contains(fr_eye.x,fr_eye.y))
        {
            sound2->Stop_Sound();
            sound1->Stop_Sound();
            sound0->Stop_Sound();
            running=false;
            menu.GameOver(true);
            game_status=1;
        }
        break;
    }
    case 5:
    {
        sf::FloatRect fin(125,50,12,10);
        map->create_ground_finish(fin);
        if(fin.contains(eye.x,eye.y) or fin.contains(fr_eye.x,fr_eye.y))
        {
            sound2->Stop_Sound();
            sound1->Stop_Sound();
            sound0->Stop_Sound();
            running=false;
            menu.GameOver(true);
            game_status=1;
        }
        break;
    }
    }

}
