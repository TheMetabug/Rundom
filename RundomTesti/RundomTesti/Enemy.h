#pragma once
#include <es_util.h>
#include <Map.h>
#include <Tile.h>
#include <Layer.h>
#include <Input.h>
#include <iostream>
#include <string.h>
#include <SpriteGameObject.h>
class Enemy
{
public:
	Enemy(yam2d::Texture* _texture, yam2d::vec2 _position);
	Enemy();
	~Enemy();

	yam2d::SpriteGameObject* enemy;
	yam2d::vec2 position;
	yam2d::Texture* texture;
	
	void Update(float deltaTime);
};

