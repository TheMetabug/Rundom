#include "Player.h"
#include "Health.h"
using namespace yam2d;

float count = 0.0f;
float hyppyvoima = 0;
float kipuvoima = 0;
bool isHeJumping = false;
bool isHeDead = false;

Player::Player()
{
}

Player::~Player()
{
}
Player::Player(Texture* _texture, vec2 _position, Health *health)
{
		SpriteSheet* spriteSheet = SpriteSheet::generateSpriteSheet(_texture,128,128,0,0); 
		//_texture->setTransparentColor(0xff,0x00,0xff);
		player = new AnimatedSpriteGameObject(0, spriteSheet);
		player->setSize(128,128);
		player->setName("player_run");
		player->setPosition(_position);

		this->health = health;

	int numClipsPerAnimation = 8;
	boost = 0;
	float animationFrameRate = 10.0f;
	for( int i=0; i<4; ++i )
	{
		std::vector<int> indices;
		indices.resize(numClipsPerAnimation);
		for( size_t j=0; j<indices.size(); ++j )
		{
			indices[j] = numClipsPerAnimation*i + j;
		}

		// Add looping animation.
		if(i <2)
		{
			player->addAnimation(i, SpriteAnimation::SpriteAnimationClip(indices,animationFrameRate, 1.0f, true));
		}
		else
		{
			player->addAnimation(i, SpriteAnimation::SpriteAnimationClip(indices,animationFrameRate, 1.0f, false));
		}

	}
	player->setPosition(_position);
	player->setActiveAnimation(0);

	hitx = 0;
	hity = 0;
	die = 0;



}
void Player::Update(float deltaTime)
{
	count++;
	hyppyvoima -= 0.05f;
	//player->getActiveAnimation();

	if (die == 0)
	{
		isHeJumping = false;
		isHeDead = false;

		if (player->getPosition().y >= 2.5f)
		{
			hyppyvoima = 0;
			player->setRotation(0);
			player->setPosition(vec2(player->getPosition().x,2.5f));
		}
	}

	if(getKeyState(KeyCodes::KEY_LEFT))
	{
		player->setPosition(player->getPosition()-vec2(0.1f,0.0f));

	}
	if(getKeyState(KeyCodes::KEY_RIGHT))
	{
		player->setPosition(player->getPosition()+vec2(0.1f,0.0f));
	}


	//Jump with space
	if(getKeyState(KeyCodes::KEY_SPACE) && kipuvoima == 0 && die == 0)
	{
		if (player->getPosition().y >= 2.5f)
		{
			hyppyvoima = 0.6f;
			isHeJumping = true;
		}
	}
	
		if (hyppyvoima > 0)
		{
			player->setRotation(count/2.5f);
			player->setPosition(player->getPosition() - vec2(0.0f,hyppyvoima/2));
		}
			
		if (hyppyvoima < 0 )
		{
			player->setRotation(count/2.5f);
			player->setPosition(player->getPosition() - vec2(0.0f,hyppyvoima/4));
		}
	
		if (kipuvoima > 0)
		{
			player->setRotation(-count/2);
			player->setPosition(player->getPosition() - vec2(kipuvoima,kipuvoima/2));
			kipuvoima -= 0.05f;
		}
			
		if (kipuvoima < 0 )
		{
			player->setRotation(-count/2);
			player->setPosition(player->getPosition() - vec2(-kipuvoima,kipuvoima/4));
			kipuvoima -= 0.05f;

			if (player->getPosition().y >= 2.5f)
				{
					kipuvoima = 0;
				}

		}

	hitx = player->getPosition().x;
	//std::cout << hitx << std::endl;
	hity = player->getPosition().y;
	//std::cout << hity << std::endl;
	//std::cout << kipuvoima << std::endl;


	//player respawn
	if (player->getPosition().y >= 40.5f)
		{
			player->setRotation(0);
			//player->setPosition(vec2(0,-4.5f));
			die = 0;
			health->hp = 4;
		}

	//player dies
	if (health->hp == 0)
	{
		isHeDead = true;
		die = 1;
	}

	//player runs faster

	boost += 0.01f;
	if (boost >= 20)
	{
		boost = 20;
	}

	player->getAnimation(0).animationFPS = 10.0f + (int)boost;

	std::cout << boost << " " << player->getAnimation(0).animationFPS << std::endl;
}

void Player::DangerHit()
{
		hyppyvoima = 0;
		kipuvoima = 0.6f;
		health->hp -= 1;
}

void Player::Death()
{
		die = 1;
		isHeDead = true;
}

void Player::Slow()
{
	boost = boost/2;
}