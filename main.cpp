#include <iostream>

using namespace std;

    short turn,position,rw,col,plr;
    char xo ,e=254,currentCell,sound=7, cells[3][3];

void Initialize_variables(){
    turn = 0;
    for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)
                cells[i][j]=e;
    }
}

bool Winner(short rw,short col){

    if((currentCell==cells[rw][(col+1)%3]&&currentCell==cells[rw][(col+2)%3]) || (currentCell==cells[(rw+1)%3][col]&&currentCell==cells[(rw+2)%3][col]))
        return true ;
    else if((min(rw,col)==0&&max(rw,col)==2)||rw==col){
        if(rw==col)
            return currentCell==cells[(rw+1)%3][(col+1)%3]&&currentCell==cells[(rw+2)%3][(col+2)%3];

        return currentCell==cells[(rw+2)%3][(col+1)%3]&&currentCell==cells[(rw+1)%3][(col+2)%3];
    }
    return false;
}

void PrintBoard(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)
                cout<<cells[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
}

int main()
{
    char cont='y';
    while(tolower(cont)=='y'){
        Initialize_variables();
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
            cout<<"Invalid inpute!"<<endl<<endl;
            continue;
        }
        currentCell=cells[rw][col];
        PrintBoard();
        if(turn>=5&&Winner(rw,col)){
            cout<<"player "<<plr<<" won!"<<sound<<endl;
            break;
        }
        else if(turn==9)
            cout<<"Draw"<<sound<<endl;
        }
        cout<<endl<<"GAME OVER"<<endl;
        while(true){
            cout<<"Play again? (y,n)"<<endl;
            cin>>cont;
            if(tolower(cont)=='n'||tolower(cont)=='y')
                break;
            else
                cout<<"Invalid inpute!"<<endl<<endl;
        }
    }
    return 0;
}
