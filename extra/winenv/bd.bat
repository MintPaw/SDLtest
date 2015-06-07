SET PATH=%PATH%;C:\MinGW\bin
del bin\game.exe
cls
g++ src\main.cpp^
	src\mintSDL\input.cpp^
	src\mintSDL\display\animation.cpp^
	src\mintSDL\display\display.cpp^
	src\mintSDL\display\geom.cpp^
	src\mintSDL\display\texture.cpp^
	-I lib\SDL2-2.0.3\include\^
	-L lib\SDL2-2.0.3\lib\x86\^
	-I lib\SDL2_image-2.0.0\i686-w64-mingw32\include\SDL2\^
	-L lib\SDL2_image-2.0.0\i686-w64-mingw32\lib^
	-lSDL2main^
	-lSDL2^
	-lmingw32^
	-lSDL2_image^
	-o bin\game.exe^
	-w -g -Wall