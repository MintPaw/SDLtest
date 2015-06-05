#ifndef TEXTURE_H
#define TEXTURE_H

char mint_DisplayTextureSetup();
SDL_Texture* mint_DisplayTextureLoadPNG(SDL_Renderer* renderer, char* path);

#endif