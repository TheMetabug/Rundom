#include <es_util.h>
#include <Map.h>
#include <Tile.h>
#include <Layer.h>
#include <Camera.h>
#include <Input.h>
#include <iostream>
#include <time.h>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "BackGround.h"
#include "Danger.h"
#include "Spark.h"
#include "Health.h"


using namespace yam2d;

namespace
{
	Map* map = 0;
	float count = 0;
	int gameState = 0;
}

std::vector <Danger> dangers;
std::vector <BackGround> backgrounds;

Player player;
Enemy enemy;
Danger danger;
Danger danger2;
Danger danger3;
Spark spark1;
Health health;
BackGround background1;
BackGround background2;
BackGround backjungle1;
BackGround backjungle2;
BackGround stepground1;
BackGround stepground2;
BackGround menu;
BackGround dead;


SpriteGameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, bool isWhiteTransparentColor = false)
{
	//Load texture to be used as texture for sprite.
	Texture* texture = new Texture(bitmapFileName.c_str());

	// If user wants to create texture which white colors is treated as atransparent color.
	if( isWhiteTransparentColor )
	{
		// Set white to transparent. Here color values are from 0 to 255 (RGB)
		texture->setTransparentColor(255,255,255);
	}

	// Create new sprite GameObject from texture.
	SpriteGameObject* gameObject = new SpriteGameObject(0,texture);

	// Resize the sprite to be correct size
	gameObject->setSize(sizeX, sizeY);

	return gameObject;

}

SpriteGameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, int clipStartX, int clipStartY, int clipSizeX, int clipSizeY, bool isWhiteTransparentColor = false )
{
	// Load texture to be used as texture for sprite.
	Texture* texture = new Texture(bitmapFileName.c_str());
	
	// If user wants to create texture which white colors is treated as atransparent color.
	if( isWhiteTransparentColor )
	{
		// Set white to transparent. Here color values are from 0 to 255 (RGB)
		texture->setTransparentColor(255,255,255);
	}

	// Create new sprite GameObject from texture.
	SpriteGameObject* gameObject = new SpriteGameObject(0,texture);

	// Resize the sprite to be correct size
	gameObject->setSize(sizeX, sizeY);

	// Specify clip area by start point and size in pixels
	Sprite::PixelClip clip;
	clip.topLeft.x = clipStartX;
	clip.topLeft.y = clipStartY;
	clip.clipSize.x = clipSizeX;
	clip.clipSize.y = clipSizeY;

	// Set pixel clip for sprite
	gameObject->getSprite()->setClip(float(texture->getWidth()), float(texture->getHeight()), clip );

	return gameObject;
}

//			Initialize the game
bool init ( ESContext *esContext )
{
	srand(time(NULL));

	// Level tile size
	vec2 tileSize(64,64);

	map = new Map(tileSize.x,tileSize.y);
		
	Layer* backgroundLayer = new Layer(map, "Background", 1.0f, true, false);
	
//			_BGLAYER0_
	map->addLayer(Map::BACKGROUND0, backgroundLayer );
//TAIVAS1
	Texture* texturebg1 =new Texture("sky.png");
	background1 = BackGround(texturebg1,vec2(0,-3.5f), 0.5f, 1280.0f, 335.0f, -3.5f);
	backgroundLayer->addGameObject(background1.background);
	backgrounds.push_back(background1);

	Texture* texturebg2 =new Texture("sky.png");
	background2 = BackGround(texturebg2,vec2(20,-3.5f), 0.5f, 1280.0f, 335.0f, -3.5f);
	backgroundLayer->addGameObject(background2.background);
	backgrounds.push_back(background2);

	Layer* objectLayer0 = new Layer(map, "Objects", 1.0f, true, false);
	Layer* objectLayer1 = new Layer(map, "Objects", 1.0f, true, false);
	Layer* objectLayer2 = new Layer(map, "Objects", 1.0f, true, false);
	Layer* objectLayerG = new Layer(map, "Objects", 1.0f, true, false);
	Layer* objectLayerM = new Layer(map, "Objects", 1.0f, true, false);
	
//				__LAYER0__
	map->addLayer(Map::MAPLAYER0, objectLayer0 );

//JUNGLEBG1
	Texture* texturebg3 =new Texture("jungle.png");
	backjungle1 = BackGround(texturebg3,vec2(0,1), 1.5f, 1280.0f, 436.0f, 1);
	objectLayer0->addGameObject(backjungle1.background);
	backgrounds.push_back(backjungle1);

	Texture* texturebg4 =new Texture("jungle.png");
	backjungle2 = BackGround(texturebg4,vec2(20,1), 1.5f, 1280.0f, 436.0f, 1);
	objectLayer0->addGameObject(backjungle2.background);
	backgrounds.push_back(backjungle2);

//				__LAYER1__
	map->addLayer(Map::MAPLAYER1, objectLayer1 );

	Texture* texturebgD =new Texture("dangerlady1.png");
	danger = Danger(texturebgD,vec2(16,1), 8.5f, 10, 50.0f, 50.0f, 13.0f, 1, 4, 10.0f);
	objectLayer1->addGameObject(danger.danger);
	dangers.push_back(danger);

	Texture* texturebgDD =new Texture("danger.png");
	danger2 = Danger(texturebgDD,vec2(16,3.2f), 3.5f, 0, 50.0f, 50.0f, 13.0f, 3.2f, 1, 20.0f);
	objectLayer1->addGameObject(danger2.danger);
	dangers.push_back(danger2);

	Texture* texturebgDDD =new Texture("danger.png");
	danger3 = Danger(texturebgDDD,vec2(16,3.2f), 15.5f, 0, 50.0f, 50.0f, 13.0f, 3.2f, 1, 20.0f);
	objectLayer1->addGameObject(danger3.danger);
	dangers.push_back(danger3);

	Texture* texturebgE =new Texture("hippo2.png");
	enemy = Enemy(texturebgE,vec2(0,0));
	objectLayer1->addGameObject(enemy.enemy);

//				__LAYER2__
	map->addLayer(Map::MAPLAYER2, objectLayer2);

	Texture* texturebg5 =new Texture("ground.png");
	stepground1 = BackGround(texturebg5,vec2(0,4.5f), 3.5f, 1280.0f, 170.0f, 4.5f);
	objectLayer2->addGameObject(stepground1.background);
	backgrounds.push_back(stepground1);

	Texture* texturebg6 =new Texture("ground.png");
	stepground2 = BackGround(texturebg6,vec2(20,4.5f), 3.5f, 1280.0f, 170.0f, 4.5f);
	objectLayer2->addGameObject(stepground2.background);
	backgrounds.push_back(stepground2);

//				__GUILAYER__
	map->addLayer(Map::GUILAYER1, objectLayerG );
//Spark
	Texture* texturesp =new Texture("iskuanim.png");
	spark1 = Spark(texturesp,vec2(20,20));
	objectLayerG->addGameObject(spark1.spark);
//Health
	Texture* texturehp =new Texture("hpbar.png");
	health = Health(texturehp,vec2(0,5));
	objectLayerG->addGameObject(health.health);
//player
	Texture* texturepl =new Texture("player_run1.png");
	player = Player(texturepl,vec2(-1,2.5), &health);
	objectLayerG->addGameObject(player.player);

//				_MENULAYER_
	map->addLayer(Map::GUILAYER2, objectLayerM );
//StartMenu

	Texture* texturemenu =new Texture("menu.png");
	menu = BackGround(texturemenu,vec2(0,0), 0, 1280.0f, 720.0f, 0);
	objectLayerM->addGameObject(menu.background);
	backgrounds.push_back(menu);
//DeathMenu

	Texture* texturedead =new Texture("death.png");
	dead = BackGround(texturedead,vec2(0,0), 0, 1280.0f, 720.0f, 0);
	objectLayerM->addGameObject(dead.background);
	backgrounds.push_back(dead);

		
	return true;
}

//						Deinitialize the game
void deinit ( ESContext *esContext )
{
	delete map;
}

//						Update game
void update( ESContext* ctx, float deltaTime )
{
	if(getKeyState(KeyCodes::KEY_ESCAPE))
	{
		exit(0);
	}

	if (gameState == 0)
		{
			menu.background->setPosition(0,0);
			dead.background->setPosition(400,400);
			if(getKeyState(KeyCodes::KEY_RETURN))
			{
			gameState = 1;
			}
		}

	if(gameState == 1)
		{
			menu.background->setPosition(400,400);
			dead.background->setPosition(400,400);
			count++;

			player.Update(deltaTime);
			enemy.Update(deltaTime);
			health.Update(deltaTime);
			
			// Update map. this will update all GameObjects inside a map layers.
			map->update(deltaTime);

			//	Collision between player and danger
			for (int i = 0; i < backgrounds.size(); i++)
			{
				backgrounds[i].Update(deltaTime);
			}

			for (int i = 0; i < dangers.size(); i++)
			{
				dangers[i].Update(deltaTime);
				if (player.hitx > dangers[i].hitx - 0.6f && player.hitx < dangers[i].hitx + 0.8f 
					&& player.hity > dangers[i].hity - 0.5f 
					&& player.hity -1.3f < dangers[i].hity + 0.5f /*danger.hit player.hity == danger.hity*/)
				{
					dangers[i].Respawn();
					player.DangerHit();
					spark1.Hit();
					spark1.spark->setPosition(dangers[i].hitx,dangers[i].hity);
				}
			}
		// death by hippo
			if (player.hitx <= -7.0f)
			{
				health.Hit();
				health.Hit();
				health.Hit();
				health.Hit();
				player.Death();				
			}

			if (player.hity >= 40.0f)
			{
				dangers[0].Respawn();
				dangers[1].Respawn();
				dangers[2].Respawn();
				player.die = 0;
				health.newGame();
				gameState = 3;
				dead.background->setPosition(0,0);
			}

		}

	if (gameState == 3)
	{
		if(getKeyState(KeyCodes::KEY_R))
		{
			gameState = 1;
			player.player->setPosition(-1,2.5);
		}
	}

	}
	

//			Draw game
void draw ( ESContext *esContext )
{
	glClearColor( 0.1f, 0.1f, 0.1f, 0.0f );

	glClear ( GL_COLOR_BUFFER_BIT );

	// Set screen size to camera.
	map->getCamera()->setScreenSize(esContext->width,esContext->height); 

	// Render map and all of its layers containing GameObjects to screen.
	map->render();
}


int main ( int argc, char *argv[] )
{

	ESContext esContext;
	esInitContext ( &esContext );
	esCreateWindow( &esContext, "Rundom: Hippo Edition", 1280, 720, ES_WINDOW_DEFAULT );
   
	if ( !init ( &esContext ) )
		return 0;

	esRegisterDrawFunc( &esContext, draw );
	esRegisterUpdateFunc( &esContext, update );
	esRegisterDeinitFunc( &esContext, deinit);

	esMainLoop ( &esContext );
	return 0;
}
