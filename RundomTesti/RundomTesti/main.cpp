#include <es_util.h>
#include <Map.h>
#include <Tile.h>
#include <Layer.h>
#include <Camera.h>
#include <Input.h>
#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <sstream>
#include <irrKlang.h>
#include "Player.h"
#include "Enemy.h"
#include "BackGround.h"
#include "Danger.h"
#include "Spark.h"
#include "Health.h"
#include "Score.h"
#include "Buttons.h"
#include <algorithm>

template <class T>
std::string to_string(T t)
{
        std::stringstream s;
        s << t;
        return s.str();
}

using namespace yam2d;
using namespace irrklang;

namespace
{
	// Enable sound engine IrrKlang
	ISoundEngine* engine = createIrrKlangDevice();

	float count = 0;

	int gameState = 0;
	int letterState = 0;
	int rc;
	int dindex = 0;

	int autsphase = 0;
	int autsrand = 0;
	int nomphase = 0;
	int nomrand = 0;
	int hopphase = 0;
	int hoprand = 0;
	int noophase = 0;
	int noorand = 0;

	bool isButtonPressed = false;
	bool isPlayerScreamed = false;
	bool isScoresRead = false;

	// Enable SQLite
	sqlite3 *db;
	
	std::string scoreList;
}

std::vector <Danger> dangers;
std::vector <BackGround> backgrounds;
std::vector <Buttons> buttons;

Player player;
Enemy enemy;
Danger danger;
Danger danger2;
Danger danger3;
Danger notDanger;
Danger apple;
Danger banana;
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
BackGround insertText;
Buttons button1;
Score* score;
Map* map = 0;


static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	std::string namez = argv[1];
	namez += " ";
	namez += argv[0];
	score->scoreTexts[dindex]->setText(namez);
    printf("\n");
	dindex++;
    return 0;
}

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

// Reads the highscore file and returns an vector of the scores
std::vector<int> parseHighscoreFile(std::string& fileName)
{
	std::vector<int> highscores;

	std::ifstream highscoreFile(fileName);
	if(highscoreFile.is_open())
	{
		while(highscoreFile.good())
		{
			std::string line;
			int score;
			std::getline(highscoreFile, line);
			
			score = atoi(line.c_str());
			if(score != 0)
				highscores.push_back(score);
		}
	}

	highscoreFile.close();
	
	return highscores;
}

void writeHighScores(int x)
{

	std::string Scores = "INSERT INTO scores VALUES ("+to_string(x)+",'"+scoreList+"');"; 

	rc = sqlite3_exec(db, Scores.c_str() , NULL, 0, NULL);

	if (rc!=SQLITE_OK)
	{
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}

}

void PlayAuts();
void PlayNom();
void PlayNoo();
void PlayHop();

//			Initialize the game
bool init ( ESContext *esContext )
{	
	rc = sqlite3_open("highscore.db", &db);

	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}

	engine->play2D("music.wav", true);

	srand(time(NULL));

	double speedsky =  1.0f;
	double speedskymax = 3.0f;

	double speedforest = 1.5f;
	double speedforestmax = 5.0f;

	double speedground = 4.0f;
	double speedgroundmax = 10.0f;

	// Level tile size
	vec2 tileSize(64,64);

	map = new Map(tileSize.x,tileSize.y);
		
	Layer* backgroundLayer = new Layer(map, "Background", 1.0f, true, false);
	
//			_BGLAYER0_
	map->addLayer(Map::BACKGROUND0, backgroundLayer );
//TAIVAS1
	Texture* texturebg1 =new Texture("sky.png");
	background1 = BackGround(texturebg1,vec2(0,-3.5f), speedsky, speedskymax,
			1280.0f, 335.0f, -3.5f);
	backgroundLayer->addGameObject(background1.background);
	backgrounds.push_back(background1);

	Texture* texturebg2 =new Texture("sky.png");
	background2 = BackGround(texturebg2,vec2(20,-3.5f), speedsky, speedskymax,
			1280.0f, 335.0f, -3.5f);
	backgroundLayer->addGameObject(background2.background);
	backgrounds.push_back(background2);

// CREATELAYERS
	Layer* objectLayer0 = new Layer(map, "Objects", 1.0f, true, false);
	Layer* objectLayer1 = new Layer(map, "Objects", 1.0f, true, false);
	Layer* objectLayer2 = new Layer(map, "Objects", 1.0f, true, false);
	Layer* objectLayerG = new Layer(map, "Objects", 1.0f, true, false);
	Layer* objectLayerM = new Layer(map, "Objects", 1.0f, true, false);
	Layer* objectLayerU = new Layer(map, "Objects", 1.0f, true, false);
	
//				__LAYER0__
	map->addLayer(Map::MAPLAYER0, objectLayer0 );

//JUNGLEBG1
	Texture* texturebg3 =new Texture("jungle.png");
	backjungle1 = BackGround(texturebg3,vec2(0,1), speedforest, speedforestmax,
			1280.0f, 436.0f, 1);
	objectLayer0->addGameObject(backjungle1.background);
	backgrounds.push_back(backjungle1);

	Texture* texturebg4 =new Texture("jungle.png");
	backjungle2 = BackGround(texturebg4,vec2(20,1), speedforest, speedforestmax,
			1280.0f, 436.0f, 1);
	objectLayer0->addGameObject(backjungle2.background);
	backgrounds.push_back(backjungle2);

//				__LAYER1__
	map->addLayer(Map::MAPLAYER1, objectLayer1 );

	Texture* texturebgD =new Texture("dangerlady1.png");
	danger = Danger(texturebgD,vec2(16,1), 8.5f, 18, 50.0f, 50.0f, 13.0f, 1, 4, 10.0f);
	objectLayer1->addGameObject(danger.danger);
	dangers.push_back(danger);

	Texture* texturebgDD =new Texture("lisko.png");
	danger2 = Danger(texturebgDD,vec2(16,3.2f), 3.5f, 0, 75.0f, 50.0f, 13.0f, 3.2f, 4, 10.0f);
	objectLayer1->addGameObject(danger2.danger);
	dangers.push_back(danger2);

	Texture* texturebgDDD =new Texture("cheeta.png");
	danger3 = Danger(texturebgDDD,vec2(16,3.1f), 15.5f, 0, 94.0f, 50.0f, 13.0f, 3.1f, 6, 20.0f);
	objectLayer1->addGameObject(danger3.danger);
	dangers.push_back(danger3);

	Texture* textureFruit1 =new Texture("mansikka.png");
	notDanger = Danger(textureFruit1,vec2(29,2.0f), 2.5f, 13, 32.0f, 32.0f, 13.0f, 2.0f, 1, 20.0f);
	objectLayer1->addGameObject(notDanger.danger);

	Texture* textureFruit2 =new Texture("banana.png");
	banana = Danger(textureFruit2,vec2(18,2.0f), 2.5f, 18, 32.0f, 32.0f, 13.0f, 2.0f, 1, 20.0f);
	objectLayer1->addGameObject(banana.danger);

	Texture* textureFruit3 =new Texture("omena.png");
	apple = Danger(textureFruit3,vec2(40,2.0f), 2.5f, 23, 32.0f, 32.0f, 13.0f, 2.0f, 1, 20.0f);
	objectLayer1->addGameObject(apple.danger);

	Texture* texturebgE =new Texture("hippo2.png");
	enemy = Enemy(texturebgE,vec2(0,0));
	objectLayer1->addGameObject(enemy.enemy);

//				__LAYER2__
	map->addLayer(Map::MAPLAYER2, objectLayer2);

	Texture* texturebg5 =new Texture("groundoma.png");
	stepground1 = BackGround(texturebg5,vec2(0,4.3f), speedground, speedgroundmax,
			1280.0f, 170.0f, 4.3f);
	objectLayer2->addGameObject(stepground1.background);
	backgrounds.push_back(stepground1);

	Texture* texturebg6 =new Texture("groundoma.png");
	stepground2 = BackGround(texturebg6,vec2(20,4.3f), speedground, speedgroundmax,
			1280.0f, 170.0f, 4.3f);
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
	Texture* texturemenu =new Texture("menu4.png");
	menu = BackGround(texturemenu,vec2(0,0), 0, 0, 1280.0f, 720.0f, 0);
	objectLayerM->addGameObject(menu.background);
	backgrounds.push_back(menu);
//DeathMenu
	Texture* texturedead =new Texture("death2.png");
	dead = BackGround(texturedead,vec2(0,0), 0, 0, 1280.0f, 720.0f, 0);
	objectLayerM->addGameObject(dead.background);
	backgrounds.push_back(dead);
	map->addLayer(Map::GUILAYER3, objectLayerU);
	//InsertText
	Texture* textureInsert =new Texture("insertname.png");
	insertText = BackGround(textureInsert,vec2(0,-6), 0, 0, 250.0f, 100.0f, 0);
	objectLayerM->addGameObject(insertText.background);
	backgrounds.push_back(insertText);

	Texture* textureButton1 = new Texture("button2.png");
	button1 = Buttons(textureButton1, vec2(0,-2),1);
	objectLayerU->addGameObject(button1.buttons);
	buttons.push_back(button1);


//Text objects
	score = new Score("Fixedsys_24_Bold.png", "Fixedsys_24_Bold.dat", &health);
	score->totalTimeText->setPosition(vec2(0,-4));
	objectLayerU->addGameObject(score->totalTimeText);

	score->fpsText->setPosition(vec2(9,5.4f));
	objectLayerU->addGameObject(score->fpsText);

	score->nameText1->setPosition(vec2(400,400));
	objectLayerU->addGameObject(score->nameText1);

	score->nameText2->setPosition(vec2(400,400));
	objectLayerU->addGameObject(score->nameText2);

	score->nameText3->setPosition(vec2(400,400));
	objectLayerU->addGameObject(score->nameText3);

	for (int i = 0; i < 5; i++)
	{
		score->scoreTextObjects[i]->setPosition(vec2(7,-4 + i*0.5f));
		objectLayerM->addGameObject(score->scoreTextObjects[i]);
	}
		
	return true;
}

//						Deinitialize the game
void deinit ( ESContext *esContext )
{
	engine->drop(); // delete engine
	sqlite3_close(db);

	delete map;
	delete score;
}

//						Update game5
void update( ESContext* ctx, float deltaTime )
{
	if(getKeyState(KeyCodes::KEY_ESCAPE))
	{
		deinit(ctx);
		exit(0);
	}

	if(player.isHeJumping == true)
	{
		PlayHop();
	}

	int number = button1.Update(deltaTime);



	switch(gameState)
	{
	case 0:
			menu.background->setPosition(0,0);
			insertText.background->setPosition(400,400);
			dead.background->setPosition(400,400);
			//gameState = 1;
			button1.buttons->setPosition(-6, 1);
			switch (number)
			{
				case 1:
					gameState = 1;
					break;
				case 2:
					break;
				case 3:
					break;
			}
		break;
	case 1:
		
		switch (letterState)
			{
			case 0:
				insertText.background->setPosition(0,0.35f);
				button1.buttons->setPosition(-400, 400);
				insertText.background->setPosition(0,0.35f);
				score->m_nameText1->setText( to_string(score->letters[score->lindex]));
				score->nameText1->setPosition(-0.5f,0);
				break;
			case 1:
				score->m_nameText2->setText( to_string(score->letters[score->lindex]));
				score->nameText2->setPosition(0,0);
				break;
			case 2:
				score->m_nameText3->setText( to_string(score->letters[score->lindex]));
				score->nameText3->setPosition(0.5f,0);
				break;
			case 3: 
				//gameState = 2;
				//button1.buttons->setPosition(4, 4);
				if(getKeyState(KeyCodes::KEY_RETURN))
				{
					menu.background->setPosition(400,400);
					insertText.background->setPosition(400,400);
					score->nameText1->setPosition(-0.5f,-5);
					score->nameText2->setPosition(0,-5);
					score->nameText3->setPosition(0.5f,-5);

					gameState = 2;
				}

				break;
				}

			if(isButtonPressed == false)
			{
				if(getKeyState(KeyCodes::KEY_DOWN))
					{
						score->lindex++;
						isButtonPressed = true;
						if (score->lindex > 25)
						{
							score->lindex = 25;
						}
					}

				if(getKeyState(KeyCodes::KEY_UP))
					{
						score->lindex--;
						isButtonPressed = true;
						if (score->lindex < 0)
						{
							score->lindex = 0;
						}
					}

				if(getKeyState(KeyCodes::KEY_RETURN))
				{
					letterState++;
					scoreList.push_back(score->letters[score->lindex]);
					isButtonPressed = true;
				}
			}
			else if(!getKeyState(KeyCodes::KEY_DOWN) && !getKeyState(KeyCodes::KEY_UP) && !getKeyState(KeyCodes::KEY_RETURN))
			{
				isButtonPressed = false;
			}
		break;
	case 2:
			count++;

			button1.buttons->setPosition(400, 400);

			dangers[0].speed = 8.5f * (1 + score->highscore/20000);
			dangers[1].speed = 3.5f * (1 + score->highscore/20000);
			dangers[2].speed = 15.5f * (1 + score->highscore/20000);

			player.Update(deltaTime);
			enemy.Update(deltaTime);
			health.Update(deltaTime);
			score->update(deltaTime);
			notDanger.Update(deltaTime);
			apple.Update(deltaTime);
			banana.Update(deltaTime);
			map->update(deltaTime);

			score->highscore += backgrounds[0].boost/10;

			if(player.isHeDead == true)
				{
					if(isPlayerScreamed == false)
					{
						PlayNoo();
					}
				}
			
			for (size_t i = 0; i < backgrounds.size(); i++)
			{
				backgrounds[i].Update(deltaTime);
			}

			for (size_t i = 0; i < dangers.size(); i++)
			{

				dangers[i].Update(deltaTime);
				//	Collision between player and danger
				if ((player.hitx > dangers[i].hitx - 0.6f && player.hitx < dangers[i].hitx + 0.8f 
					&& player.hity > dangers[i].hity - 0.5f 
					&& player.hity -1.3f < dangers[i].hity + 0.5f) && player.isHeBlinking == false)
				{
					if(player.isHeDead == false)
					{
						PlayAuts();
						//engine->play2D("ouch.wav", false);
					}
					dangers[i].Respawn();
					player.DangerHit();
					player.Blink();
					
				// spark effect
					spark1.Hit();
					spark1.spark->setPosition((float)dangers[i].hitx,(float)dangers[i].hity);
				// slow effect
					for (int i = 0; i < 6; i++)
					{
						backgrounds[i].Slow();
					}
				// player slow effect
					player.Slow();
				}

				// Player pickups a bonus
				if (notDanger.danger->collidesTo(player.player))
				{
					PlayNom();
					//engine->play2D("pickup1.wav", false);
					notDanger.Respawn();
					health.Medkit();
					score->strawberry();
				}
				// Player pickups a bonus
				if (banana.danger->collidesTo(player.player))
				{
					PlayNom();
					//engine->play2D("pickup1.wav", false);
					banana.Respawn();
					//health.Medkit();
					score->banaani();
				}
				// Player pickups a bonus
				if (apple.danger->collidesTo(player.player))
				{
					PlayNom();
					//engine->play2D("pickup1.wav", false);
					apple.Respawn();
					//health.Medkit();
					score->omena();
				}
			}
			// Hit hippo
			if (player.hitx <= -6.0f)
			{
				//health.hp = 0;
				//player.Death();
				PlayAuts();
				player.Blink();
				player.HippoHit();
				if(player.isHeDead == true)
				{
					if(isPlayerScreamed == false)
					{
						PlayNoo();
					}
				}
			}
		
			if (player.hity >= 40.0f)
			{
				dangers[0].Respawn();
				dangers[1].Respawn();
				dangers[2].Respawn();
				notDanger.Respawn();
				player.die = 0;
				engine->play2D("deathscreen.wav", false);
				health.newGame();
				gameState = 3;
				dead.background->setPosition(0,2);
			}
		break;
	case 3:
		if (isScoresRead == false)
		{
			writeHighScores(ceil(score->highscore));
			sqlite3_exec(db, "select * FROM scores ORDER BY score DESC LIMIT 0, 5;", callback, NULL, NULL);
			isScoresRead = true;
		}

		for (size_t i = 0; i < score->scoreTexts.size(); i++)
		{
			score->scoreTextObjects[i]->setPosition(vec2(7,-4.5f + i*0.5f));
		}

		if(getKeyState(KeyCodes::KEY_R))
		{
			gameState = 2;
			player.player->setPosition(-1,2.5);
			score->highscore = 0;
			isPlayerScreamed = false;
			isScoresRead = false;
			dindex = 0;
			dead.background->setPosition(400,400);

			for (int i = 0; i < 5; i++)
			{
				score->scoreTextObjects[i]->setPosition(vec2(-15,0));
			}
		}
		break;
	}
}	

//			Draw game
void draw ( ESContext *esContext )
{
	glClearColor( 0.0f, 0.0f, 1.0f, 0.0f );

	glClear ( GL_COLOR_BUFFER_BIT );

	map->getCamera()->setScreenSize(esContext->width,esContext->height); 

	score->render(0.0f,0.0f);

	map->render();
}




int main ( int argc, char *argv[] )
{

	ESContext esContext;
	esInitContext ( &esContext );
	esCreateWindow( &esContext, "Rundom: Jungle", 1280, 720, ES_WINDOW_DEFAULT );
   
	if ( !init ( &esContext ) )
		return 0;

	esRegisterDrawFunc( &esContext, draw );
	esRegisterUpdateFunc( &esContext, update );
	esRegisterDeinitFunc( &esContext, deinit);

	esMainLoop ( &esContext );
	return 0;
}

void PlayAuts()
{
	autsrand = rand() %80;
	std::cout << autsrand << std::endl;
	if(autsrand >= 0 && autsrand <=25)
	{
		autsphase = 1;
	}
	if(autsrand >= 26 && autsrand <=45)
	{
		autsphase = 2;
	}
	if(autsrand >= 46 && autsrand <=80)
	{
		autsphase = 3;
	}
	switch(autsphase)
	{
		case 0:
			break;
		case 1:
			engine->play2D("auts1.wav", false);
			autsphase = 0;
			break;
		case 2:
			engine->play2D("auts2.wav", false);
			autsphase = 0;
			break;
		case 3:
			std::cout << "auts" << std::endl;
			engine->play2D("auts3.wav", false);
			autsphase = 0;
			break;
	}

}

void PlayNom()
{
	nomrand = rand() %80;
	std::cout << hoprand << std::endl;
	if(nomrand >= 0 && nomrand <=25)
	{
		nomphase = 1;
	}
	else if(nomrand >= 26 && nomrand <=45)
	{
		hopphase = 2;
	}
	else if(nomrand >= 46 && nomrand <=80)
	{
		nomphase = 3;
	}
	switch(nomphase)
	{
		case 0:
			break;
		case 1:
			engine->play2D("omnom1.wav", false);
			nomphase++;
			break;
		case 2:
			engine->play2D("omnom2.wav", false);
			nomphase++;
			break;
		case 3:
			engine->play2D("omnom3.wav", false);
			nomphase++;
			break;
	}

}
void PlayNoo()
{
	noorand = rand() %80;
	//std::cout << noorand << std::endl;
	if(noorand >= 0 && noorand <=25)
	{
		noophase = 1;
	}
	else if(noorand >= 26 && noorand <=45)
	{
		noophase = 2;
	}
	else if(noorand >= 46 && noorand <=80)
	{
		noophase = 3;
	}
	switch(noophase)
	{
		case 0:
			break;
		case 1:
			engine->play2D("deathh1.wav", false);
			noophase = 0;
			break;
		case 2:
			engine->play2D("noo2.wav", false);
			noophase = 0;
			break;
		case 3:
			engine->play2D("noo3.wav", false);
			noophase = 0;
			break;
			}
			isPlayerScreamed = true;
			//engine->play2D("death1.wav", false);

}
void PlayHop()
{
	hoprand = rand() %80;
		std::cout << hoprand << std::endl;
		if(hoprand >= 0 && hoprand <=25)
		{
			hopphase = 1;
		}
		else if(hoprand >= 26 && hoprand <=45)
		{
			hopphase = 2;
		}
		else if(hoprand >= 46 && hoprand <=80)
		{
			hopphase = 3;
		}

		switch(hopphase)
		{
			case 0:
				break;
			case 1:
				engine->play2D("hop2.wav", false);
				hopphase = 0;
				break;
			case 2:
				engine->play2D("hop4.wav", false);
				hopphase = 0;
				break;
			case 3:
				engine->play2D("hop1.wav", false);
				hopphase = 0;
				break;
		}
}