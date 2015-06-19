#include "mintSDL/display/texture.h"
#include "mintSDL/display/anim.h"
#include "mintSDL/maths/geom.h"
#include "mintSDL/maths/phys.h"
#include "game/player.h"

Player* player_Setup(MintSystem* _sys)
{
	Player* player = (Player*)malloc(sizeof(Player));
	player->dir4 = GEOM_RIGHT;
	player->mintTexture = mint_TextureFromPNG(_sys, "assets/img/player_blue.png");
	mint_TextureResizeHit(player->mintTexture, 52, 22);
	player->mintTexture->hitboxOffset = { 0, 44 };
	mint_PhysEnable(player->mintTexture, 1, 1);
	mint_PhysSetGravity(_sys, 0, 0);
	mint_PhysSetDamping(player->mintTexture, 50);

	mint_AnimCreateFromXML(player->mintTexture, "assets/img/player_blue.xml");

	int i;
	for (i = 0; i < player->mintTexture->totalAnims; i++) mint_AnimGetByIndex(player->mintTexture, i)->loop = 1;

	mint_AnimPlay(mint_AnimGetByName(player->mintTexture, "player_blue_SMG_downRight_running_"));

	return player;
}