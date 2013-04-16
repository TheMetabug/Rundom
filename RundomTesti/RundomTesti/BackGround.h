#pragma once
#include <es_util.h>
#include <Map.h>
#include <Tile.h>
#include <Layer.h>
//#include <iostream>
#include <string.h>
#include <SpriteGameObject.h>
class BackGround
{
public:
	BackGround(yam2d::Texture* _texture, yam2d::vec2 _position, double _speed, double _speedmax,
				int _width, int _height, float _yspawn);
	BackGround();
	~BackGround();

	yam2d::SpriteGameObject* background;
	yam2d::vec2 position;
	yam2d::Texture* texture;
	double speed;
	double speedmax;
	float yspawn;
	float boost;

	void Slow();

	void Update(float deltaTime);
};

