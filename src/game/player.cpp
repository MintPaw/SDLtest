#include "mintSDL/display/texture.h"
#include "mintSDL/display/anim.h"
#include "mintSDL/maths/phys.h"

MintTexture* player_Setup(MintSystem* _sys)
{
	MintTexture* player = mint_TextureFromPNG(_sys, "assets/img/player_blue.png");
	mint_TextureResizeHit(player, 52, 66);
	mint_PhysEnable(player, _sys->world, 1, 1);
	mint_PhysSetGravity(_sys->world, 0, 0);
	mint_PhysSetDamping(player->phys, 50);

	mint_AnimCreateFromXML(player->animMan, "assets/img/player_blue.xml");

	int i;
	for (i = 0; i < player->animMan->totalAnims; i++) mint_AnimGetByIndex(player->animMan, i)->loop = 1;

	mint_AnimPlay(mint_AnimGetByName(player->animMan, "player_blue_SMG_downRight_running_"));

	return player;
}