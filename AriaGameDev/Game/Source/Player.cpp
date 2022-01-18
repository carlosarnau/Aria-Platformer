#include "App.h"
#include "Log.h"
#include "Player.h"
#include "Input.h"
#include "p2List.h"
#include "Scene.h"
#include "Physics.h"
#include "Textures.h"
#include"Render.h"
#include"Audio.h"
#include"Window.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"


Player::Player() : Module()
{
	name.Create("player");

	texture = nullptr;

	float idleSpeed = 0.1f;
	float movement1Speed = 0.1f;
	float movement2Speed = 0.2f;
	float deathSpeed = 0.1f;

	// IDLE animation right
	rightIdleAnim.PushBack({ 294, 15, 19, 33 });
	rightIdleAnim.PushBack({ 342, 15, 19, 33 });
	rightIdleAnim.PushBack({ 389, 15, 20, 33 });
	rightIdleAnim.PushBack({ 437, 15, 19, 33 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = idleSpeed;

	// IDLE animation left
	leftIdleAnim.PushBack({ 263, 15, 19, 33 });
	leftIdleAnim.PushBack({ 215, 15, 19, 33 });
	leftIdleAnim.PushBack({ 167, 15, 20, 33 });
	leftIdleAnim.PushBack({ 119, 15, 19, 33 });
	leftIdleAnim.loop = true;
	leftIdleAnim.speed = idleSpeed;

	// Walking animation right
	walkingRigthAnim.PushBack({ 297, 63, 23, 33 });
	walkingRigthAnim.PushBack({ 346, 62, 20, 34 });
	walkingRigthAnim.PushBack({ 393, 61, 17, 35 });
	walkingRigthAnim.PushBack({ 439, 63, 19, 33 });
	walkingRigthAnim.PushBack({ 489, 62, 17, 34 });
	walkingRigthAnim.PushBack({ 538, 61, 21, 35 });
	walkingRigthAnim.loop = true;
	walkingRigthAnim.speed = movement1Speed;

	// Walking animation left
	walkingLeftAnim.PushBack({ 256, 63, 23, 33 });
	walkingLeftAnim.PushBack({ 210, 62, 20, 34 });
	walkingLeftAnim.PushBack({ 166, 61, 17, 35 });
	walkingLeftAnim.PushBack({ 118, 63, 19, 33 });
	walkingLeftAnim.PushBack({ 70, 62, 17, 34 });
	walkingLeftAnim.PushBack({ 17, 61, 21, 35 });
	walkingLeftAnim.loop = true;
	walkingLeftAnim.speed = movement1Speed;

	// Running animation right
	runningRigthAnim.PushBack({ 292, 111, 25, 33 });
	runningRigthAnim.PushBack({ 344, 113, 25, 31 });
	runningRigthAnim.PushBack({ 388, 113, 25, 31 });
	runningRigthAnim.PushBack({ 436, 112, 26, 32 });
	runningRigthAnim.PushBack({ 488, 113, 26, 31 });
	runningRigthAnim.PushBack({ 532, 113, 26, 31 });
	runningRigthAnim.loop = true;
	runningRigthAnim.speed = movement2Speed;

	// Running animation left
	runningLeftAnim.PushBack({ 259, 111, 25, 33 });
	runningLeftAnim.PushBack({ 207, 113, 25, 31 });
	runningLeftAnim.PushBack({ 163, 113, 25, 31 });
	runningLeftAnim.PushBack({ 114, 112, 26, 32 });
	runningLeftAnim.PushBack({ 62, 113, 26, 31 });
	runningLeftAnim.PushBack({ 18, 113, 26, 31 });
	runningLeftAnim.loop = true;
	runningLeftAnim.speed = movement2Speed;

	// Jumping animation right
	jumpingRigthAnim.PushBack({ 297, 209, 16, 31 });
	jumpingRigthAnim.PushBack({ 342, 208, 18, 32 });
	jumpingRigthAnim.PushBack({ 388, 206, 20, 34 });
	jumpingRigthAnim.PushBack({ 436, 201, 19, 34 });
	jumpingRigthAnim.PushBack({ 483, 198, 19, 39 });
	jumpingRigthAnim.PushBack({ 531, 206, 20, 34 });
	jumpingRigthAnim.loop = true;
	jumpingRigthAnim.speed = movement1Speed;

	// Jumping animation left
	jumpingLeftAnim.PushBack({ 263, 209, 16, 31 });
	jumpingLeftAnim.PushBack({ 216, 208, 18, 32 });
	jumpingLeftAnim.PushBack({ 168, 206, 20, 34 });
	jumpingLeftAnim.PushBack({ 121, 201, 19, 34 });
	jumpingLeftAnim.PushBack({ 74, 198, 19, 39 });
	jumpingLeftAnim.PushBack({ 25, 206, 20, 34 });
	jumpingLeftAnim.loop = true;
	jumpingLeftAnim.speed = movement1Speed;

	// Getting hit right
	hitFromRightAnim.PushBack({ 294, 255, 19, 33 });
	hitFromRightAnim.PushBack({ 343, 255, 19, 33 });
	hitFromRightAnim.PushBack({ 391, 255, 18, 33 });
	hitFromRightAnim.loop = false;
	hitFromRightAnim.speed = movement1Speed;

	// Getting hit left
	hitFromLeftAnim.PushBack({ 263, 255, 19, 33 });
	hitFromLeftAnim.PushBack({ 214, 255, 19, 33 });
	hitFromLeftAnim.PushBack({ 167, 255, 18, 33 });
	hitFromLeftAnim.loop = false;
	hitFromLeftAnim.speed = movement1Speed;

	// Death animation right
	deathFromRightAnim.PushBack({ 294, 303, 19, 33 });
	deathFromRightAnim.PushBack({ 340, 303, 23, 33 });
	deathFromRightAnim.PushBack({ 387, 303, 32, 33 });
	deathFromRightAnim.PushBack({ 435, 303, 35, 33 });
	deathFromRightAnim.PushBack({ 483, 303, 34, 33 });
	deathFromRightAnim.PushBack({ 531, 303, 35, 33 });
	deathFromRightAnim.loop = false;
	deathFromRightAnim.speed = deathSpeed;

	// Death animation left
	deathFromLeftAnim.PushBack({ 263, 303, 19, 33 });
	deathFromLeftAnim.PushBack({ 213, 303, 23, 33 });
	deathFromLeftAnim.PushBack({ 157, 303, 32, 33 });
	deathFromLeftAnim.PushBack({ 106, 303, 35, 33 });
	deathFromLeftAnim.PushBack({ 59, 303, 34, 33 });
	deathFromLeftAnim.PushBack({ 10, 303, 35, 33 });
	deathFromLeftAnim.loop = false;
	deathFromLeftAnim.speed = deathSpeed;
}

Player::~Player()
{}

bool Player::Awake()
{
	return true;
}

// Load assets
bool Player::Start()
{
	// Textures
	texture = app->tex->Load("Assets/sprites/GraveRobber.png");

	// Player stats
	startPosX = 70;
	startPosY = 100;
	speed = { 1.3,0 };
	jumpForce = { 0,-2.6f };

	// Id's :
	// 0 Nothing
	// 1 Player
	// 2 Water
	// 3 Holes
	// 4 Win
	// 5 Flying Enemy
	// 6 Walking Enemy

	ColHitbox = app->physics->CreateCircle(startPosX, startPosY,15);
	ColHitbox->id = 1;
	ColHitbox->listener = app->player;
	
	int x_ = (int)x;
	int y_ = (int)y;
	ColHitbox->GetPosition(x_, y_);

	lifes = 4;
	isAlive = true;
	deathAnimAllowed = false;
	win = false;
	slowMoHability = false;

	LOG("Loading player");
	return true;
}

// Unload assets
bool Player::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
bool Player::Update(float dt)
{
	b2Vec2 pos = { x,y };
	b2Vec2 stopping = {0.0f,0.0f};

	bool goLeft = (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT);
	bool goRight = (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT);
	bool qHability = (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN);
	
	// X movement on ground
	if (lifes <= 0)
	{
		isAlive = false;
	}
	if (isAlive != false && win == false)
	{
		if (goRight == true)
		{
			if (ColHitbox->body->GetLinearVelocity().x < 5.f)
				ColHitbox->body->ApplyLinearImpulse(speed, ColHitbox->body->GetPosition(), true);
		}
		if (goLeft == true)
		{
			if (ColHitbox->body->GetLinearVelocity().x > -5.f)
				ColHitbox->body->ApplyLinearImpulse(-speed, ColHitbox->body->GetPosition(), true);
		}
		if (qHability == true)
		{
			if (slowMoHability == true)
			{
				slowMoHability = false;				
			}
			else
			{
				slowMoHability = true;				
			}
		}
	}	
	else
	{
	}

	app->render->camera.x = METERS_TO_PIXELS(ColHitbox->body->GetPosition().x)-0.5f *app->win->GetWidth();

	// X movement on air
	if (ColHitbox->body->GetLinearVelocity().x < -3)
	{
		stopping = { speed.x * 0.2f,0 };

		ColHitbox->body->ApplyLinearImpulse(stopping, ColHitbox->body->GetPosition(), true);
	}
	
	if (ColHitbox->body->GetLinearVelocity().x > 3 )
	{
		stopping = { speed.x * 0.2f,0 };

		ColHitbox->body->ApplyLinearImpulse(-stopping, ColHitbox->body->GetPosition(), true);
	}
		
	b2Body* ground;

	if (ColHitbox->body->GetContactList() != nullptr)
	{
		ground = ColHitbox->body->GetContactList()->contact->GetFixtureA()->GetBody();

		if (ground != nullptr)
		{
			b2Vec2 xVel = { 0,ColHitbox->body->GetLinearVelocity().y };
			if (!goLeft && !goRight) ColHitbox->body->SetLinearVelocity(xVel);

			if (isAlive != false && win == false)
			{
				if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
				{
					b2Vec2 yVel = { ColHitbox->body->GetLinearVelocity().y,0 };
					ColHitbox->body->SetLinearVelocity(yVel);
					ColHitbox->body->ApplyLinearImpulse(jumpForce, ColHitbox->body->GetPosition(), true);
					ColHitbox->body->SetLinearDamping(0);
				}
			}
		}
	}

	if (isAlive == true)
	{
		if (ColHitbox->body->GetLinearVelocity().x < 0)
		{
			direction = 3;
		}
		else if (ColHitbox->body->GetLinearVelocity().x > 0)
		{
			direction = 2;
		}
		else if (direction == 6)
		{
			direction = 0;
		}
		else if (direction == 7)
		{
			direction = 1;
		}
		else if ((ColHitbox->body->GetLinearVelocity().y != 0))
		{
			if (direction == 0) {
				direction = 4;
			}
			if (direction == 1) {
				direction = 5;
			}
			if (direction == 2) {
				direction = 4;
			}
			if (direction == 3) {
				direction = 5;
			}
		}
		else if ((ColHitbox->body->GetLinearVelocity().x == 0) && (ColHitbox->body->GetLinearVelocity().y == 0))
		{
			if (direction == 2) {
				direction = 0;
			}
			if (direction == 3) {
				direction = 1;
			}
			if (direction == 4) {
				direction = 0;
			}
			if (direction == 5) {
				direction = 1;
			}
		}
	}
	else
	{
		if (deathAnimAllowed == true)
		{
			if (direction == 0) {
				direction = 6;
			}
			if (direction == 1) {
				direction = 7;
			}
			if (direction == 2) {
				direction = 6;
			}
			if (direction == 3) {
				direction = 7;
			}
			if (direction == 4) {
				direction = 6;
			}
			if (direction == 5) {
				direction = 7;
			}
		}
	}
	if (direction == 0)
	{
		currentAnimation = &rightIdleAnim;
	}
	else if (direction == 1)
	{
		currentAnimation = &leftIdleAnim;
	}
	else if (direction == 2)
	{
		currentAnimation = &runningRigthAnim;
	}
	else if (direction == 3)
	{
		currentAnimation = &runningLeftAnim;
	}
	else if (direction == 4)
	{
		currentAnimation = &jumpingRigthAnim;
	}
	else if (direction == 5)
	{
		currentAnimation = &jumpingLeftAnim;
	}
	else if (direction == 6)
	{
		currentAnimation = &deathFromRightAnim;
	}
	else if (direction == 7)
	{
		currentAnimation = &deathFromLeftAnim;
	}

	currentAnimation->Update();

	return true;
}

bool Player::GetPlayerSlowMo()
{
	return slowMoHability;
}

void Player::SetPlayerSlowMo(bool b)
{
	slowMoHability = b;
}

// Called each loop iteration
bool Player::PostUpdate()
{
	// Drawing player
	app->render->DrawTexture(texture, METERS_TO_PIXELS(ColHitbox->body->GetPosition().x)-10, METERS_TO_PIXELS(ColHitbox->body->GetPosition().y)-17, &currentAnimation->GetCurrentFrame());

	return true;
}

int Player::GetPlayerLifes()
{
	return lifes;
}

void Player::SetPlayerLifes(int l)
{
	lifes = l;
}

bool Player::GetPlayerWin()
{
	return win;
}

void Player::SetPlayerWin(bool b)
{
	win = b;
}

bool Player::LoadState(pugi::xml_node& data)
{
	LOG("loading player ");
	startPosX = data.child("startPos").attribute("x").as_float(0);
	startPosY = data.child("startPos").attribute("y").as_float(0);
	lifes = data.child("lifes").attribute("value").as_int();
	isAlive = data.child("isAlive").attribute("value").as_bool();
	deathAnimAllowed = data.child("deathAnimation").attribute("value").as_bool();

	b2Vec2 v = { PIXEL_TO_METERS( startPosX), PIXEL_TO_METERS(startPosY )};
	ColHitbox->body->SetTransform(v, 0);

	return true;
}

bool Player::SaveState(pugi::xml_node& data) const
{
	LOG("saving player ");
	data.child("startPos").attribute("x").set_value(METERS_TO_PIXELS(ColHitbox->body->GetPosition().x));
	data.child("startPos").attribute("y").set_value(METERS_TO_PIXELS(ColHitbox->body->GetPosition().y));
	data.child("lifes").attribute("value").set_value(lifes);
	data.child("isAlive").attribute("value").set_value(isAlive);
	data.child("deathAnimation").attribute("value").set_value(deathAnimAllowed);

	return true;
}

void Player::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == nullptr)
	{
	}
	else
	{
		if ((bodyA->id == 1) && (bodyB->id == 2))
		{
			if (app->player->GetPlayerLifes() > 0)
			{
				// Fall in water loose one life
				app->audio->PlayFx(app->scene->water_fx);
				//app->player->life
				app->player->SetPlayerLifes(app->player->GetPlayerLifes() - 1);

				bodyA->body->ApplyLinearImpulse({ 0, -3.5f }, app->player->GetColHitbox()->body->GetPosition(), true);
			}
			else
			{
				//app->player->currentAnimation = &app->player->deathFromLeftAnim;
				app->player->deathAnimAllowed = true;
				app->audio->PlayFx(app->scene->pdeath_fx);
				//app->player->SetPlayerLifes(3);
			}
		}
		else if ((bodyA->id == 1) && (bodyB->id == 3))
		{
			// Fall and loose

			if (app->player->GetPlayerLifes() > 0)
			{
				app->audio->PlayFx(app->scene->fall_fx);

				app->player->SetPlayerLifes(app->player->GetPlayerLifes() - 1);

				bodyA->body->ApplyLinearImpulse({ 0, -5.5f }, app->player->GetColHitbox()->body->GetPosition(), true);
			}
			else
			{

				//app->player->currentAnimation=&app->player->deathFromRightAnim;
				app->audio->PlayFx(app->scene->pdeath_fx);
				app->player->deathAnimAllowed = true;
				//app->player->SetPlayerLifes(3);
			}
		}
		else if ((bodyA->id == 1) && (bodyB->id == 0))
		{
			if (app->player->GetPlayerLifes() > 0)
			{
			}
			else
			{
				//app->player->currentAnimation=&app->player->deathFromRightAnim;
				app->player->deathAnimAllowed = true;
				//app->audio->PlayFx(app->scene->pdeath_fx);
				//app->player->SetPlayerLifes(3);
			}
		}
		else if ((bodyA->id == 1) && (bodyB->id == 4))
		{
			if (app->player->GetPlayerLifes() > 0)
			{
				Mix_HaltMusic();
				app->audio->PlayFx(app->scene->win_fx);
				app->player->SetPlayerWin(true);
			}
			else
			{
			}
		}
		else if ((bodyA->id == 1) && (bodyB->id == 5))
		{
			// Fall and loose

			if (app->player->GetPlayerLifes() > 0)
			{
				app->audio->PlayFx(app->scene->hit_fx);

				app->player->SetPlayerLifes(app->player->GetPlayerLifes() - 1);

				if (app->player->GetColHitbox()->body->GetPosition().x > bodyB->body->GetPosition().x)
				{
					bodyA->body->ApplyLinearImpulse({ 5.0f, 0.0f }, app->player->GetColHitbox()->body->GetPosition(), true);
				}

				if (app->player->GetColHitbox()->body->GetPosition().x < bodyB->body->GetPosition().x)
				{
					bodyA->body->ApplyLinearImpulse({ -5.0f, 0.0f }, app->player->GetColHitbox()->body->GetPosition(), true);
				}				
			}
			else
			{
				app->player->deathAnimAllowed = true;
				app->audio->PlayFx(app->scene->pdeath_fx);
			}
		}
		else if ((bodyA->id == 1) && (bodyB->id == 6))
		{
		// Fall and loose

			if (app->player->GetPlayerLifes() > 0)
			{
				app->audio->PlayFx(app->scene->hit_fx);

				app->player->SetPlayerLifes(app->player->GetPlayerLifes() - 1);

				if (app->player->GetColHitbox()->body->GetPosition().x > bodyB->body->GetPosition().x)
				{
					bodyA->body->ApplyLinearImpulse({ 5.0f, 0.0f }, app->player->GetColHitbox()->body->GetPosition(), true);
				}

				if (app->player->GetColHitbox()->body->GetPosition().x < bodyB->body->GetPosition().x)
				{
					bodyA->body->ApplyLinearImpulse({ -5.0f, 0.0f }, app->player->GetColHitbox()->body->GetPosition(), true);
				}
			}
			else
			{
				app->player->deathAnimAllowed = true;
				app->audio->PlayFx(app->scene->pdeath_fx);
			}
		}
	}
}