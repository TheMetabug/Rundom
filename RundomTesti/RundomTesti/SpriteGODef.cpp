//#include "SpriteGODef.h"
//
//SpriteGODef::SpriteGODef(void)
//{
//	
//}
//
//SpriteGameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, bool isWhiteTransparentColor = false)
//{
//	//Load texture to be used as texture for sprite.
//	Texture* texture = new Texture(bitmapFileName.c_str());
//
//	// If user wants to create texture which white colors is treated as atransparent color.
//	if( isWhiteTransparentColor )
//	{
//		// Set white to transparent. Here color values are from 0 to 255 (RGB)
//		texture->setTransparentColor(255,255,255);
//	}
//
//	// Create new sprite GameObject from texture.
//	SpriteGameObject* gameObject = new SpriteGameObject(0,texture);
//
//	// Resize the sprite to be correct size
//	gameObject->setSize(sizeX, sizeY);
//
//	return gameObject;
//
//}
//
//
//
//SpriteGameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, int clipStartX, int clipStartY, int clipSizeX, int clipSizeY, bool isWhiteTransparentColor = false )
//{
//	// Load texture to be used as texture for sprite.
//	Texture* texture = new Texture(bitmapFileName.c_str());
//	
//	// If user wants to create texture which white coros is treated as atransparent color.
//	if( isWhiteTransparentColor )
//	{
//		// Set white to transparent. Here color values are from 0 to 255 (RGB)
//		texture->setTransparentColor(255,255,255);
//	}
//
//	// Create new sprite GameObject from texture.
//	SpriteGameObject* gameObject = new SpriteGameObject(0,texture);
//
//	// Resize the sprite to be correct size
//	gameObject->setSize(sizeX, sizeY);
//
//	// Specify clip area by start point and size in pixels
//	Sprite::PixelClip clip;
//	clip.topLeft.x = clipStartX;
//	clip.topLeft.y = clipStartY;
//	clip.clipSize.x = clipSizeX;
//	clip.clipSize.y = clipSizeY;
//
//	// Set pixel clip for sprite
//	gameObject->getSprite()->setClip(float(texture->getWidth()), float(texture->getHeight()), clip );
//
//	return gameObject;
//}
//
//
//
//SpriteGODef::~SpriteGODef(void)
//{
//}
