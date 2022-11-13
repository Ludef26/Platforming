#ifndef __LOSE_H__
#define __LOSE_H__

#include "Module.h"

#include "Point.h"

#include "SDL/include/SDL.h"

class Lose : public Module
{
public:

	Lose();

	// Destructor
	virtual ~Lose();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();
};

