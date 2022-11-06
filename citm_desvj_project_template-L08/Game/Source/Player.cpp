#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Item.h"
#include "Map.h"
#include "EntityManager.h"
#include "Window.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
}

Player::~Player() {

}

bool Player::Awake() {

	//L02: DONE 1: Initialize Player parameters
	//pos = position;
	//texturePath = "Assets/Textures/player/idle1.png";

	//L02: DONE 5: Get Player parameters from XML
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("p.Idle").as_string();

	return true;
}

bool Player::Start() {


	// L07 DONE 5: Add physics to the player - initialize physics body
	
	pbody = app->physics->CreateRectangle(position.x+16, position.y+16, 16,23, bodyType::DYNAMIC);
	pbody->body->SetFixedRotation(true); // Asi no rota la hit box del jugador

	// L07 DONE 6: Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method
	pbody->listener = this; 

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::PLAYER;

	//initialize audio effect - !! Path is hardcoded, should be loaded from config.xml
	pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");

	return true;
}

bool Player::Update()
{
	b2Vec2 vel = pbody->body->GetLinearVelocity();

	int speed = 5; 

	texture = app->tex->Load(texturePath);
	
	// L07 DONE 5: Add physics to the player - updated player position using physics
	
	//L02: DONE 4: modify the position of the player using arrow keys and render the texture
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && onFloor ==true) {
		//
		onFloor = false;
		jump = true;
		LOG("Jump");
		//Sprite de salto
		texturePath = parameters.attribute("p.Jump").as_string();

		for (jumpTime; jumpTime >= 0;jumpTime--) {

		vel.y = b2Max(-10 - 0.1f, -5.0f);

		}
		if (jumpTime <= 0) {
		jump = false;
		jumpTime = 600;

		}

	}
	else if (onFloor==true) 
	{
	//Sprite de Idle
	texturePath = parameters.attribute("p.Idle").as_string();
	}

	//-------------------------GRAVEDAD CUANDO NO SALTAS
	if (onFloor == false && jumpTime <= 0)
	{
		vel.y = b2Min(speed + 0.1f, 5.0f);
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{
		//
	}
		
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT ) 
	{
		
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && onFloor==false ) 
		{
			texturePath = parameters.attribute("p.JumpL").as_string();
		}
		else
		texturePath = parameters.attribute("p.Left").as_string();

		vel.x = b2Max(-speed - 0.1f, -5.0f);
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT )
	{
		
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && onFloor == false)
		{
			texturePath = parameters.attribute("p.JumpR").as_string();
		}
		else
		texturePath = parameters.attribute("p.Right").as_string();

		vel.x = b2Min(speed + 0.1f, 5.0f);
	}

	vel.x *= 0.88;

	//Set the velocity of the pbody of the player
	pbody->body->SetLinearVelocity(vel);
	//Update player position in pixels
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	app->render->DrawTexture(texture, position.x, position.y);

	//--------------------------------Posicion Camara
	app->render->camera.y = -position.y;
	app->render->camera.x = 400 - position.x * 2.0f;
	
	
	return true;
}

bool Player::CleanUp()
{
	return true;
}

// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	// L07 DONE 7: Detect the type of collision

	switch (physB->ctype)
	{
		//-----------------------------MONEDAS
		case ColliderType::ITEM:
			LOG("Collision ITEM");
			//------------------------------------Posible forma para destruir entidades
			//app->entityManager->DestroyEntity();
			break;
		//-----------------------------SUELO
		case ColliderType::PLATFORM:
			onFloor = true;
			LOG("Collision PLATFORM");
			break;
		//-----------------------------CAMBIO DE POSCION DE CAMARA 
		case ColliderType::CHANGECAMERA:
			//app->render->camera.x = -position.x-60;
			LOG("Collision CHANGE CAMERA");
			break;

		//-----------------------------GANAR
		case ColliderType::WIN:
			
			
			LOG("Collision WIN");
			break;
	}
	


}
