#ifndef TEXTURE_H
#define TEXTURE_H

struct MintTexture {
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	int x;
	int y;
	int _width;
	int _height;
	int (*getWidth)(MintTexture* self);
	int (*getHeight)(MintTexture* self);
	void (*render)(MintTexture* self, int x, int y);
};

char mint_DisplayTextureSetup();
MintTexture* mint_DisplayTextureFromPNG(SDL_Renderer* renderer, char* path);

#endif