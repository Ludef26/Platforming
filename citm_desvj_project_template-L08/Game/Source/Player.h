#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Item.h"

struct SDL_Texture;

class Player : public Entity
{
public:

	Player();
	
	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
	void OnCollision(PhysBody* physA, PhysBody* physB);




public:
	Item* item;

	//L02: DONE 1: Declare player parameters
	SDL_Texture* texture;
	const char* texturePath;
	const char* lastSprite;

	// L07 DONE 5: Add physics to the player - declare a Physics body
	PhysBody* pbody;

	int pickCoinFxId;

	float limMap=2.0f;
	
	bool onFloor = false;
	int jumpTime=600;
	bool jump = false;

};

#endif // __PLAYER_H__