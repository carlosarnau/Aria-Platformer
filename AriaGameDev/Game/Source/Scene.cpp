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
	pScene = MENUSCREEN;
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	switch (app->currentScene)
	{
		case TITLESCREEN:
		{
			titleScreen = app->tex->Load("Assets/gamescreens/titlescreen.png");
			app->audio->PlayMusic("Assets/audio/music/menu_music.ogg");
		}
		break;

		case MENUSCREEN:
		{
			menuscreen = app->tex->Load("Assets/gamescreens/menuscreen.png");
			app->audio->PlayMusic("Assets/audio/music/menu_music.ogg");
		}
		break;

		case LEVEL1:
		{
			app->physics->world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
			app->physics->world->SetContactListener(app->physics);

			app->player->SetPlayerLifes(3);

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

			// Id's :
			// 0 Map
			// 1 Player
			// 2 Water
			// 3 Holes
			// 4 Win

			// Map
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

			// Water
			sensor_water01 = app->physics->CreateRectangleSensor(240, 455, 250, 60);
			sensor_water01->id = 2;
			sensor_water01->listener = this;

			sensor_water02 = app->physics->CreateRectangleSensor(1060, 455, 500, 60);
			sensor_water02->id = 2;
			sensor_water02->listener = this;

			sensor_water03 = app->physics->CreateRectangleSensor(1727, 420, 265, 60);
			sensor_water03->id = 2;
			sensor_water03->listener = this;

			// Holes
			sensor_fall01 = app->physics->CreateRectangleSensor(420, 550, 100, 60);
			sensor_fall01->id = 3;
			sensor_fall01->listener = this;

			sensor_fall02 = app->physics->CreateRectangleSensor(660, 550, 110, 85);
			sensor_fall02->id = 3;
			sensor_fall02->listener = this;

			sensor_fall03 = app->physics->CreateRectangleSensor(2255, 550, 523, 100);
			sensor_fall03->id = 3;
			sensor_fall03->listener = this;

			// Win
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

			// Uploading the assets
			pathTex = app->tex->Load("Assets/sprites/PathTexture.png");
			originTex = app->tex->Load("Assets/sprites/Cross.png");
			img = app->tex->Load("Assets/background/Background.png");
			ingamegui = app->tex->Load("Assets/gamescreens/ingamegui.png");
			livestate0 = app->tex->Load("Assets/sprites/livestate0.png");
			livestate1 = app->tex->Load("Assets/sprites/livestate1.png");
			livestate2 = app->tex->Load("Assets/sprites/livestate2.png");
			livestate3 = app->tex->Load("Assets/sprites/livestate3.png");

			edeath_fx = app->audio->LoadFx("Assets/audio/fx/enemy_death.wav");
			ehit_fx = app->audio->LoadFx("Assets/audio/fx/enemy_hitted.wav");
			hit_fx = app->audio->LoadFx("Assets/audio/fx/player_hitted.wav");
			pdeath_fx = app->audio->LoadFx("Assets/audio/fx/death_player.wav");
			water_fx = app->audio->LoadFx("Assets/audio/fx/touching_water.wav");
			fall_fx = app->audio->LoadFx("Assets/audio/fx/player_falling.wav");
			win_fx = app->audio->LoadFx("Assets/audio/fx/winning.wav");
			app->audio->PlayMusic("Assets/audio/music/level_sound.ogg");

			if (app->player->Awake() == 0)
			{
				app->player->Awake();
			}
		}
		break;

		case SETTINGS:
		{
			settingsscreen = app->tex->Load("Assets/gamescreens/settingsscreen.png");
		}
		break;

		case CREDITS:
		{
			creditsscreen = app->tex->Load("Assets/gamescreens/creditsscreen.png");
		}
		break;
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
	switch (app->currentScene)
	{
		case TITLESCREEN:
		{
			app->render->DrawTexture(titleScreen, 0, 0, NULL);

			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
			{
				app->ChangeScene(MENUSCREEN);

				app->render->camera.x = 0;
				return true;
			}
		}
		break;

		case MENUSCREEN:
		{
			app->render->DrawTexture(menuscreen, 0, 0, NULL);

			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
			{
				app->ChangeScene(LEVEL1);

				app->render->camera.x = 0;
				return true;
			}

			if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
			{
				app->ChangeScene(CREDITS);

				app->render->camera.x = 0;
				return true;
			}

			if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
			{
				app->ChangeScene(SETTINGS);

				app->render->camera.x = 0;
				return true;
			}

			if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
			{
				app->ChangeScene(TITLESCREEN);

				app->render->camera.x = 0;
				return true;
			}
		}
		break;

		case LEVEL1:
		{
			app->render->DrawTexture(img, 0, 0, NULL);
			app->render->DrawTexture(ingamegui, 0 + app->render->camera.x, 0, NULL);

			if (app->player->GetPlayerLifes() == 0)
			{
				app->render->DrawTexture(livestate0, 0 + app->render->camera.x, 0, NULL);
			}
			else if (app->player->GetPlayerLifes() == 1)
			{
				app->render->DrawTexture(livestate1, 0 + app->render->camera.x, 0, NULL);
			}
			else if (app->player->GetPlayerLifes() == 2)
			{
				app->render->DrawTexture(livestate2, 0 + app->render->camera.x, 0, NULL);
			}
			else if (app->player->GetPlayerLifes() == 3)
			{
				app->render->DrawTexture(livestate3, 0 + app->render->camera.x, 0, NULL);
			}

			// Resetting the level at pressing F3
			if ((app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) || (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN))
			{
				ResetLevel();
			}

			// L02: DONE 3: Request Load/Save when pressing L/S
			if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
				app->LoadGameRequest();

			if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
				app->SaveGameRequest();

			if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
			{
				app->ChangeScene(MENUSCREEN);

				app->render->camera.x = 0;
				return true;
			}

			// Draw map
			app->map->Draw();
		}
		break;

		case SETTINGS:
		{
			app->render->DrawTexture(settingsscreen, 0, 0, NULL);

			if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
			{
				app->ChangeScene(MENUSCREEN);

				app->render->camera.x = 0;
				return true;
			}
		}
		break;

		case CREDITS:
		{
			app->render->DrawTexture(creditsscreen, 0, 0, NULL);

			if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
			{
				app->ChangeScene(MENUSCREEN);

				app->render->camera.x = 0;
				return true;
			}
		}
		break;
	}
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