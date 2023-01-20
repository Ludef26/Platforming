#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "EntityManager.h"
#include "Map.h"
#include "PathFinding.h"
#include "Physics.h"
#include "HUD.h"

#include "Defs.h"
#include "Log.h"

HUD::HUD(bool enabled) : Module(enabled)
{
	name.Create("HUD");
}

// Destructor
HUD::~HUD()
{}

// Called before render is available
bool HUD::Awake(pugi::xml_node& config)
{
	LOG("Loading HUD");
	return true;
}

// Called before the first frame
bool HUD::Start()
{
	VidaJugador1 = app->tex->Load("Assets/Textures/VidaJugador1.png");
	VidaJugador2 = app->tex->Load("Assets/Textures/VidaJugador2.png");
	VidaJugador3 = app->tex->Load("Assets/Textures/VidaJugador3.png");

	MonedasJugador = app->tex->Load("Assets/Textures/goldSlime.png");
	HudMonedas = app->tex->Load("Assets/Textures/HudMonedas.png");

	Perder = app->tex->Load("Assets/Screens/Dying_scene.png");
	Ganar = app->tex->Load("Assets/Screens/Win_scene.png");
	return true;
}

// Called each loop iteration
bool HUD::PreUpdate()
{
	
	return true;
}

// Called each loop iteration
bool HUD::Update(float dt)
{
	
    tamanoHudMonedas = { 0, 0, 133,47 };
	rectPerder = { 0, 0, 1280,720 };



	//-------------------------------------------------------HUD MONEDAS
	if (app->scene->player->win == false || app->scene->player->vidas > 0)
	{
		app->render->DrawTexture(HudMonedas, app->scene->player->position.x - 200, 390, &tamanoHudMonedas);
	}

	switch (cantidadMonedas) {
	case 0:

		break;

	case 1:
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 188, 394, &rect);
		break;

	case 2:
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 188, 394, &rect);
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 169, 394, &rect);
		break;

	case 3:
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 188, 394, &rect);
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 169, 394, &rect);
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 150, 394, &rect);

		break;

	case 4:
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 188, 394, &rect);
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 169, 394, &rect);
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 150, 394, &rect);
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 131, 394, &rect);
		break;

	case 5:
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 188, 394, &rect);
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 169, 394, &rect);
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 150, 394, &rect);
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 131, 394, &rect);
		app->render->DrawTexture(MonedasJugador, app->scene->player->position.x - 112, 394, &rect);
		break;
	}
	// -----------------------------------------------------Vida Jugador
	rect = { 0, 0, 32,32 };
	if (app->scene->player->vidas == 3) {
	app->render->DrawTexture(VidaJugador1, app->scene->player->position.x+28, app->scene->player->position.y - 20, &rect);
	app->render->DrawTexture(VidaJugador2, app->scene->player->position.x, app->scene->player->position.y - 20, &rect);
	app->render->DrawTexture(VidaJugador3, app->scene->player->position.x - 28, app->scene->player->position.y - 20, &rect);

	}

	else if (app->scene->player->vidas == 2) {
	app->render->DrawTexture(VidaJugador1, app->scene->player->position.x, app->scene->player->position.y - 20, &rect);
	app->render->DrawTexture(VidaJugador2, app->scene->player->position.x - 28, app->scene->player->position.y - 20, &rect);
	
	}

	else if (app->scene->player->vidas == 1) {
		
	app->render->DrawTexture(VidaJugador1, app->scene->player->position.x - 28, app->scene->player->position.y - 20, &rect);

	}

	// pantalla de perder
	else
	app->render->DrawTexture(Perder, app->scene->player->position.x - 530, 210, &rectPerder);

	//pantalla de ganar
	if (app->scene->player->win == true) 
	{
		app->render->DrawTexture(Ganar, app->scene->player->position.x - 530, 210, &rectPerder);
	}

	

	
	return true;
}

// Called each loop iteration
bool HUD::PostUpdate()
{

	return true;
}

// Called before quitting
bool HUD::CleanUp()
{
	LOG("Freeing HUD");
	
	return true;
}
