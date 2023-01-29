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

	sonido_mover = app->audio->LoadFx("Assets/Audio/Fx/pop.wav");
	sonido_clickar = app->audio->LoadFx("Assets/Audio/Fx/equip.wav");

	rect = {  0,  0,1280,720 };

	rectBoton = { 0,  0, 150,40 };

	seleccionador = { 0,  0, 32,32 };
	
	FondoMenu = app->tex->Load("Assets/Screens/Menu.png");
	SlimeMenu = app->tex->Load("Assets/Textures/SlimeMenu.png");

	FondoCreditos = app->tex->Load("Assets/Screens/Creditos.png");

	FondoOpciones = app->tex->Load("Assets/Screens/Opciones.png");

	

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
	botonFX = app->tex->Load("Assets/Textures/botonFX.png");
	botonSalirAjustes = app->tex->Load("Assets/Textures/botonSalirAjustes.png");
	//-------------------------

	//-------------------Sprites botones ON
	botonMusicaON = app->tex->Load("Assets/Textures/botonMusicaOn.png");
	botonFullScreamON = app->tex->Load("Assets/Textures/botonFullScreamOn.png");
	botonVSYNCON = app->tex->Load("Assets/Textures/botonVSYNCOn.png");
	botonFXON = app->tex->Load("Assets/Textures/botonFXOn.png");

	app->scene->player->godMod = true;	
	app->scene->enemyFy->stopEnem=true;
	
	if (musica == true)
	{
		app->audio->PlayMusic("Assets/Audio/Music/menu_music.ogg",0.0f);
	}
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
					if (fx) {

					app->audio->PlayFx(sonido_mover);
					}
			}

			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && numMenu != 4)
			{
					posicionSlime += 55;
					numMenu++;
					if (fx) {

					app->audio->PlayFx(sonido_mover);
					}
			}

		}
		

		switch (numMenu) {

			//BOTON JUGAR
			case 0:
				if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
				{
					if (fx) {

					app->audio->PlayFx(sonido_clickar);
					}
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
					if (fx) {
					app->audio->PlayFx(sonido_clickar);

					}
				}
				break;

			// BOTON AJUSTES
			case 2:
				if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
				{
					if (fx) {

					app->audio->PlayFx(sonido_clickar);
					}
					menuOpciones = true;
				}
				break;

			// BOTON IMAGEN EQUIPO
			case 3:
				if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
				{
					if (fx) {

					app->audio->PlayFx(sonido_clickar);
					}
					creditos = true;
				}
				break;

			// BOTON SALIR DEL JUEGO
			case 4:
				if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN )
				{
					if (fx) {

					app->audio->PlayFx(sonido_clickar);
					}
					salirJuego = true;
				}
				break;

		}



	}


	if (menuOpciones) 
	{
		esperarMenu--;
		if (musica == false) {
			app->audio->StopMusic(0.0f);
		}

		//eleccion menu
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && numOpciones != 0 && esperarMenu<=0)
		{
			posicionSlimeAjustes -= 55;
			numOpciones--;

			if (fx) {
			app->audio->PlayFx(sonido_mover);

			}
		}

		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && numOpciones != 4 && esperarMenu <= 0)
		{
			posicionSlimeAjustes += 55;
			numOpciones++;

			if (fx) {
			app->audio->PlayFx(sonido_mover);

			}
		}


		switch (numOpciones) {

			//BOTON MUSICA
		case 0:
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && esperarMenu <= 0)
			{
				if (fx) {
				app->audio->PlayFx(sonido_clickar);

				}
				musica = !musica;
				
			}
			break;

			// BOTON FULLSCREEN
		case 1:
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && esperarMenu <= 0)
			{
				if (fx) {
				app->audio->PlayFx(sonido_clickar);

				}
				activarFullscream = !activarFullscream;

			}
			break;

			// BOTON VSYNC
		case 2:
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && esperarMenu <= 0)
			{
				if (fx) {
				app->audio->PlayFx(sonido_clickar);

				}
				activarVsync = !activarVsync;
			}
			break;


			// BOTON QUITAR FX
		case 3:
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && esperarMenu <= 0)
			{
				fx = !fx;

				if (fx) {
				app->audio->PlayFx(sonido_clickar);
				}
			}

			break;
			// BOTON SALIR DE AJUSTES
		case 4:
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && esperarMenu <= 0)
			{
				if (fx) {

				app->audio->PlayFx(sonido_clickar);
				}
				menuOpciones = false;
				numOpciones = 0;
				posicionSlimeAjustes = 0;
				esperarMenu = 30;
			}
			break;

		}


		
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && esperarMenu <= 0)
	    {
			if (fx) {

			app->audio->PlayFx(sonido_clickar);
			}
			menuOpciones = false;
			numOpciones = 0;
			posicionSlimeAjustes = 0;
			esperarMenu = 30;

		}

		app->render->DrawTexture(FondoOpciones, posicionMenu.x - 200, posicionMenu.y, &rect);

		//-------------------------------------botones menu
		
		
		
	
		app->render->DrawTexture(botonSalirAjustes, posicionMenu.x + 40, posicionMenu.y + 264, &rectBoton);
		//----------------------------------------

		if (activarFullscream) 
		{
			app->render->DrawTexture(botonFullScreamON, posicionMenu.x + 40, posicionMenu.y + 99, &rectBoton);
		}else
			app->render->DrawTexture(botonFullScream, posicionMenu.x + 40, posicionMenu.y + 99, &rectBoton);



		if (activarVsync)
		{
			app->render->DrawTexture(botonVSYNC, posicionMenu.x + 40, posicionMenu.y + 154, &rectBoton);
		}
		else
			app->render->DrawTexture(botonVSYNCON, posicionMenu.x + 40, posicionMenu.y + 154, &rectBoton);



		if (fx)
		{
			app->render->DrawTexture(botonFXON, posicionMenu.x + 40, posicionMenu.y + 209, &rectBoton);
		}
		else
			app->render->DrawTexture(botonFX, posicionMenu.x + 40, posicionMenu.y + 209, &rectBoton);



		if (musica)
		{
			app->render->DrawTexture(botonMusicaON, posicionMenu.x + 40, posicionMenu.y + 40, &rectBoton);
		}
		else
			app->render->DrawTexture(botonMusica, posicionMenu.x + 40, posicionMenu.y + 40, &rectBoton);




		app->render->DrawTexture(SlimeMenu, posicionMenu.x, posicionMenu.y + 40 + posicionSlimeAjustes, &seleccionador);


	}

	if (activarVsync) {
		SDL_RENDERER_PRESENTVSYNC;
	}

	if (activarFullscream) {

		SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN);
	}
	else if(!activarFullscream)
	{
		SDL_SetWindowFullscreen(app->win->window, 0);
	}

	if (creditos == true)
	{
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
			creditos = false;
		}
		//textura fondo menu 
		app->render->DrawTexture(FondoCreditos, posicionMenu.x - 500, posicionMenu.y-200, &rect);

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

