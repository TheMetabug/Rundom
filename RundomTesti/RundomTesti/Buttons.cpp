#include "Buttons.h"

using namespace yam2d;

Buttons::Buttons(void)
{
}


Buttons::~Buttons(void)
{
}

Buttons::Buttons(Texture* _texture, vec2 _position, int _number)
{
	number = _number;
	SpriteSheet* spriteSheet = SpriteSheet::generateSpriteSheet(_texture,_texture->getWidth(),
		_texture->getHeight()/3,0,0); 
	texture = _texture;
	texture->setTransparentColor(255,255,255);
	buttons = new AnimatedSpriteGameObject(0, spriteSheet);
	buttons->setPosition(_position);
	buttons->setSize(_texture->getWidth(),_texture->getHeight()/3);

	int numClipsPerAnimation = 1;

	float animationFrameRate = 0;
	for( int i=0; i<3; ++i )
	{
		std::vector<int> indices;
		indices.resize(numClipsPerAnimation);
		for( size_t j=0; j<indices.size(); ++j )
		{
			indices[j] = numClipsPerAnimation*i + j;
		}

		// Add looping animation.
		if(i <3)
		{
			buttons->addAnimation(i, SpriteAnimation::SpriteAnimationClip(indices,animationFrameRate, 1.0f, false));
		}
	}

}

int Buttons::Update(float deltaTime)
{
	
	if (getMouseAxisX() - 640 >= buttons->getPosition().x * 64 - texture->getWidth()/2 &&
		getMouseAxisX() - 640 <= buttons->getPosition().x * 64 + texture->getWidth()/2 && 
		getMouseAxisY() - 360 >= buttons->getPosition().y * 64 - texture->getHeight()/6 &&
		getMouseAxisY() - 360 <= buttons->getPosition().y * 64 + texture->getHeight()/6) 
	{
		buttons->setActiveAnimation(1);
		std::cout << getMouseAxisX() << std::endl;
		if(getMouseButtonState(MouseButtons::MOUSE_LEFT))
		{
			buttons->setActiveAnimation(2);
			return number;
		}
	}
	else
	{
		buttons->setActiveAnimation(0);
	}
}

int Buttons::ReturnNumber()
{
	return 0;
}