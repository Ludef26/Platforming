#ifndef __MENU_H__
#define __MENU_H__

#include "Module.h"
#include "Animation.h"


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
	SDL_Texture* FondoMenu = NULL;
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

	int posicionSlime = 0;

	bool abrirMenu = true;
	bool salirJuego = false;
};

#endif