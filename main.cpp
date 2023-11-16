#include <iostream>

using namespace std;

bool gameOver(short rw,short col,char cells[3][3]){
            if(cells[rw][col]==cells[rw][(col+1)%3]&&cells[rw][col]==cells[rw][(col+2)%3])
                return true;
            if(cells[rw][col]==cells[(rw+1)%3][col]&&cells[rw][col]==cells[(rw+2)%3][col])
                return true;
            if(rw==0&&col==0||rw==2&&col==2)
                return cells[rw][col]==cells[(rw+1)%3][(col+1)%3]&&cells[rw][col]==cells[(rw+2)%3][(col+2)%3];
            if(rw==0&&col==2||rw==2&&col==0)
                return cells[rw][col]==cells[(rw+2)%3][(col+1)%3]&&cells[rw][col]==cells[(rw+1)%3][(col+2)%3];
    return false;
}

int main()
{
    short turn = 0,position,rw,col,plr;
    char xo , cells[3][3]={
        {'0','0','0'},
        {'0','0','0'},
        {'0','0','0'}
    };
    while(turn!=9){
        plr=turn%2+1;
        cout<<"player "<<plr<<" turn"<<endl;
        cin>>position;
        rw=(position-1)/3;col=(position-1)%3;
        xo=turn%2==0?'X':'O';
        if(cells[rw][col]=='0'||position>1&&position<=9){
            cells[rw][col]=xo;
            turn++;
        }
        else{
            cout<<"Invalid inpute! "<<endl<<endl;
            continue;
        }

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)
                cout<<cells[i][j]<<" ";
            cout<<endl;
        }
    if(turn>=5&&gameOver(rw,col,cells)){
        cout<<"player "<<plr<<" won!"<<endl;
        break;
    }

    }
    cout<<endl<<"GAME OVER"<<endl;
    return 0;
}
