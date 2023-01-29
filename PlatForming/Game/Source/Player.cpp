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
#include "Menu.h"
#include "HUD.h"
#include "Map.h"
#include "EntityManager.h"

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
	texturePath = parameters.attribute("p.idle").as_string();

	return true;
}

bool Player::Start() {

	
	texture = app->tex->Load(texturePath);
	// L07 DONE 5: Add physics to the player - initialize physics body
	pbody = app->physics->CreateRectangle(position.x + 16, position.y + 16, 32, 20, bodyType::DYNAMIC);
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
	b2Vec2 vel;
	int speed = 5;


	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && app->menu->creditos == false && app->menu->menuOpciones == false)
	{
		if (app->menu->abrirMenu == false) 
		{
			
			app->menu->Enable();
			app->menu->abrirMenu = true;
			app->menu->posicionSlime = 0;
			app->menu->numMenu = 0;


		}

		else if (app->menu->abrirMenu == true) 
		{
			app->scene->enemyFy->stopEnem = false;
			app->menu->Disable();
			app->scene->player->godMod = false;
			app->menu->abrirMenu = false;
		}

	}
	

	if (vidas > 0 && win==false && app->menu->abrirMenu==false)
	{
		//PARA IR AL PRINCIPIO
		if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		{
			pbody->body->SetTransform(b2Vec2(4, 13), 0);
		}


		//PARA IR AL FINAL
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
		{
			pbody->body->SetTransform(b2Vec2(35, 13), 0);
		}

		// IR AL CHECKPOINT
		if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		{
			pbody->body->SetTransform(b2Vec2(16, 13), 0);
		}

		//-------------------------GOD MODE-------------------------------------
		if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		{
			godMod = !godMod;
		}

		if (godMod == true) {
			vel.x = 0;
			vel.y = -0.168f;
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				vel.x = -speed;
			}

			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				vel.x = speed;
			}

			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			{
				vel.y = -speed;
			}

			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				vel.y = speed;
			}
		}

		//-----------------------------------------MODO NORMAL------------------------------ 
		else {
			vel = pbody->body->GetLinearVelocity();


			// L07 DONE 5: Add physics to the player - updated player position using physics

			//L02: DONE 4: modify the position of the player using arrow keys and render the texture
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && onFloor == true) {
				//
				if (lastSprite != parameters.attribute("p.Jump").as_string())
				{
					texturePath = parameters.attribute("p.Jump").as_string();
					lastSprite = texturePath;
					texture = app->tex->Load(texturePath);
				}

				onFloor = false;
				jump = true;
				LOG("Jump");
				//Sprite de salto
				texturePath = parameters.attribute("p.Jump").as_string();

				for (jumpTime; jumpTime >= 0; jumpTime--) {

					vel.y = b2Max(-10 - 0.1f, -5.0f);

				}
				if (jumpTime <= 0) {
					jump = false;
					jumpTime = 600;

				}

			}

			else if (onFloor == true)
			{
				//Sprite de Idle

				if (lastSprite != parameters.attribute("p.Idle").as_string())
				{
					texturePath = parameters.attribute("p.Idle").as_string();
					lastSprite = texturePath;
					texture = app->tex->Load(texturePath);
				}

			}

			//-------------------------GRAVEDAD CUANDO NO SALTAS
			if (onFloor == false && jumpTime <= 0)
			{
				vel.y = b2Min(speed + 0.1f, 5.0f);
			}




			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{

				if (onFloor == false)
				{
					if (lastSprite != parameters.attribute("p.JumpL").as_string())
					{
						texturePath = parameters.attribute("p.JumpL").as_string();
						lastSprite = texturePath;
						texture = app->tex->Load(texturePath);
					}
				}



				vel.x = b2Max(-speed - 0.1f, -5.0f);
			}



			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{



				if (onFloor == false)
				{
					if (lastSprite != parameters.attribute("p.JumpR").as_string())
					{
						texturePath = parameters.attribute("p.JumpR").as_string();
						lastSprite = texturePath;
						texture = app->tex->Load(texturePath);
					}
				}


				vel.x = b2Min(speed + 0.1f, 5.0f);
			}

			vel.x *= 0.88;


		}

		pbody->body->SetLinearVelocity(vel);

		//Set the velocity of the pbody of the player
		//Update player position in pixels
		position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
		position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

		app->render->DrawTexture(texture, position.x, position.y);

		//--------------------------------Posicion Camara
		
		app->render->camera.x = 400 - position.x * 2.0f;

	}


	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		vidas = 3;
		win = false;
	}

	
	if (die == true && puntodeguardar==false) {

		pbody->body->SetTransform(b2Vec2(3, 13), 0); //MUEVE AL JUGADOR A LA POSICION INICIAL
		vidas--;
		die = false;
		app->scene->enemyFy->die = true;
	}
	else if (die == true && puntodeguardar == true) //MUEVE AL JUGADOR A LA POSICION DEL CHECK POINT
	{
		pbody->body->SetTransform(b2Vec2(17, 13), 0);
		vidas--;
		die = false;
		app->scene->enemyFy->die = true;
	}

	//-----------GANAR------------
	if (win == true) {
		pbody->body->SetTransform(b2Vec2(3, 13), 0); //MUEVE AL JUGADOR A LA POSICION INICIAL
		app->hud->cantidadMonedas = 0;
		app->scene->enemyFy->die = true;
		app->hud->tamañoTiempo = app->hud->cantidadTiempo;
		app->map->cura->body->SetActive(true);
		app->map->checkpoint->body->SetActive(true);
		app->map->nocura = true;
		app->map->adiosCheckpoint = true;

	}
	//----------------------------

	//-----------PERDER------------
	if (vidas <= 0)
	{
		pbody->body->SetTransform(b2Vec2(3, 13), 0);
		app->map->cura->body->SetActive(true);
		app->map->checkpoint->body->SetActive(true);
		app->map->nocura = true;
		app->hud->cantidadMonedas = 0;
		app->hud->tamañoTiempo = app->hud->cantidadTiempo;
		puntodeguardar = false;
		app->map->adiosCheckpoint = true;
	}
	//----------------------------

	return true;
}

bool Player::CleanUp()
{
	return true;
}

// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	// L07 DONE 7: Detect the type of collision

	// L07 DONE 7: Detect the type of collision

	switch (physB->ctype)
	{
		//-----------------------------MONEDAS
	case ColliderType::ITEM:
		LOG("Collision ITEM");


		//app->scene->item->active = false;
		if(app->hud->cantidadMonedas<=4)
		app->hud->cantidadMonedas++;

		//------------------------------------Posible forma para destruir entidades
		posi = app->scene->itemNode.attribute("x").as_int();
		if (posi == position.x) {
			elemi = true;
		}
		else
			app->scene->itemNode.next_sibling();
		//item->attr.set_value(true);



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
		win = true;
		LOG("Collision WIN");

		break;

		//------------------------PERDER
	case ColliderType::DIE:
		if (godMod == false)
		{
			die = true;
			app->scene->enemyFy->die = true;
		}
		LOG("Collision DIE");
		break;

	case ColliderType::ENEMY:
		if (godMod == false)
		{
			die = true;
		}
		LOG("Collision DIE");
		break;


	case ColliderType::MASVIDA:

		if (vidas < 3) {
		vidas++;
		app->map->cura->body->SetActive(false);
		app->map->nocura = false;
		}
		LOG("Collision MAS VIDA");
		break;



	case ColliderType::CHECKPOINT:
		app->map->checkpoint->body->SetActive(false);
		app->map->adiosCheckpoint = false;
		puntodeguardar = true;
		LOG("Collision checkpoint");
		break;
	}

	

}
