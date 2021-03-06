#ifndef SCORE // Include guard
#define SCORE

#include <SpriteBatch.h>
#include <SpriteSheet.h>
#include <Text.h>
#include <Texture.h>
#include <TextGameObject.h>
#include <iostream>
#include <vector>
#include <string>
#include "Health.h"

class Score
{
public:

	Score(
		const char* fontTextureFileName, 
		const char* fontDatFileName,
		Health *health);
	
	~Score(void);

	void update( float deltaTime);

	void render(float posX, float posY);

	Health* health;

	double highscore;

	std::string letters;
	int lindex;

	std::vector <yam2d::Ref<yam2d::Text>> scoreTexts;
	std::vector <yam2d::Ref<yam2d::TextGameObject>> scoreTextObjects;

	// Text objects
	yam2d::Ref<yam2d::Text> m_totalTimeText;
	yam2d::Ref<yam2d::Text> m_fpsText;
	yam2d::Ref<yam2d::Text> m_scoreText1;
	yam2d::Ref<yam2d::Text> m_scoreText2;
	yam2d::Ref<yam2d::Text> m_scoreText3;
	yam2d::Ref<yam2d::Text> m_scoreText4;
	yam2d::Ref<yam2d::Text> m_scoreText5;
	yam2d::Ref<yam2d::Text> m_nameText1;
	yam2d::Ref<yam2d::Text> m_nameText2;
	yam2d::Ref<yam2d::Text> m_nameText3;



	yam2d::Ref<yam2d::TextGameObject> totalTimeText;
	yam2d::Ref<yam2d::TextGameObject> fpsText;
	yam2d::Ref<yam2d::TextGameObject> scoreText1;
	yam2d::Ref<yam2d::TextGameObject> scoreText2;
	yam2d::Ref<yam2d::TextGameObject> scoreText3;
	yam2d::Ref<yam2d::TextGameObject> scoreText4;
	yam2d::Ref<yam2d::TextGameObject> scoreText5;
	yam2d::Ref<yam2d::TextGameObject> nameText1;
	yam2d::Ref<yam2d::TextGameObject> nameText2;
	yam2d::Ref<yam2d::TextGameObject> nameText3;


	// Create new sprite batch group. This must be deleted at deinit.
	yam2d::Ref<yam2d::SpriteBatchGroup>	m_batch;

	// Texture to be used when rendering text
	yam2d::Texture* m_fontTexture;

	// Font is series of clipping regions (SpriteSheet), which specifies font and character set.
	yam2d::SpriteSheet* m_font;

	// T�h�n lasketaan kokonaisaikaa
	float m_totalTime; // Kokonaisaika
	int m_frameCount;  // Framen numero

	float m_fps;		// FPS
	float m_frameRateCounter; // Ajastin, joka laskee, milloin viimeksi on m_fps-muutttuja p�ivitetty
	int m_frameRateFrameCounter; // VAstaava, kuin yll�, mutta laskee framejen lukum��r��

	void strawberry();
	void banaani();
	void omena();

};


#endif



