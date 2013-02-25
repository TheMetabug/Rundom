#pragma once
#include <es_util.h>
#include <Map.h>
#include <Tile.h>
#include <Layer.h>
#include <Input.h>
#include <iostream>
#include <AnimatedSpriteGameObject.h>
class Health
{
public:
	Health(yam2d::Texture* _texture, yam2d::vec2 _position);
	Health();
	~Health();
	
	int hp;
	yam2d::AnimatedSpriteGameObject* health;
	yam2d::vec2 position;
	yam2d::Texture* texture;
	void Hit();
	void newGame();
	void Update(float deltaTime);
};
