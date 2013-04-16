#pragma once
#include <es_util.h>
#include <Map.h>
#include <Tile.h>
#include <Layer.h>
#include <Input.h>
#include <iostream>
#include <string.h>
#include <SpriteGameObject.h>
class Particles
{
public:
	Particles(yam2d::Texture* _texture, yam2d::vec2 _position, double _speed, double scale, double rotation);
	Particles();
	~Particles();

	yam2d::SpriteGameObject* background;
	yam2d::vec2 position;
	yam2d::Texture* texture;

	double speed;
	double scale;
	double rotation;

	void Update(float deltaTime);
};

