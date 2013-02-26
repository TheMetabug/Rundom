#include "Danger.h"
using namespace yam2d;

float hyppyvoimaD = 0;
double countd = 0;

Danger::Danger()
{
}


Danger::~Danger()
{
}

Danger::Danger(Texture* _texture, vec2 _position, float _speed, float _speedy,
						int _width, int _height, float _xspawn, float _yspawn, int _frameCount,
						float _frameRate)
{
	SpriteSheet* spriteSheet = SpriteSheet::generateSpriteSheet(_texture,_width,_height,0,0); 
	Texture* texture(_texture);
	texture->setTransparentColor(255,255,255);
	danger = new AnimatedSpriteGameObject(0, spriteSheet);
	danger->setPosition(_position);
	danger->setSize(_width,_height);
	speed = _speed;
	speedy = _speedy;
	yspawn = _yspawn;
	xspawn = _xspawn;
	frameRate = _frameRate;
	frameCount = _frameCount;
	hitx = 0;
	hity = 0;

	int numClipsPerAnimation = _frameCount;

	float animationFrameRate = _frameRate;
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
			danger->addAnimation(i, SpriteAnimation::SpriteAnimationClip(indices,animationFrameRate, 1.0f, true));
		}
		else
		{
			danger->addAnimation(i, SpriteAnimation::SpriteAnimationClip(indices,animationFrameRate, 1.0f, false));
		}
	}
	danger->setPosition(_position);
	danger->setActiveAnimation(0);

}
void Danger::Update(float deltaTime)
{

	countd += deltaTime;

	if (speedy != 0)
	{
		danger->setPosition(vec2(danger->getPosition().x - speed*deltaTime, yspawn - sin(countd)/0.7f));
	}
	else
	{
	danger->setPosition(danger->getPosition()-vec2(speed*deltaTime,0));
	}
	if (danger->getPosition().x <= -15)
	{
		Respawn();
	}
	hitx = danger->getPosition().x;
	hity = danger->getPosition().y  - 0.7f;
}

void Danger::Respawn()
{
	//countd = 0;
	danger->setPosition(vec2(xspawn + rand() %50,yspawn));
}

void Danger::Jump()
{
	if (danger->getPosition().y >= 2.5f)
		{
			hyppyvoimaD = 0.6f;
		}
		//std::cout << "Hyppy" << std::endl;
	
	
		if (hyppyvoimaD > 0)
		{
			//std::cout << "Wat" << std::endl;
			danger->setRotation(countd/2.5f);
			danger->setPosition(danger->getPosition() - vec2(0.0f,hyppyvoimaD/2));
		}
			
		if (hyppyvoimaD < 0 )
		{
			danger->setRotation(countd/2.5f);
			danger->setPosition(danger->getPosition() - vec2(0.0f,hyppyvoimaD/4));

			/*if (player->getPosition().y = */
		}
}