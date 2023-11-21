#include <iostream>

using namespace std;

    short turn = 0,position,rw,col,plr;
    char xo ,e=254, cells[3][3]={
        {e,e,e},
        {e,e,e},
        {e,e,e}
    };

bool Winner(short rw,short col){

    char currentCell=cells[rw][col];

    if(currentCell==cells[rw][(col+1)%3]&&currentCell==cells[rw][(col+2)%3])
        return true;
    if(currentCell==cells[(rw+1)%3][col]&&currentCell==cells[(rw+2)%3][col])
        return true;
    if(rw==1&&col==1)
        return (currentCell==cells[rw+1][col+1]&&currentCell==cells[rw-1][col-1])||(currentCell==cells[rw+1][col-1]&&currentCell==cells[rw-1][col+1]);
    if((rw==0&&col==0)||(rw==2&&col==2))
        return currentCell==cells[(rw+1)%3][(col+1)%3]&&currentCell==cells[(rw+2)%3][(col+2)%3];
    if((rw==0&&col==2)||(rw==2&&col==0))
        return currentCell==cells[(rw+2)%3][(col+1)%3]&&currentCell==cells[(rw+1)%3][(col+2)%3];

    return false;
}

void PrintBoard(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)
                cout<<cells[i][j]<<" ";
            cout<<endl;
        }
}

int main()
{
    PrintBoard();
    while(turn!=9){
        plr=turn%2+1;
        cout<<"player "<<plr<<" turn"<<endl;
        cin>>position;
        rw=(position-1)/3;col=(position-1)%3;
        xo=turn%2==0?'X':'O';
        if(cells[rw][col]==e&&(position>=1&&position<=9)){
            cells[rw][col]=xo;
            turn++;
        }
        else{
            cout<<"Invalid inpute! "<<endl<<endl;
            continue;
        }
        PrintBoard();
    if(turn>=5&&Winner(rw,col)){
        cout<<"player "<<plr<<" won!"<<endl;
        break;
    }
    else if(turn==9)
        cout<<"Draw";
    }
    cout<<endl<<"GAME OVER"<<endl;
    return 0;
}
