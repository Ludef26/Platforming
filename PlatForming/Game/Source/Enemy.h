#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Item.h"


struct SDL_Texture;

class Enemy : public Entity
{
public:

	Enemy();
	
	virtual ~Enemy();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

public:
	Item* item;

    int rutax[100];
	int rutay[100];
	iPoint ir;

	SDL_Texture* texture;
	const char* texturePath;
	const char* lastSprite;

	PhysBody* pbody2;
	PhysBody* pbody;

	int pickCoinFxId;


	bool onFloor = false;
	int jumpTime = 600;
	bool jump = false;

	bool die = false;

};

#endif // __PLAYER_H__