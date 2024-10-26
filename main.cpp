#include <iostream>
#include <limits>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN "cls"
#define SQUARE "\xfe"
#else
#define CLEAR_SCREEN "clear"
#define SQUARE "\u25a0"
#endif
using namespace std;

short turn;
string sound = string(1, char(7));
const char e[] = SQUARE;
const short rLength = strlen(e) * 3 + 3;
char cells[3][rLength],row[rLength];

void moveCursorTo(const short &row, const short &column)
{
#ifdef _WIN32
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {static_cast<SHORT>(column), static_cast<SHORT>(row)});
#else
    cout << "\033[" << (row + 1) << ";" << (column + 1) << "H";
#endif
}

void clearFromCursor()
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD cellsWritten;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputCharacter(hConsole, (TCHAR)' ', csbi.dwSize.X * csbi.dwSize.Y, csbi.dwCursorPosition, &cellsWritten);
#else
    cout << "\033[J";
#endif
}

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

void Initialize_variables()
{
    turn = 0;
    itterateArray([](short i)
                  { strcpy(cells[i], row); });
}

bool Winner(const short &rw, const short &col, const short &rowLenght, const short &step)
{
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

void updateCells(const short &row, const short &column, const short &step, const char &newCell)
{
    moveCursorTo(row, (column / step) * 2);
    cout << newCell;
    moveCursorTo(3, 0);
    clearFromCursor();
    cout << endl;
}

int main()
{
    short position, rw, col, plr;
    const char xo[2] = {'X', 'O'};
    snprintf(row, rLength, "%s %s %s", e, e, e);
    short step = rLength / 3;
    char replay = 'y';
    while (replay == 'y')
    {
        Initialize_variables();
        reprint();
        while (turn < 9)
        {
            plr = turn % 2;
            cout << "player " << (plr + 1) << " turn" << endl;
            cin >> position;
            rw = (position - 1) / 3;
            col = ((position - 1) * step) % rLength;
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
                continue;
            }
            else
            {
                cells[rw][col] = xo[plr];
                turn++;
            }
            updateCells(rw, col, step, xo[plr]);
            if (turn >= 5 && Winner(rw, col, rLength, step))
            {
                cout << "player " << plr + 1 << " won!" << endl;
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
