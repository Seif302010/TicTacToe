windres addIcon.rc -O coff -o addIcon-x64.res
windres addIcon.rc -O coff -F pe-i386 -o addIcon-x32.res
g++ -static -o tic_tac_toe-x64 main.cpp addIcon-x64.res
g++ -static -m32 -o tic_tac_toe-x32 main.cpp addIcon-x32.res