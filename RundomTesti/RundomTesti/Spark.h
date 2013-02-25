#pragma once
#include <es_util.h>
#include <Map.h>
#include <Tile.h>
#include <Layer.h>
#include <Input.h>
#include <iostream>
#include <AnimatedSpriteGameObject.h>
class Spark
{
public:
	Spark(yam2d::Texture* _texture, yam2d::vec2 _position);
	Spark();
	~Spark();
	
	yam2d::AnimatedSpriteGameObject* spark;
	yam2d::vec2 position;
	yam2d::Texture* texture;
	void Hit();
	void Update(float deltaTime);
};

