#ifndef IMAGE_H
#define IMAGE_H

SDL_Renderer* mint_DisplayCreateRenderer(SDL_Window* window);
void mint_DisplayClearRenderer(SDL_Renderer* renderer);
void mint_DisplayDrawRect(SDL_Renderer* renderer, int x, int y, int width, int height, unsigned long colour);
void mint_DisplayDrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, unsigned long colour);
void mint_DisplayHexToSDLColor(SDL_Color* sdlColor, unsigned long colour);

#endif