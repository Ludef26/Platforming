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
	SDL_Texture* VidaJugador1 = NULL;
	SDL_Texture* VidaJugador2 = NULL;
	SDL_Texture* VidaJugador3 = NULL;

	SDL_Texture* HudMonedas = NULL;
	SDL_Texture* MonedasJugador = NULL;
	bool ganarMoneda=false;
	int posicionMoneda = 0;
	int cantidadMonedas = 0;
	SDL_Rect tamanoHudMonedas;

	SDL_Rect rect;
	//---------------------------------------------------------
	SDL_Rect lineaTiempo;
	bool tiempoActivo = true;
	int cantidadTiempo=2000;
	int tamañoTiempo=cantidadTiempo;
	SDL_Color colorBarra;


	SDL_Texture* Perder = NULL;
	SDL_Texture* Ganar = NULL;
	SDL_Rect rectPerder;

	//---------Sprite y posicion cura jugador
	int posicionCurax = 700;
	int posicionCuray = 600;
	SDL_Texture* curaJugador = NULL;
	SDL_Rect rectCura;
	//--------------

	int checkpointx = 800;
	int checkpointy = 657;
	SDL_Texture* texturaCheckpoint = NULL;
	SDL_Texture* texturaCheckpointCogido = NULL;
	SDL_Rect tamañoCheckpoint;


};

#endif // __SCENE_H__