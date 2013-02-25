#include "Health.h"

using namespace yam2d;


Health::Health(void)
{
}


Health::~Health(void)
{

}

Health::Health(yam2d::Texture* _texture, yam2d::vec2 _position)
{

	hp = 4;

	SpriteSheet* spriteSheet = SpriteSheet::generateSpriteSheet(_texture,200,50,0,0); 
		//_texture->setTransparentColor(0xff,0x00,0xff);
		health = new AnimatedSpriteGameObject(0, spriteSheet);
		health->setSize(200,50);
		health->setName("health");
		health->setPosition(_position);

	int numClipsPerAnimation = 1;

	float animationFrameRate = 0.0f;
	for( int i=0; i<5; ++i )
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
			health->addAnimation(i, SpriteAnimation::SpriteAnimationClip(indices,animationFrameRate, 1.0f, false));
		}
		else
		{
			health->addAnimation(i, SpriteAnimation::SpriteAnimationClip(indices,animationFrameRate, 1.0f, false));
		}
	}
	health->setPosition(_position);
	health->setActiveAnimation(3);

}

void Health::Update(float deltaTime)
{
	if (hp < 0)
	{
		hp = 0;
	}
	if (hp == -1)
	{
		health->setActiveAnimation(0);
	}

	if (hp == 0)
	{
		health->setActiveAnimation(4);
	}

	if (hp == 1)
	{
		health->setActiveAnimation(0);
	}

	if (hp == 2)
	{
		health->setActiveAnimation(1);
	}

	if (hp == 3)
	{
		health->setActiveAnimation(2);
	}

	if (hp == 4)
	{
		health->setActiveAnimation(3);
	}
}

void Health::Hit()
{
	--hp;
}

void Health::newGame()
{
	hp = 4;
}