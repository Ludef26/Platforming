#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
struct SDL_Texture;

class Scene : public Module
{
public:

	Scene(bool enabled);

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:

	Item* item;
	pugi::xml_node itemNode;
	//L02: DONE 3: Declare a Player attribute 
	Player* player;
	Enemy* enemyFy;
	Enemy* enemyFo;
	bool showPath;

	SDL_Rect tamañoParadax;
	SDL_Texture* paradax1 = NULL;

private:
	bool debugpath;
	SDL_Texture* img;
	SDL_Texture* mouseTileTex = nullptr;
	SDL_Texture* originTex = nullptr;

	// L12: Debug pathfing
	iPoint origin;
	iPoint destino;
	
	
	bool originSelected = false;
};

#endif // __SCENE_H__