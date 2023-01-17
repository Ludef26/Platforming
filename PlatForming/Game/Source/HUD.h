#ifndef __HUD_H__
#define __HUD_H__

#include "Module.h"
#include "Player.h"

struct SDL_Texture;

class HUD : public Module
{
public:

	HUD(bool enabled);

	// Destructor
	virtual ~HUD();

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
	//---------------------Para textura de perder
	SDL_Texture* VidaJugador = NULL;
	SDL_Rect rect;
	//---------------------------------------------------------

	SDL_Texture* Perder = NULL;
	SDL_Rect rectPerder;
};

#endif // __SCENE_H__