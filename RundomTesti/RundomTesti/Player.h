#pragma once
#include <es_util.h>
#include <Map.h>
#include <Tile.h>
#include <Layer.h>
#include <Input.h>
#include <iostream>
#include <AnimatedSpriteGameObject.h>
#include "Health.h"
class Player
{
public:
	Player(yam2d::Texture* _texture, yam2d::vec2 _position, Health *health);
	Player();
	~Player();
	
	yam2d::AnimatedSpriteGameObject* player;
	yam2d::vec2 position;
	yam2d::Texture* texture;
	
	Health* health;

	int die;
	void Update(float deltaTime);
	double hitx;
	double hity;
	void DangerHit();
	void Death();
	float boost;
};

