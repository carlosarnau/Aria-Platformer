#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Intro.h"
#include "Scene.h"
#include "Map.h"
#include "Physics.h"
#include "Player.h"
#include "PathFinding.h"
#include "FlyingEnemy.h"
#include "WalkingEnemy.h"

#include "Defs.h"
#include "Log.h"

#include <iostream>
#include <sstream>

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	frames = 0;
	PERF_START(ptimer);
	

	win = new Window();
	input = new Input();
	render = new Render();
	tex = new Textures();
	audio = new Audio();
	intro = new Intro(false);
	scene = new Scene(false);
	map = new Map();
	physics = new Physics();
	player = new Player();
	pathfinding = new PathFinding();
	flyingenemy = new FlyingEnemy();
	walkingenemy = new WalkingEnemy();

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(win);
	AddModule(input);
	AddModule(tex);
	AddModule(audio);
	AddModule(physics);
	AddModule(intro);
	AddModule(scene);
	AddModule(map);
	AddModule(player);
	AddModule(pathfinding);
	AddModule(flyingenemy);
	AddModule(walkingenemy);
	

	// Render last to swap buffer
	AddModule(render);

	PERF_PEEK(ptimer);
}

// Destructor
App::~App()
{
	// Release modules
	ListItem<Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.clear();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.add(module);
}

// Called before render is available
bool App::Awake()
{

	PERF_START(ptimer);

	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	bool ret = false;

	// L01: DONE 3: Load config from XML
	config = LoadConfig(configFile);

	if (config.empty() == false)
	{
		ret = true;
		configApp = config.child("app");

		// L01: DONE 4: Read the title from the config file
		title.Create(configApp.child("title").child_value());
		organization.Create(configApp.child("organization").child_value());
		framerateCap = config.child("app").attribute("framerate_cap").as_uint();
		Capto30 = config.child("app").attribute("Capto30").as_bool();
		vSyncBool = config.child("renderer").child("vsync").attribute("value").as_bool();
	}


	if (ret == true)
	{
		ListItem<Module*>* item;
		item = modules.start;

		while ((item != NULL) && (ret == true))
		{
			// L01: DONE 5: Add a new argument to the Awake method to receive a pointer to an xml node.
			// If the section with the module name exists in config.xml, fill the pointer with the valid xml_node
			// that can be used to read all variables for that module.
			// Send nullptr if the node does not exist in config.xml
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called before the first frame
bool App::Start()
{

	PERF_START(ptimer);

	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	while(item != NULL && ret == true)
	{
		ret = item->data->Start();
		item = item->next;
	}


	PERF_PEEK(ptimer);

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	init = SDL_GetTicks();
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();
	end = SDL_GetTicks();
	
	if (input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		Capto30 = !Capto30;
		if (Capto30 == true)
		{
			framerateCap = 30;
			
		}
		else
		{
			framerateCap = 60;
		}
	}

	

	long elapsedTime = (float)(end - init);
	(float)SDL_GetPerformanceFrequency();

	float frameSpeed = 1000 / limitFrames;
	currentFPS = 1000.0f / elapsedTime;
	//LOG("Current FPS: %f", currentFPS);
	//LOG("time left: %f", frameSpeed - elapsedTime);
	if ((frameSpeed - elapsedTime) > 0.0f)
	{
		SDL_Delay(fabs(floor((long)frameSpeed - elapsedTime)));
	}

	DisplayFrameRateInfo();

	FinishUpdate();
	return ret;
}

// Load config from XML file
// NOTE: Function has been redesigned to avoid storing additional variables on the class
pugi::xml_node App::LoadConfig(pugi::xml_document& configFile) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = configFile.load_file(CONFIG_FILENAME);

	if (result == NULL) LOG("Could not load xml file: %s. pugi error: %s", CONFIG_FILENAME, result.description());
	else ret = configFile.child("config");

	return ret;
}

pugi::xml_node App::LoadSave(pugi::xml_document& saveFile) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = saveFile.load_file(SAVE_STATE_FILENAME);

	if (result == NULL) LOG("Could not load xml file: %s. pugi error: %s", SAVE_STATE_FILENAME, result.description());
	else ret = saveFile.child("config");

	return ret;
}

// ---------------------------------------------
void App::PrepareUpdate()
{
	frame_count++;
	last_sec_frame_count++;

	dt = frame_time.ReadSec();
	LOG("differential time %f ", dt);

	frame_time.Start();
}

// ---------------------------------------------
void App::FinishUpdate()
{
	// L02: DONE 1: This is a good place to call Load / Save methods
	if (loadGameRequested == true) 
		LoadGame();
	if (saveGameRequested == true) 
		SaveGame();

	CalculateFramerate();
}

// Call modules before each loop iteration
bool App::PreUpdate()
{

	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{

	PERF_START(ptimer);

	bool ret = true;
	ListItem<Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	PERF_PEEK(ptimer);

	return ret;
}

// ---------------------------------------
int App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* App::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* App::GetOrganization() const
{
	return organization.GetString();
}

// Load / Save
void App::LoadGameRequest()
{
	// NOTE: We should check if SAVE_STATE_FILENAME actually exist
	loadGameRequested = true;
}

// ---------------------------------------
void App::SaveGameRequest() const
{
	// NOTE: We should check if SAVE_STATE_FILENAME actually exist and... should we overwriten
	saveGameRequested = true;
}

// ---------------------------------------
// L02: TODO 5: Create a method to actually load an xml file
// then call all the modules to load themselves
bool App::LoadGame()
{
	bool ret = false;

	pugi::xml_document saveFile;
	pugi::xml_node save;
	save = LoadSave(saveFile);

	ListItem<Module*>* item;
	item = modules.start;
	//LOG("name: %s", item->data->name.GetString());
	while (item != NULL)
	{
		SString name = item->data->name;
		LOG("name: %s", name.GetString());
		ret = item->data->LoadState(save.child(name.GetString()));
		item = item->next;
	}
	

	loadGameRequested = false;

	return ret;
}

// L02: TODO 7: Implement the xml save method for current state
bool App::SaveGame() const
{
	bool ret = true;

	pugi::xml_document saveFile;
	pugi::xml_node save;
	
	save = LoadSave(saveFile);

	ListItem<Module*>* item;
	item = modules.start;
	
	while (item != NULL)
	{
		LOG("name: %s", item->data->name.GetString());
		SString name = item->data->name;
		LOG("name: %s", name.GetString());
		ret = item->data->SaveState(save.child(name.GetString()));
		item = item->next;
	}

	ret = saveFile.save_file("save_game.xml");

	saveGameRequested = false;

	return ret;
}

void App::CalculateFramerate() {


	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	avg_fps = float(frame_count) / startup_time.ReadSec();
	seconds_since_startup = startup_time.ReadSec();
	last_frame_ms = frame_time.Read();
	frames_on_last_update = prev_last_sec_frame_count;



	if (Capto30 == true) 
	{

		deltaTime = 1000 / framerateCap;

		int delay = deltaTime - last_frame_ms;

		DelayTimer.Start();
		if (delay > 0)
			SDL_Delay((uint32)delay);


		LOG("we waited %u and got back %f", delay, DelayTimer.ReadMs());
	}
}

void App::DisplayFrameRateInfo() {


	if (Capto30) 
	{
		static char title[256];


		sprintf_s(title, 256, "Av.FPS: %.2f Last Frame Ms: %02u Last sec frames: %i  Time since startup: %.3f Frame Count: %lu  CapedTo30:On  vSync:Off",
			avg_fps, last_frame_ms, frames_on_last_update, seconds_since_startup, frame_count);

		app->win->SetTitle(title);
	}

	else {

		static char title[256];
		sprintf_s(title, 256, "Av.FPS: %.2f Last Frame Ms: %02u Last sec frames: %i  Time since startup: %.3f Frame Count: %lu  CapedTo30:Off  vSync:Off",
			avg_fps, last_frame_ms, frames_on_last_update, seconds_since_startup, frame_count);

		app->win->SetTitle(title);


	}

}

