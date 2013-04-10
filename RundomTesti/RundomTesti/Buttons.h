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

class Buttons
{
public:
	Buttons(yam2d::Texture* _texture, yam2d::vec2 _position, int _number);
	Buttons();
	~Buttons();

	int Update(float deltaTime);
	int ReturnNumber();

	int number;
	yam2d::AnimatedSpriteGameObject* buttons;
	yam2d::vec2 position;
	yam2d::Texture* texture;
};