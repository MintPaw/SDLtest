cmake_minimum_required (VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
project (SDLtest)

include_directories(
	src
	lib/win32/SDL2-2.0.3/include
	lib/win32/SDL2_image-2.0.0/include
	lib/win32/SDL2_ttf-2.0.12/include
	lib/win32/Box2d/include
)

link_directories(
	lib/win32/SDL2-2.0.3/lib/x86
	lib/win32/SDL2_image-2.0.0/lib/x86
	lib/win32/SDL2_ttf-2.0.12/lib/x86
	lib/win32/Box2d/lib
)

add_executable(SDLtest
	src/main.cpp
	src/mintSDL/display/anim.cpp
	src/mintSDL/display/draw.cpp
	src/mintSDL/display/rend.cpp
	src/mintSDL/display/texture.cpp
	src/mintSDL/display/trans.cpp
	src/mintSDL/display/tilemap.cpp
	src/mintSDL/maths/geom.cpp
	src/mintSDL/maths/phys.cpp
	src/mintSDL/maths/maths.cpp
	src/mintSDL/util/array.cpp
	src/mintSDL/util/input.cpp
	src/mintSDL/util/timer.cpp
	src/mintSDL/util/io.cpp
	src/mintSDL/gui/textbox.cpp
)

target_link_libraries(SDLtest
	SDL2main
	SDL2
	SDL2_image
	SDL2_ttf
	Box2D
)