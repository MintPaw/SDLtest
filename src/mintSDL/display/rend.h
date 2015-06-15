#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>
#include "mintSDL/display/texture.h"

SDL_Renderer* mint_RendCreateSdlRenderer(SDL_Window* window, char vsync);
void mint_RendClearSdlRenderer(SDL_Renderer* renderer);
// void mint_RendHexToSDLColor(unsigned long colour, SDL_Color* sdlColour);
// unsigned long mint_RendSDLColorToHex(SDL_Color* sdlColor);

// void mint_RendSetColour(MintRend* rend, SDL_Color* colour);
// void mint_RendSetAlpha(MintRend* rend, char alpha);
// void mint_RendFree(MintRend* rend);

#endif