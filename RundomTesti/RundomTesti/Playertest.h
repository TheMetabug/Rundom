#ifndef _PLAYER_
#define _PLAYER_
#include <es_util.h>
#include <Map.h>
#include <Tile.h>
#include <Layer.h>

using namespace yam2d;
//
class Playertest
{
public:
	SpriteGameObject* playertest;
	Texture* playertexture;
	void init ( ESContext *esContext );
	void update(ESContext* ctx, float deltaTime);
	void draw(ESContext *esContext);


	Playertest(void);
	~Playertest(void);
};
#endif

