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

Danger::Danger(yam2d::Texture* _texture, yam2d::vec2 _position, float _speed, float _speedy,
						int _width, int _height, float _xspawn, float _yspawn)
{
	Texture* texture(_texture);
	texture->setTransparentColor(255,255,255);
	danger = new SpriteGameObject(0, texture);
	danger->setPosition(_position);
	danger->setSize(50,50);
	speed = _speed;
	speedy = _speedy;
	yspawn = _yspawn;
	xspawn = _xspawn;
	hitx = 0;
	hity = 0;
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