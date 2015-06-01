SET PATH=%PATH%;C:\MinGW\bin
del bin\game.exe
cls
g++ src\main.cpp -I lib\SDL2-2.0.3\include\ -L lib\SDL2-2.0.3\lib\x86\ -lSDL2main -lSDL2 -lmingw32 -o bin\game.exe -w