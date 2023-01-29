#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"
#include "Scene.h"
#include "HUD.h"
#include "EntityManager.h"
#include "Physics.h"
#include "Pathfinding.h"

#include "Menu.h"

#include "Map.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"


Menu::Menu(bool enabled) : Module(enabled)
{
	name.Create("menu");

}

// Destructor
Menu::~Menu()
{}

// Called before render is available
bool Menu::Awake()
{

	return true;
}

// Called before the first frame
bool Menu::Start()
{
	
	rect = {  0,  0,1280,720 };

	rectBoton = { 0,  0, 150,40 };

	seleccionador = { 0,  0, 32,32 };
	
	FondoMenu = app->tex->Load("Assets/Screens/Menu.png");
	SlimeMenu = app->tex->Load("Assets/Textures/SlimeMenu.png");

	//-------------------Sprites botones
	botonJugar = app->tex->Load("Assets/Textures/BotonJugar.png");
	botonCargar = app->tex->Load("Assets/Textures/BotonCargar.png");
	botonAjustes = app->tex->Load("Assets/Textures/BotonAjustes.png");
	botonCreditos = app->tex->Load("Assets/Textures/BotonCreditos.png");
	botonSalir = app->tex->Load("Assets/Textures/BotonSalir.png");
	//-------------------------

	app->scene->player->godMod = true;	
	app->scene->enemyFy->stopEnem=true;
	

	
	return true;
}

// Called each loop iteration
bool Menu::PreUpdate()
{
	

	return true;
}

// Called each loop iteration
bool Menu::Update(float dt)
{
	posicionMenu.x = app->scene->player->position.x;
	posicionMenu.y = 390;

	if (abrirMenu == true)
	{
		if (creditos == false)
		{
			//textura fondo menu 

			app->render->DrawTexture(FondoMenu, posicionMenu.x - 200, posicionMenu.y, &rect);

		}
		


			//-------------------------------------botones menu
			app->render->DrawTexture(botonJugar, posicionMenu.x + 40, posicionMenu.y + 40, &rectBoton);
			app->render->DrawTexture(botonCargar, posicionMenu.x + 40, posicionMenu.y + 99, &rectBoton);
			app->render->DrawTexture(botonAjustes, posicionMenu.x + 40, posicionMenu.y + 154, &rectBoton);
			app->render->DrawTexture(botonCreditos, posicionMenu.x + 40, posicionMenu.y + 209, &rectBoton);
			app->render->DrawTexture(botonSalir, posicionMenu.x + 40, posicionMenu.y + 264, &rectBoton);
			//----------------------------------------
			//textura slime menu
			app->render->DrawTexture(SlimeMenu, posicionMenu.x, posicionMenu.y + 40 + posicionSlime, &seleccionador);

			if (creditos == false)
			{
				//eleccion menu
				if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && numMenu != 0)
				{
					posicionSlime -= 55;
					numMenu--;
				}

				if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && numMenu != 4)
				{
					posicionSlime += 55;
					numMenu++;
				}
			}
			

		
	

	switch (numMenu) {

		//BOTON JUGAR
	case 0:
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			app->scene->enemyFy->stopEnem = false;
			app->menu->Disable();
			app->scene->player->godMod = false;
			app->menu->abrirMenu = false;
		}
		break;

		// BOTON CARGAR
	case 1:
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{

		}
		break;

		// BOTON AJUSTES
	case 2:
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{

		}
		break;

		// BOTON IMAGEN EQUIPO
	case 3:
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			creditos = true;
		}
		break;

		// BOTON SALIR DEL JUEGO
	case 4:
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN )
		{
			salirJuego = true;
		}
		break;

	}



	}

	if (creditos == true)
	{
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
			creditos = false;
		}
		//textura fondo menu 
		app->render->DrawTexture(FondoMenu, posicionMenu.x - 200, posicionMenu.y, &rect);

	}

	return true;
}

// Called each loop iteration
bool Menu::PostUpdate()
{
	
	return true;
}

// Called before quitting
bool Menu::CleanUp()
{
	return true;
}

