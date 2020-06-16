#include <queue>
#include "world.h"
#include "Character.h"

struct str_findpathing
{
    int value;
    int i;
    int x;
    int y;
};

struct compare
{
    template < class T > bool operator ()( const T & el_1, const T & el_2) const {
        return el_1.value > el_2.value;
    }
};

int heuristics(const sf::Vector2i &temp_pos_e,const int &square_x,const int &square_y)
{
    int heur=abs(temp_pos_e.x-square_x)+abs(temp_pos_e.y-square_y);
        return heur;
}

bool colission_path(const world* w,const int &pos_e_x,const int &pos_e_y)
{
    sf::FloatRect rect(pos_e_x-1,pos_e_y-1,3,3);
    for(size_t i=0; i!=w->rect.size(); i++)
    {

        if(rect.intersects(w->rect[i]))
        {
           return true;
        }
    }
    return false;
}

void find_path(const sf::Vector2i &temp_eye, sf::Vector2i &temp_pos_e,
               std::vector<char> &list_of_move, const world* w,
               bool &collision_Enemy_Hero, int &distance, char **board, const sf::Vector2i &map_size,
               int &receive_distance, bool &coop_mode)
{
    bool find_p=false;

    for(unsigned int w=0; w!=map_size.x; w++)
        for(unsigned int j=0; j!=map_size.y; j++)
            board[w][j]='0';


   std::priority_queue < str_findpathing, std::vector < str_findpathing >, compare > q;
   q.push({0,0,temp_eye.x,temp_eye.y});

    do
    {
        sf::Vector2i actually_square(q.top().x,q.top().y);
        int i=q.top().i+1;
        if(actually_square.x<map_size.x and actually_square.y<map_size.y)
        {
            if(board[actually_square.x+1][actually_square.y]=='0' and
                    !colission_path(w,actually_square.x+2,actually_square.y) and
                    !colission_path(w,actually_square.x+1,actually_square.y))
            {
                int f=i+heuristics(temp_pos_e,actually_square.x+1,actually_square.y);
                q.push({f,i,actually_square.x+1,actually_square.y});
                board[actually_square.x+1][actually_square.y]='l';
            }

            if(board[actually_square.x][actually_square.y+1]=='0' and
                    !colission_path(w,actually_square.x,actually_square.y+2) and
                    !colission_path(w,actually_square.x,actually_square.y+1))
            {
                int f=i+heuristics(temp_pos_e,actually_square.x,actually_square.y+1);
                q.push({f,i,actually_square.x,actually_square.y+1});
                board[actually_square.x][actually_square.y+1]='d';
            }
        }
        if(actually_square.x>1 and actually_square.y>1)
        {
            if(board[actually_square.x-1][actually_square.y]=='0' and
                    !colission_path(w,actually_square.x-2,actually_square.y) and
                    !colission_path(w,actually_square.x-1,actually_square.y))
            {

                int f=i+heuristics(temp_pos_e,actually_square.x-1,actually_square.y);
                q.push({f,i,actually_square.x-1,actually_square.y});
                board[actually_square.x-1][actually_square.y]='r';
            }
            if(board[actually_square.x][actually_square.y-1]=='0' and
                    !colission_path(w,actually_square.x,actually_square.y-2) and
                    !colission_path(w,actually_square.x,actually_square.y-1))
            {
                int f=i+heuristics(temp_pos_e,actually_square.x,actually_square.y-1);
                q.push({f,i,actually_square.x,actually_square.y-1});
                board[actually_square.x][actually_square.y-1]='u';
            }
         }
            q.pop();
            distance=i;

            if(receive_distance+1<distance and receive_distance!=0 and coop_mode)
            {
               // std::cout<<"jest mniejsze"<<std::endl;
                break;
            }

        if(board[temp_pos_e.x][temp_pos_e.y]!='0')
        {
            break;
       }
    }while(!q.empty());

    list_of_move.clear();

    list_of_move.emplace_back(board[temp_pos_e.x][temp_pos_e.y]);

    if(temp_eye==temp_pos_e)
        collision_Enemy_Hero=true;


}

bool collision(const world*w, const Character*h)
{

    for(size_t i=0; i!=w->rect.size(); i++)
    {
        if(w->rect[i].intersects(h->rect_))
           return true;
    }
    return false;
}



