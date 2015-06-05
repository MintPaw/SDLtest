#ifndef IMAGE_H
#define IMAGE_H

SDL_Renderer* mint_DisplayCreateRenderer(SDL_Window* window);
void mint_DisplayClearRenderer(SDL_Renderer* renderer);
SDL_Color* mint_DisplayHexToSDLColor(unsigned long colour);
unsigned long mint_DisplaySDLColorToHex(SDL_Color* sdlColor);

#endif