fileName=tic_tac_toe

g++ -static -o ${fileName}-x64 main.cpp
g++ -static -m32 -o ${fileName}-x32 main.cpp

tar -cJvf linux-x32.tar.xz ${fileName}-x32
tar -cJvf linux-x64.tar.xz ${fileName}-x64
