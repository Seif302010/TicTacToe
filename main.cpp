#include <iostream>
#include <limits>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN "cls"
#define SQUARE string(1, char(254)).c_str()
#else
#define CLEAR_SCREEN "clear"
#define SQUARE string("\u25a0").c_str()
#endif
using namespace std;

short turn;
const char *row;
string sound = string(1, char(7));
char *cells[3];

void clearScreen()
{
    system(CLEAR_SCREEN);
}

void itterateArray(void (*func)(short))
{
    for (short i = 0; i < 3; i++)
    {
        func(i);
    }
}

void allocateMemmory()
{
    itterateArray([](short i)
                  { cells[i] = new char[strlen(row) + 1]; });
}

void freeMemory()
{
    itterateArray([](short i)
                  { delete[] cells[i]; });
}

void Initialize_variables()
{
    turn = 0;
    itterateArray([](short i)
                  { strcpy(cells[i], row); });
}

bool Winner(const short &rw, const short &col, const short &rowLenght, const short &step)
{
    string currentRow = cells[rw];
    char cell = cells[rw][col];
    if ((cell == cells[rw][(col + step) % rowLenght] && cell == cells[rw][(col + step * 2) % rowLenght]) ||
        (cell == cells[(rw + 1) % 3][col] && cell == cells[(rw + 2) % 3][col]))
        return true;
    else if ((min(rw, col) == 0 && max(rw, short(col / step)) == 2) || rw == col / step)
        return rw == col / step ? (cell == cells[(rw + 1) % 3][(col + step) % rowLenght] && cell == cells[(rw + 2) % 3][(col + step * 2) % rowLenght])
                                : (cell == cells[(rw + 2) % 3][(col + step) % rowLenght] && cell == cells[(rw + 1) % 3][(col + step * 2) % rowLenght]);
    return false;
}

void printBoard()
{
    itterateArray([](short i)
                  { cout << cells[i] << endl; });
    cout << endl;
}

void reprint()
{
    clearScreen();
    printBoard();
}

int main()
{
    short position, rw, col, plr;
    const char xo[2] = {'X', 'O'}, *e = SQUARE;
    row = (string(e) + ' ' + e + ' ' + e).c_str();
    short rowLength = strlen(row) + 1, step = rowLength / 3;
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
            col = ((position - 1) * step) % rowLength;
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
            else if (cells[rw][col] != *e)
            {
                cout << "The selected square is not empty" << endl
                     << endl;
                cout << "current cell: " << cells[rw][col] << endl;
                continue;
            }
            else
            {
                cells[rw][col] = xo[turn % 2];
                turn++;
            }
            reprint();
            if (turn >= 5 && Winner(rw, col, rowLength, step))
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
