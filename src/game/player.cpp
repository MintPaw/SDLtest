#include "mintSDL/display/texture.h"
#include "mintSDL/display/anim.h"
#include "mintSDL/maths/phys.h"

MintTexture* player_Setup(MintSystem* _sys)
{
	MintTexture* player = mint_TextureFromPNG(_sys, "assets/img/player_blue.png");
	mint_TextureResizeHit(player, 52, 66);
	mint_PhysEnable(player, 1, 1);
	mint_PhysSetGravity(_sys, 0, 0);
	mint_PhysSetDamping(player, 50);

	mint_AnimCreateFromXML(player, "assets/img/player_blue.xml");

	int i;
	for (i = 0; i < player->totalAnims; i++) mint_AnimGetByIndex(player, i)->loop = 1;

	mint_AnimPlay(mint_AnimGetByName(player, "player_blue_SMG_downRight_running_"));

	return player;
}