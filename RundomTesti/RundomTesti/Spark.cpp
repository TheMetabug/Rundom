#include "Spark.h"

using namespace yam2d;

Spark::Spark(void)
{
}


Spark::~Spark(void)
{
}

Spark::Spark(yam2d::Texture* _texture, yam2d::vec2 _position)
{
	SpriteSheet* spriteSheet = SpriteSheet::generateSpriteSheet(_texture,80,80,0,0); 
		//_texture->setTransparentColor(0xff,0x00,0xff);
		spark = new AnimatedSpriteGameObject(0, spriteSheet);
		spark->setSize(80,80);
		spark->setName("spark");
		spark->setPosition(_position);

	int numClipsPerAnimation = 6;

	float animationFrameRate = 30.0f;
	for( int i=0; i<4; ++i )
	{
		std::vector<int> indices;
		indices.resize(numClipsPerAnimation);
		for( size_t j=0; j<indices.size(); ++j )
		{
			indices[j] = numClipsPerAnimation*i + j;
		}

		// Add looping animation.
		if(i <2)
		{
			spark->addAnimation(i, SpriteAnimation::SpriteAnimationClip(indices,animationFrameRate, 1.0f, false));
		}
		else
		{
			spark->addAnimation(i, SpriteAnimation::SpriteAnimationClip(indices,animationFrameRate, 1.0f, false));
		}
	}
	spark->setPosition(_position);
	spark->setActiveAnimation(0);
}

void Spark::Update(float deltaTime)
{

}

void Spark::Hit()
{
	spark->setActiveAnimation(0);
}