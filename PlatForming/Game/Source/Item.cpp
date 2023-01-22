#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"

Item::Item() : Entity(EntityType::ITEM)
{
	name.Create("item");
}

Item::~Item() {}

bool Item::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	isPicked = parameters.attribute("picked").as_bool();
	idItem = parameters.attribute("idItem").as_int();
	return true;
}

bool Item::Start() {

	//initilize textures
	if (isPicked == false) {
		texture = app->tex->Load(texturePath);
		// L07 DONE 4: Add a physics to an item - initialize the physics body

		pbody = app->physics->CreateRectangleSensor(position.x + 16, position.y + 16, 10, 16, bodyType::STATIC);
		pbody->ctype = ColliderType::ITEM;

		
	}

	return true;
}

bool Item::Update()
{
	

	switch (idItem) {
	case 1:
		if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
		parameters.append_attribute("picked") = true;
		}
		break;

	case 2:
		if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			parameters.append_attribute("picked") = true;
		}
		break;

	case 3:
		parameters.append_attribute("picked") = true;
		break;

	case 4:
		parameters.append_attribute("picked") = true;
		break;

	case 5:
		parameters.append_attribute("picked") = true;
		break;

	}
	

	

	if (isPicked == false)
	{
		// L07 DONE 4: Add a physics to an item - update the position of the object from the physics.  
		position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
		position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

		app->render->DrawTexture(texture, position.x, position.y);
	}
	return true;
}

bool Item::CleanUp()
{
	return true;
}