#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Physics.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "Physics.h"
#include "Map.h"
#include "PathFinding.h"
#include "WalkingEnemy.h"
#include "FlyingEnemy.h"
#include "SDL_mixer/include/SDL_mixer.h"

#include <iostream>

#include "Defs.h"
#include "Log.h"

Scene::Scene(bool startEnabled) : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	//LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	app->physics->world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	app->physics->world->SetContactListener(app->physics);

	app->player->SetPlayerLifes(3);

	// Level 1 Box2D points
	if (currentLevel != 2)
	{
		// Show level 1 Box2D points
	}
	
	// Level 2 Box2D points
	if (currentLevel == 2)
	{
		// Show level 2 Box2D points
	}

	// List of Box2D points
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
	// 0 map
	// 1 player
	// 2 water
	// 3 holes
	// 4 win

	// map
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

	// FlyingEnemiesList.add(app->flyingenemy->CreateFlyingEnemy(50,50));

	// water
	sensor_water01 = app->physics->CreateRectangleSensor(240, 455, 250, 60);
	sensor_water01->id = 2;
	sensor_water01->listener = this;

	sensor_water02 = app->physics->CreateRectangleSensor(1060, 455, 500, 60);
	sensor_water02->id = 2;
	sensor_water02->listener = this;

	sensor_water03 = app->physics->CreateRectangleSensor(1727, 420, 265, 60);
	sensor_water03->id = 2;
	sensor_water03->listener = this;

	// holes
	sensor_fall01 = app->physics->CreateRectangleSensor(420, 550, 100, 60);
	sensor_fall01->id = 3;
	sensor_fall01->listener = this;

	sensor_fall02 = app->physics->CreateRectangleSensor(660, 550, 110, 85);
	sensor_fall02->id = 3;
	sensor_fall02->listener = this;

	sensor_fall03 = app->physics->CreateRectangleSensor(2255, 550, 523, 100);
	sensor_fall03->id = 3;
	sensor_fall03->listener = this;

	// win
	sensor_win = app->physics->CreateRectangleSensor(2550, 310, 20, 85);
	sensor_win->id = 4;
	sensor_win->listener = this;

	if (app->map->Load("level1_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data, 1)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	pathTex = app->tex->Load("Assets/sprites/PathTexture.png");
	originTex = app->tex->Load("Assets/sprites/Cross.png");

	hit_fx = app->audio->LoadFx("Assets/audio/fx/player_hitted.wav");

	edeath_fx = app->audio->LoadFx("Assets/audio/fx/enemy_death.wav");
	ehit_fx = app->audio->LoadFx("Assets/audio/fx/b.wav");
	shield_fx = app->audio->LoadFx("Assets/audio/fx/no.wav");
	pdeath_fx = app->audio->LoadFx("Assets/audio/fx/death_player.wav");
	
	// Uploading the assets
	// app->map->Load("level1.tmx");

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
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	app->render->DrawTexture(img, 0, 0, NULL);

	// L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	//std::cout << "    " << app->player->xposition << "      " << app->player->yposition <<std::endl;
	if ((app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) || (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN))
	{
		//app->audio->PlayFx(app->scene->ehit_fx);
		//app->audio->PlayFx(app->scene->pdeath_fx);
		ResetLevel();
	}
	

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	// Draw map
	app->map->Draw();

	// L03: DONE 7: Set the window title with map/tileset info
	// SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
	//	app->map->mapData.width, app->map->mapData.height,
	//	app->map->mapData.tileWidth, app->map->mapData.tileHeight,
	//	app->map->mapData.tilesets.count());
	//
	//  app->win->SetTitle(title.GetString());

	//app->collisions->AddCollider();

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}


// Used to pass to the second level
bool Scene::PassLevelCondition()
{
	if (app->player->GetPlayerWin() == true)
	{
		if (app->player->GetPlayerLifes() > 0)
		{
			return true;
		}
	}
	else 
	{
		return false;
	}
}

// Win and Loss screens and consequences
bool Scene::WinLoseCondition()
{
	if (PassLevelCondition() == true)
	{
		// Show winning screen
		// Destroy all the chains
		return currentLevel = 2;
	}
	else if (app->player->GetPlayerLifes() < 1)
	{
		// Show loosing screen
		// Press x to restart the level
	}
}


// Called before quitting
bool Scene::CleanUp()
{
	//LOG("Freeing scene");

	return true;
}

void Scene::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
}

void Scene::ResetLevel()
{
	b2Vec2 v;
	//player

	v.x = PIXEL_TO_METERS(16);
	v.y = PIXEL_TO_METERS(16);
	app->player->SetPlayerLifes(3);
	app->player->isAlive = true;
	app->player->deathAnimAllowed = false;
	app->player->SetPlayerWin(false);

	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	app->player->GetColHitbox()->body->SetTransform(v, 0);

	// Walking Enemy

	v.x = PIXEL_TO_METERS(app->map->MapToWorld(30, 6).x);
	v.y = PIXEL_TO_METERS(app->map->MapToWorld(30, 6).y);

	app->walkingenemy->lifes = 2;
	app->walkingenemy->isAlive = true;
	app->walkingenemy->deathAnimAllowed = false;
	app->walkingenemy->statesInt = 0;

	

	app->walkingenemy->ColHitbox->body->SetTransform(v, 0);


	// Flying enemy

	v.x = PIXEL_TO_METERS(300);
	v.y = PIXEL_TO_METERS(150);

	app->flyingenemy->lifes = 2;
	app->flyingenemy->isAlive = true;
	app->flyingenemy->deathAnimAllowed = false;
	app->flyingenemy->statesInt = 0;



	app->flyingenemy->ColHitbox->body->SetTransform(v, 0);

}