#include "Score.h"
#include <sstream>
template <class T>
std::string to_string(T t)
{
        std::stringstream s;
        s << t;
        return s.str();
}

using namespace yam2d;

Score::Score(
	const char* fontTextureFileName, 
	const char* fontDatFileName,
	Health *health)
{
	// Create new sprite batch group. This must be deleted at deinit.
	m_batch = new SpriteBatchGroup();

	// Load font texture. Made with font creation tool like bitmap font builder.
	m_fontTexture = new Texture(fontTextureFileName);

	this->health = health;

	// Create font clip areas (sprite sheet), from dat file and texture. Dat-file is made with bitmap font builder.
	m_font = SpriteSheet::autoFindFontFromTexture(m_fontTexture,fontDatFileName);

	// Create new texts using font
	m_totalTimeText		= new Text(m_font);
	m_fpsText			= new Text(m_font);

	for (int i = 0; i < 5; i++)
	{
		scoreTexts.push_back(new Text(m_font));
	}

	totalTimeText		= new TextGameObject(0,m_totalTimeText);
	fpsText				= new TextGameObject(0,m_fpsText);

	for (int i = 0; i < 5; i++)
	{
		scoreTextObjects.push_back(new TextGameObject(0,scoreTexts[i]));
	}



	// Set total time to 0
	m_totalTime = 0.0f;
	m_frameCount = 0;

	highscore = 0.0f;

	m_fps = 0.0f;
	m_frameRateCounter = 0.0f;
	m_frameRateFrameCounter = 0;
}


Score::~Score(void)
{
}

void Score::update(float deltaTime)
{
	

	// Increase total time
	if (health->hp != 0)
	{
		m_totalTime += deltaTime;
	}

	m_frameRateCounter += deltaTime;

	if( m_frameRateCounter > .2f )
	{
		m_fps = float(m_frameRateFrameCounter) / m_frameRateCounter;

		//std::cout << m_fps << std::endl;

		m_fpsText->setText(	"FPS: "	+ to_string(floor(m_fps)) );
		// Nollaa laskurit
		m_frameRateCounter = 0.0f;
		m_frameRateFrameCounter = 0;

		// Nollaa sprite batchin laskurit
		SpriteBatch::resetStatsValues();
	}

	highscore = ceil(m_totalTime*100);

	// Set text.
	m_totalTimeText->setText( "Score : " + to_string(highscore) );

	
}

void Score::render(float posX, float posY)
{
	// Kasvata frame counttia
	++m_frameCount;
	++m_frameRateFrameCounter;

	// Clear sprite before add new dynamic sprites.
	m_batch->clear();

	// Add text to position posX + textwidth*0.5, posX
	//m_batch->addText(m_fontTexture, m_totalTimeText, vec2((float)int(0.5f*m_totalTimeText->getWidth()+posX+0.5f),				posY),			0);
	//m_batch->addText(m_fontTexture, m_fpsText, vec2((float)int(0.5f*m_fpsText->getWidth()+posX+0.5f),					posY-60.0f),	0);
	//
	// Render
	m_batch->render();
}