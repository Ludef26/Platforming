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
	VidaJugador = app->tex->Load("Assets/Textures/VidaJugador.png");

	Perder = app->tex->Load("Assets/Scene/Dying_Scene.png");
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
	// -----------------------------------------------------Vida Jugador
	rect = { 0, 0, 24,24 };

	if (app->scene->player->vidas == 3) {
	app->render->DrawTexture(VidaJugador, app->scene->player->position.x+24, app->scene->player->position.y - 30, &rect);
	app->render->DrawTexture(VidaJugador, app->scene->player->position.x, app->scene->player->position.y - 30, &rect);
	app->render->DrawTexture(VidaJugador, app->scene->player->position.x - 24, app->scene->player->position.y - 30, &rect);

	}

	else if (app->scene->player->vidas == 2) {
	app->render->DrawTexture(VidaJugador, app->scene->player->position.x, app->scene->player->position.y - 30, &rect);
	app->render->DrawTexture(VidaJugador, app->scene->player->position.x - 24, app->scene->player->position.y - 30, &rect);
	
	}

	else if (app->scene->player->vidas == 1) {
		
	app->render->DrawTexture(VidaJugador, app->scene->player->position.x - 24, app->scene->player->position.y - 30, &rect);

	}

	else
	app->render->DrawTexture(VidaJugador, 0, 0 , &rectPerder);

	//-------------------------------------------------------
	
	
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
