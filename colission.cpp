#include <queue>
#include "world.h"
#include "Character.h"

bool colission_path(const world* w,const int &pos_e_x,const int &pos_e_y)
{
    sf::FloatRect rect(pos_e_x-1,pos_e_y-1,3,3);
    for(size_t i=0; i!=w->rect.size(); i++)
    {
        if(w->rect[i].intersects(rect))
           return true;
    }
    return false;
}

void find_path(const int &pos_h_x,const int &pos_h_y,int &pos_e_x,
               int &pos_e_y,std::vector<char> &list_of_move,
               const world* w,bool &colission_Enemy_Hero)
{
    unsigned int i=0;
    size_t width_map=150,length_map=190;
    float board[width_map][length_map];
    bool find_p=false;

    std::queue<std::pair<size_t,size_t>> q;
    q.emplace(pos_h_x,pos_h_y);

    for(size_t w=0; w!=width_map; w++)
        for(size_t j=0; j!=length_map; j++)
            board[w][j]=0;
    size_t number=1;

    board[pos_h_x][pos_h_y]=-1;

    do
    {
        size_t temp=number;
        number=0;
        i++;
        for(size_t j=0; j!=temp; j++)
        {
            if(board[q.front().first+1][q.front().second]==0 and
                    !colission_path(w,q.front().first+2,q.front().second) and
                    !colission_path(w,q.front().first+1,q.front().second) and
                    q.front().first+1<width_map)
            {
                q.emplace(q.front().first+1,q.front().second);
                board[q.front().first+1][q.front().second]=i;
                number++;
            }

            if(board[q.front().first-1][q.front().second]==0 and q.front().first!=0 and
                    !colission_path(w,q.front().first-2,q.front().second) and
                   !colission_path(w,q.front().first-1,q.front().second))
            {
                q.emplace(q.front().first-1,q.front().second);
                board[q.front().first-1][q.front().second]=i;
                number++;
            }

            if(board[q.front().first][q.front().second+1]==0 and
                    !colission_path(w,q.front().first,q.front().second+2) and
                    !colission_path(w,q.front().first,q.front().second+1) and
                    q.front().second+1<length_map)
            {
                q.emplace(q.front().first,q.front().second+1);
                board[q.front().first][q.front().second+1]=i;
                number++;
            }

            if(board[q.front().first][q.front().second-1]==0 and q.front().second!=0 and
                    !colission_path(w,q.front().first,q.front().second-2) and
                    !colission_path(w,q.front().first,q.front().second-1))
            {
                q.emplace(q.front().first,q.front().second-1);
                board[q.front().first][q.front().second-1]=i;
                number++;
            }
            q.pop();
        }
        if(board[pos_e_x][pos_e_y]!=0)
            break;
        if(i>200*500)
            break;

    }while(!find_p);

    int temp_pos_e_x=pos_e_x;
    int temp_pos_e_y=pos_e_y;
    list_of_move.clear();

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
        if(pos_e_x==pos_h_x and pos_e_y==pos_h_y)
        {
            std::cout<<"colission"<<std::endl;
            colission_Enemy_Hero=true;
        }
}

bool colission(const world*w, const Character*h)
{

    for(size_t i=0; i!=w->rect.size(); i++)
    {
        if(w->rect[i].intersects(h->rect_))
           return true;
    }
    return false;
}



