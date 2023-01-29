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


    int rutax[100];
	int rutay[100];


	SDL_Texture* texture;
	const char* texturePath;



	PhysBody* pbody;


	bool die = false;
	bool stopEnem;
private:

};

#endif // __PLAYER_H__