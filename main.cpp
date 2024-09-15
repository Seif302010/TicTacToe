#include <iostream>
#include <limits>
#include <cstring>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#define SQUARE string(1, char(254)).c_str()
#else
#define CLEAR_SCREEN "clear"
#define SQUARE string("\u25a0").c_str()
#endif
using namespace std;

short turn, position, rw, col, plr;
const char *xo[2] = {"X", "O"};
string sound = string(1, char(7));
char *cells[3][3];

void clearScreen()
{
    system(CLEAR_SCREEN);
}

void itterateArray(void (*func)(short, short))
{
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 3; j++)
        {
            func(i, j);
        }
    }
}

void allocateMemmory()
{
    itterateArray([](short i, short j)
                  { cells[i][j] = new char[strlen(SQUARE) + 1]; });
}

void freeMemory()
{
    itterateArray([](short i, short j)
                  { delete[] cells[i][j]; });
}

void Initialize_variables()
{
    turn = 0;
    itterateArray([](short i, short j)
                  { strcpy(cells[i][j], SQUARE); });
}

bool Winner(short &rw, short &col)
{
    const char *cell = cells[rw][col];
    if ((strcmp(cell, cells[rw][(col + 1) % 3]) == 0 && strcmp(cell, cells[rw][(col + 2) % 3]) == 0) ||
        (strcmp(cell, cells[(rw + 1) % 3][col]) == 0 && strcmp(cell, cells[(rw + 2) % 3][col]) == 0))
        return true;
    else if ((min(rw, col) == 0 && max(rw, col) == 2) || rw == col)
    {
        if (rw == col)
            return strcmp(cell, cells[(rw + 1) % 3][(col + 1) % 3]) == 0 && strcmp(cell, cells[(rw + 2) % 3][(col + 2) % 3]) == 0;

        return strcmp(cell, cells[(rw + 2) % 3][(col + 1) % 3]) == 0 && strcmp(cell, cells[(rw + 1) % 3][(col + 2) % 3]) == 0;
    }
    return false;
}

void printBoard()
{
    itterateArray([](short i, short j)
                  { cout << cells[i][j] << " ";
        if (j == 2) cout << endl; });
    cout << endl;
}

void reprint()
{
    clearScreen();
    printBoard();
}

int main()
{
    allocateMemmory();
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
            else if (strcmp(cells[rw][col], SQUARE) != 0)
            {
                cout << "The selected square is not empty" << endl
                     << endl;
                continue;
            }
            else
            {
                strcpy(cells[rw][col], xo[turn % 2]);
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
    freeMemory();
    return 0;
}
