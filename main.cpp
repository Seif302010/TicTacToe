#include <iostream>
#include <limits>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#define SQUARE string(1,char(254))
#else
#define CLEAR_SCREEN "clear"
#define SQUARE "\u25a0"
#endif
using namespace std;

short turn, position, rw, col, plr;
string xo, e = SQUARE, sound = string(1,char(7)), cells[3][3];

void clearScreen()
{
    system(CLEAR_SCREEN);
}

void Initialize_variables()
{
    turn = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cells[i][j] = e;
    }
}

bool Winner(short &rw, short &col)
{

    if ((xo == cells[rw][(col + 1) % 3] && xo == cells[rw][(col + 2) % 3]) || (xo == cells[(rw + 1) % 3][col] && xo == cells[(rw + 2) % 3][col]))
        return true;
    else if ((min(rw, col) == 0 && max(rw, col) == 2) || rw == col)
    {
        if (rw == col)
            return xo == cells[(rw + 1) % 3][(col + 1) % 3] && xo == cells[(rw + 2) % 3][(col + 2) % 3];

        return xo == cells[(rw + 2) % 3][(col + 1) % 3] && xo == cells[(rw + 1) % 3][(col + 2) % 3];
    }
    return false;
}

void printBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << cells[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

void reprint()
{
    clearScreen();
    printBoard();
}

int main()
{
    char replay = 'y';
    while (replay == 'y')
    {
        Initialize_variables();
        reprint();
        while (turn < 9)
        {
            plr = turn % 2 + 1;
            cout << "player " << plr << " turn" << endl;
            cin >> position;
            rw = (position - 1) / 3;
            col = (position - 1) % 3;
            xo = turn % 2 == 0 ? "X" : "O";
            if (cin.fail())
            {
                cout << "Invalid input! the input should be a number" << endl
                     << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            else if (position < 1 || position > 9)
            {
                cout << "The number should be in the range from 1 to 9" << endl
                     << endl;
                continue;
            }
            else if (cells[rw][col] != e)
            {
                cout << "The selected square is not empty" << endl
                     << endl;
                continue;
            }
            else
            {
                cells[rw][col] = xo;
                turn++;
            }
            reprint();
            if (turn >= 5 && Winner(rw, col))
            {
                cout << "player " << plr << " won!" << endl;
                break;
            }
            else if (turn == 9)
                cout << "Draw" << endl;
        }
        cout << sound;
        cout << endl
             << "GAME OVER" << endl;

        cout << "Play again? (y,n)" << endl;
        while (true)
        {
            replay = tolower(cin.get());
            if (replay == '\n')
                continue;
            else if (replay == 'n' || replay == 'y')
                break;
            else
                cout << "Invalid input!" << endl
                     << endl;
        }
    }
    return 0;
}
