#include "Enemy.h"

using namespace yam2d;
float countt = 0.0f;
Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Enemy::Enemy(yam2d::Texture* _texture, yam2d::vec2 _position)
{
	//SpriteSheet* spriteSheet = SpriteSheet::generateSpriteSheet(_texture,128,128,0,0); 
	Texture* texture(_texture); 
	enemy = new SpriteGameObject(0, texture);
	enemy->setSize(346,231);
}
void Enemy::Update(float deltaTime)
{
	countt++;
	enemy->setPosition(vec2(cos(countt/10)/2 - 9, sin(countt/10)/4.5 + 1.3));
	
}