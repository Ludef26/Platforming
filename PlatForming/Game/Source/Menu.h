#ifndef __MENU_H__
#define __MENU_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Window;
struct SDL_Surface;

class Menu : public Module
{
public:
	Menu(bool enabled);

	virtual ~Menu();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

public:
	uint sonido_mover;
	uint sonido_clickar;

	SDL_Texture* FondoOpciones = NULL;
	bool menuOpciones = false;
	int numOpciones = 0;
	int posicionSlimeAjustes = 0;
	int esperarMenu = 30;

	SDL_Texture* FondoMenu = NULL;
	SDL_Texture* FondoCreditos = NULL;
	SDL_Texture* SlimeMenu = NULL;
	SDL_Rect rect;
	SDL_Rect rectBoton;
	SDL_Rect seleccionador;

	SDL_Rect posicionMenu;
	int numMenu = 0;
	
	//botones menu
	SDL_Texture* botonJugar = NULL;
	SDL_Texture* botonCargar = NULL;
	SDL_Texture* botonAjustes = NULL;
	SDL_Texture* botonCreditos = NULL;
	SDL_Texture* botonSalir = NULL;


	//botones opciones
	SDL_Texture* botonMusica = NULL;
	SDL_Texture* botonFullScream = NULL;
	SDL_Texture* botonVSYNC = NULL;
	SDL_Texture* botonFX = NULL;
	SDL_Texture* botonSalirAjustes = NULL;


	SDL_Texture* botonMusicaON = NULL;
	SDL_Texture* botonFullScreamON = NULL;
	SDL_Texture* botonVSYNCON = NULL;
	SDL_Texture* botonFXON = NULL;


	int posicionSlime = 0;

	bool abrirMenu = true;
	bool salirJuego = false;
	bool creditos = false;

	bool activarFullscream=false;
	bool activarVsync = true;
	bool musica = true;
	bool fx = true;

};

#endif