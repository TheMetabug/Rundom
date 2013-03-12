#include "BackGround.h"

using namespace yam2d;

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}


BackGround::BackGround(yam2d::Texture* _texture, yam2d::vec2 _position, double _speed,
						int _width, int _height, float _yspawn)
{
	/*background1 =  new SpriteGameObject::SpriteGameObject(_texture, 1281.0f, 335.0f);
	background1->setPosition(vec2(0,-3.5f));*/
	Texture* texture(_texture); 
	background = new SpriteGameObject(0, texture);
	background->setSize(_width,_height);
	background->setName("skybg1");
	background->setPosition(_position);
	speed = _speed;
	yspawn = _yspawn;
	boost = 0;
	_texture->setTransparentColor(0xff,0x00,0xff);
}

void BackGround::Update(float deltaTime)
{
	boost += 0.02f;
	if (boost >= 10)
	{
		std::cout << boost << std::endl;
		boost = 10;
	}
	background->setPosition(background->getPosition()-vec2((speed + boost)*deltaTime,0.0f));
	if (background->getPosition().x <= -20)
	{
		background->setPosition(vec2(background->getPosition().x + 40,yspawn));
	}

}

