#ifndef IMAGE_H
#define IMAGE_H

SDL_Renderer* mint_DisplayCreateRenderer(SDL_Window* window);
void mint_DisplayClearRenderer(SDL_Renderer* renderer);
void mint_DisplayHexToSDLColor(SDL_Color* sdlColor, unsigned long colour);

#endif