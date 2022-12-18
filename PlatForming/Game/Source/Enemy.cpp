#include "Enemy.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "PathFinding.h"
#include "Map.h"

Enemy::Enemy() : Entity(EntityType::ENEMY)
{
	name.Create("Enemy");
}

Enemy::~Enemy() {

}

bool Enemy::Awake() {

	
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("ef.Jump").as_string();

	return true;
}

bool Enemy::Start() {

	stopEnem = false;
	texture = app->tex->Load(texturePath);

	pbody = app->physics->CreateRectangle(position.x+15, position.y+10, 15, 15, bodyType::DYNAMIC);
	
	// L07 DONE 6: Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method
	pbody->listener = this;

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::ENEMY;

	

	return true;
}

bool Enemy::Update()
{
	
	float speed = 1.0f;
	b2Vec2 vel = b2Vec2(0, -0.168f);

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		stopEnem = !stopEnem;


	if (stopEnem ==false) {

	for (int i = 0; i < 100; i++)
	{
		
		if (position.x > rutax[1]) {
			vel = b2Vec2(-speed, 0);
			
		}

		if (position.x  < rutax[1]) {
			vel = b2Vec2(speed,0);
			
		}
		
		if (position.y > rutay[1]) {
			vel = b2Vec2(0, -speed);
			
		}

		if (position.y < rutay[1]) {
			vel = b2Vec2(0, speed);
		}

		
		
	}
	 pbody->body->SetLinearVelocity(vel);
	
	if (die == true) {
		pbody->body->SetTransform(b2Vec2(8,10), 0);
		
		die = false;
	}
	
	}


	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;
	

	app->render->DrawTexture(texture, position.x, position.y);

	return true;
}

bool Enemy::CleanUp()
{
	return true;
}

// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
void Enemy::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	
		//------------------------PERDER
	case ColliderType::PLAYER:
		if (app->scene->player->position.y >= position.y)
		{
			die = true;
		}
		
		break;
	}


}
