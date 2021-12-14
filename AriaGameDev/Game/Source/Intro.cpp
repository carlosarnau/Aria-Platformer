#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Physics.h"
#include "Window.h"
#include "Intro.h"
#include "Player.h"
#include "Physics.h"
#include "Map.h"
#include "SDL_mixer/include/SDL_mixer.h"

#include <iostream>

#include "Defs.h"


Intro::Intro(bool startEnabled) : Module()
{
	name.Create("scene");
}

// Destructor
Intro::~Intro()
{}

// Called before render is available
bool Intro::Awake()
{
	//LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Intro::Start()
{
	app->physics->world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	app->physics->world->SetContactListener(app->physics);

	app->player->SetPlayerLifes(3);

	// List of points of Box2D
	int map[142] = {
	-2, -3,
	-2, 417,
	127, 417,
	127, 444,
	352, 444,
	352, 417,
	383, 417,
	383, 571,
	455, 573,
	448, 480,
	511, 417,
	606, 417,
	606, 587,
	704, 593,
	705, 481,
	705, 353,
	832, 225,
	1310, 225,
	1310, 285,
	831, 286,
	831, 417,
	927, 417,
	929, 445,
	1028, 445,
	1031, 418,
	1047, 418,
	1050, 445,
	1159, 444,
	1159, 417,
	1176, 417,
	1179, 442,
	1278, 442,
	1280, 417,
	1312, 417,
	1439, 288,
	1504, 288,
	1600, 383,
	1600, 413,
	1855, 413,
	1855, 385,
	1951, 288,
	2015 ,288,
	2015, 600,
	2112, 600,
	2112, 319,
	2080, 319,
	2080, 288,
	2175, 288,
	2175, 319,
	2143, 319,
	2143, 600,
	2240, 600,
	2240, 319,
	2208, 319,
	2208, 288,
	2303, 288,
	2303, 319,
	2271, 319,
	2271, 600,
	2368, 600,
	2368, 319,
	2336, 319,
	2336, 288,
	2431, 288,
	2431, 319,
	2399, 319,
	2399, 600,
	2496, 600,
	2496, 288,
	2570, 288,
	2570, -3
	};

	int platform01[8] = {
	129, 289,
	383, 288,
	383, 317,
	129, 317
	};

	int platform02[8] = {
	448, 192,
	480, 192,
	480, 224,
	449, 224
	};

	int platform03[8] = {
	544, 256,
	607, 256,
	607, 286,
	545, 286
	};

	int platform04[8] = {
	1664, 288,
	1664, 319,
	1695, 319,
	1695, 288
	};

	int platform05[8] = {
	1760, 288,
	1760, 319,
	1791, 319,
	1791, 288
	};

	int platform06[8] = {
	2048, 128,
	2048, 159,
	2079, 159,
	2079, 128
	};

	int platform07[8] = {
	2176, 128,
	2176, 159,
	2207, 159,
	2207, 128
	};

	int platform08[8] = {
	2304, 128,
	2304, 159,
	2335, 159,
	2335, 128
	};

	int platform09[8] = {
	2432, 128,
	2432, 159,
	2463, 159,
	2463, 128
	};

	// id's :
	// 0 nothing
	// 1 player
	// 2 water
	// 3 holes
	// 4 win


	static_chains.add(app->physics->CreateStaticChain(0, 0, map, 142));
	static_chains.getLast()->data->id = 0;
	static_chains.getLast()->data->listener = this;

	static_chains.add(app->physics->CreateStaticChain(0, 0, platform01, 8));
	static_chains.getLast()->data->id = 0;
	static_chains.getLast()->data->listener = this;

	static_chains.add(app->physics->CreateStaticChain(0, 0, platform02, 8));
	static_chains.getLast()->data->id = 0;
	static_chains.getLast()->data->listener = this;

	static_chains.add(app->physics->CreateStaticChain(0, 0, platform03, 8));
	static_chains.getLast()->data->id = 0;
	static_chains.getLast()->data->listener = this;

	static_chains.add(app->physics->CreateStaticChain(0, 0, platform04, 8));
	static_chains.getLast()->data->id = 0;
	static_chains.getLast()->data->listener = this;
	static_chains.add(app->physics->CreateStaticChain(0, 0, platform05, 8));
	static_chains.getLast()->data->id = 0;
	static_chains.getLast()->data->listener = this;
	static_chains.add(app->physics->CreateStaticChain(0, 0, platform06, 8));
	static_chains.getLast()->data->id = 0;
	static_chains.getLast()->data->listener = this;
	static_chains.add(app->physics->CreateStaticChain(0, 0, platform07, 8));
	static_chains.getLast()->data->id = 0;
	static_chains.getLast()->data->listener = this;
	static_chains.add(app->physics->CreateStaticChain(0, 0, platform08, 8));
	static_chains.getLast()->data->id = 0;
	static_chains.getLast()->data->listener = this;
	static_chains.add(app->physics->CreateStaticChain(0, 0, platform09, 8));
	static_chains.getLast()->data->id = 0;
	static_chains.getLast()->data->listener = this;

	sensor_water01 = app->physics->CreateRectangleSensor(240, 455, 250, 60);
	sensor_water01->id = 2;
	sensor_water01->listener = this;

	sensor_water02 = app->physics->CreateRectangleSensor(1060, 455, 500, 60);
	sensor_water02->id = 2;
	sensor_water02->listener = this;

	sensor_water03 = app->physics->CreateRectangleSensor(1727, 420, 265, 60);
	sensor_water03->id = 2;
	sensor_water03->listener = this;

	sensor_fall01 = app->physics->CreateRectangleSensor(420, 550, 100, 60);
	sensor_fall01->id = 3;
	sensor_fall01->listener = this;

	sensor_fall02 = app->physics->CreateRectangleSensor(660, 550, 110, 85);
	sensor_fall02->id = 3;
	sensor_fall02->listener = this;

	sensor_fall03 = app->physics->CreateRectangleSensor(2255, 550, 523, 100);
	sensor_fall03->id = 3;
	sensor_fall03->listener = this;

	sensor_win = app->physics->CreateRectangleSensor(2540, 280, 20, 85);
	sensor_win->id = 4;
	sensor_win->listener = this;


	// Uploading the assets
	app->map->Load("level1.tmx");
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	img = app->tex->Load("Assets/background/Background.png");
	water_fx = app->audio->LoadFx("Assets/audio/fx/Fall_in_water.wav");
	fall_fx = app->audio->LoadFx("Assets/audio/fx/mixkit-lose-life-falling-2029.wav");
	win_fx = app->audio->LoadFx("Assets/audio/fx/uno.wav");


	if (app->player->Awake() == 0)
	{
		app->player->Awake();
	}


	return true;
}

// Called each loop iteration
bool Intro::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Intro::Update(float dt)
{
	app->render->DrawTexture(img, 0, 0, NULL);

	// L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();


	//std::cout << "    " << app->player->xposition << "      " << app->player->yposition <<std::endl;

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	// Draw map
	app->map->Draw();

	// L03: DONE 7: Set the window title with map/tileset info
	//SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
	//	app->map->mapData.width, app->map->mapData.height,
	//	app->map->mapData.tileWidth, app->map->mapData.tileHeight,
	//	app->map->mapData.tilesets.count());
	//
	//app->win->SetTitle(title.GetString());


	//app->collisions->AddCollider();

	return true;
}

// Called each loop iteration
bool Intro::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;



	return ret;
}



// Called before quitting
bool Intro::CleanUp()
{
	//LOG("Freeing scene");
	while (app->physics->GetWorld()->GetBodyList()->GetNext() != nullptr)
	{
		app->physics->world->DestroyBody(app->physics->GetWorld()->GetBodyList());
	}

	return true;
}

void Intro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
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
				// fall in water loose one life
				app->audio->PlayFx(water_fx);
				//app->player->life
				app->player->SetPlayerLifes(app->player->GetPlayerLifes() - 1);

				bodyA->body->ApplyLinearImpulse({ 0, -3.5f }, app->player->GetColHitbox()->body->GetPosition(), true);

			}
			else
			{
				//app->player->currentAnimation = &app->player->deathFromLeftAnim;


				//app->player->SetPlayerLifes(3);
			}
		}
		else if ((bodyA->id == 1) && (bodyB->id == 3))
		{
			// fall and loose

			if (app->player->GetPlayerLifes() > 0)
			{
				app->audio->PlayFx(fall_fx);

				app->player->SetPlayerLifes(app->player->GetPlayerLifes() - 1);

				bodyA->body->ApplyLinearImpulse({ 0, -5.5f }, app->player->GetColHitbox()->body->GetPosition(), true);

			}
			else
			{

				//app->player->currentAnimation=&app->player->deathFromRightAnim;


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

				//app->player->SetPlayerLifes(3);
			}

		}
		else if ((bodyA->id == 1) && (bodyB->id == 4))
		{

			if (app->player->GetPlayerLifes() > 0)
			{
				Mix_HaltMusic();
				app->audio->PlayFx(win_fx);
				app->player->SetPlayerWin(true);

			}
			else
			{
			}

		}

	}

}