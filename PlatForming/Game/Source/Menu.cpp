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

	FondoCreditos = app->tex->Load("Assets/Screens/Creditos.png");

	FondoOpciones = app->tex->Load("Assets/Screens/Opciones.png");

	app->audio->PlayMusic("Assets/Music/menu_music.ogg");

	//-------------------Sprites botones
	botonJugar = app->tex->Load("Assets/Textures/BotonJugar.png");
	botonCargar = app->tex->Load("Assets/Textures/BotonCargar.png");
	botonAjustes = app->tex->Load("Assets/Textures/BotonAjustes.png");
	botonCreditos = app->tex->Load("Assets/Textures/BotonCreditos.png");
	botonSalir = app->tex->Load("Assets/Textures/BotonSalir.png");
	//-------------------------

	//-------------------Sprites botones
	botonMusica = app->tex->Load("Assets/Textures/botonMusica.png");
	botonFullScream = app->tex->Load("Assets/Textures/botonFullScream.png");
	botonVSYNC = app->tex->Load("Assets/Textures/botonVSYNC.png");
	botonSINASIGNAR = app->tex->Load("Assets/Textures/botonSINASIGNAR.png");
	botonSalirAjustes = app->tex->Load("Assets/Textures/botonSalirAjustes.png");
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
		if (creditos == false && menuOpciones ==false)
		{
			//textura fondo menu 

			app->render->DrawTexture(FondoMenu, posicionMenu.x - 200, posicionMenu.y, &rect);

			//-------------------------------------botones menu
			app->render->DrawTexture(botonJugar, posicionMenu.x + 40, posicionMenu.y + 40, &rectBoton);
			app->render->DrawTexture(botonCargar, posicionMenu.x + 40, posicionMenu.y + 99, &rectBoton);
			app->render->DrawTexture(botonAjustes, posicionMenu.x + 40, posicionMenu.y + 154, &rectBoton);
			app->render->DrawTexture(botonCreditos, posicionMenu.x + 40, posicionMenu.y + 209, &rectBoton);
			app->render->DrawTexture(botonSalir, posicionMenu.x + 40, posicionMenu.y + 264, &rectBoton);
			//----------------------------------------
			//textura slime menu
			app->render->DrawTexture(SlimeMenu, posicionMenu.x, posicionMenu.y + 40 + posicionSlime, &seleccionador);


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
					menuOpciones = false;
					creditos = false;
				
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
					menuOpciones = true;
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


	if (menuOpciones) 
	{
		
		

		//eleccion menu
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && numOpciones != 0)
		{
			posicionSlimeAjustes -= 55;
			numOpciones--;
		}

		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && numOpciones != 4)
		{
			posicionSlimeAjustes += 55;
			numOpciones++;
		}


		switch (numOpciones) {

			//BOTON MUSICA
		case 0:
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				
			}
			break;

			// BOTON FULLSCREEN
		case 1:
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				activarFullscream = !activarFullscream;
			}
			break;

			// BOTON VSYNC
		case 2:
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				
			}
			break;

			// BOTON SIN ASIGNAR
		case 3:
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				
			}
			break;

			// BOTON SALIR DE AJUSTES
		case 4:
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				menuOpciones = false;
			}
			break;

		}


		app->render->DrawTexture(FondoOpciones, posicionMenu.x - 200, posicionMenu.y, &rect);

		//-------------------------------------botones menu
		app->render->DrawTexture(botonMusica, posicionMenu.x + 40, posicionMenu.y + 40, &rectBoton);
		app->render->DrawTexture(botonFullScream, posicionMenu.x + 40, posicionMenu.y + 99, &rectBoton);
		app->render->DrawTexture(botonVSYNC, posicionMenu.x + 40, posicionMenu.y + 154, &rectBoton);
		app->render->DrawTexture(botonSINASIGNAR, posicionMenu.x + 40, posicionMenu.y + 209, &rectBoton);
		app->render->DrawTexture(botonSalirAjustes, posicionMenu.x + 40, posicionMenu.y + 264, &rectBoton);
		//----------------------------------------

		app->render->DrawTexture(SlimeMenu, posicionMenu.x, posicionMenu.y + 40 + posicionSlimeAjustes, &seleccionador);

		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	    {
			menuOpciones = false;
		}

	}



	if (creditos == true)
	{
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
			creditos = false;
		}
		//textura fondo menu 
		app->render->DrawTexture(FondoCreditos, posicionMenu.x - 200, posicionMenu.y, &rect);

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

