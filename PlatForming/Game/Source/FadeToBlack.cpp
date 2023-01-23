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

#include "FadeToBlack.h"

#include "Map.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"


FadeToBlack::FadeToBlack(bool enabled) : Module(enabled)
{
	name.Create("fadetoblack");

}

// Destructor
FadeToBlack::~FadeToBlack()
{}

// Called before render is available
bool FadeToBlack::Awake()
{

	return true;
}

// Called before the first frame
bool FadeToBlack::Start()
{
	
	return true;
}

// Called each loop iteration
bool FadeToBlack::PreUpdate()
{
	

	return true;
}

// Called each loop iteration
bool FadeToBlack::Update(float dt)
{
	
	return true;
}

// Called each loop iteration
bool FadeToBlack::PostUpdate()
{
	
	return true;
}

// Called before quitting
bool FadeToBlack::CleanUp()
{
	return true;
}

