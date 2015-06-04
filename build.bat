SET PATH=%PATH%;C:\MinGW\bin
del bin\game.exe
cls
g++ src\main.cpp^
	src\mintSDL\input\input.cpp^
	-I lib\SDL2-2.0.3\include\^
	-I lib\SDL_image-1.2.12\include\^
	-L lib\SDL2-2.0.3\lib\x86\^
	-L lib\SDL_image-1.2.12\lib\^
	-lSDL2main^
	-lSDL2^
	-lmingw32^
	-lSDL_image^
	-o bin\game.exe^
	-w -g -Wall