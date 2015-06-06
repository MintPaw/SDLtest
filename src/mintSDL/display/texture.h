#ifndef TEXTURE_H
#define TEXTURE_H

struct MintTexture {
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	int x;
	int y;
	int _width;
	int _height;
	int _alpha;
	int (*getWidth)(MintTexture* self);
	int (*getHeight)(MintTexture* self);
	void (*setColour)(MintTexture* self, SDL_Color* colour);
	void (*setAlpha)(MintTexture* self, char alpha);
	void (*render)(MintTexture* self);
};

char mint_DisplayTextureSetup();
MintTexture* mint_DisplayTextureFromPNG(SDL_Renderer* renderer, char* path);

#endif