#pragma once
#include <es_util.h>
#include <Map.h>
#include <Tile.h>
#include <Layer.h>
#include <Input.h>
#include <iostream>
#include <string.h>
#include <SpriteGameObject.h>
#include <AnimatedSpriteGameObject.h>

class Danger
{
public:
	Danger(yam2d::Texture* _texture, yam2d::vec2 _position, float _speed, float _speedy,
						int _width, int _height, float _xspawn, float _yspawn, int frameCount,
						float frameRate);
	Danger();
	~Danger();

	void Update(float deltaTime);
	void Respawn();
	void Jump();

	yam2d::AnimatedSpriteGameObject* danger;
	yam2d::vec2 position;
	yam2d::Texture* texture;
	float speed;
	float speedy;
	float yspawn;
	float xspawn;
	int frameCount;
	float frameRate;
	double hitx;
	double hity;

};
