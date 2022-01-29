#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"
#include "PugiXml/src/pugixml.hpp"
#include "PerfTimer.h"
#include "Timer.h"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"


// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Intro;
class Scene;
class Map;
class Physics;
class Player;
class FlyingEnemy;
class WalkingEnemy;
class PathFinding;
//class Timer;
//class PerfTimer;

enum sceneType
{
	TITLESCREEN,
	MENUSCREEN,
	LEVEL1,
	SETTINGS,
	CREDITS,
};

class App
{
public:
	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

    // L02: DONE 1: Create methods to request Load / Save
	void LoadGameRequest();
	void SaveGameRequest() const;

	void ChangeScene(sceneType nextScene);

	float GetDeltaTime()
	{
		return dt;
	}

	float DEGTORAD() const
	{
		return degtorad;
	}

	float RADTODEG() const
	{
		return radtodeg;
	}

	bool	vSyncBool;
	bool	Capto30;
	uint framerateCap;

private:
	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;
	pugi::xml_node LoadSave(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGame();
	bool SaveGame() const;

	void CalculateFramerate();
	void DisplayFrameRateInfo();

public:
	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Intro* intro = nullptr;
	Scene* scene = nullptr;
	Map* map;
	Physics* physics;
	Player* player;
	PathFinding* pathfinding;
	FlyingEnemy* flyingenemy;
	WalkingEnemy* walkingenemy;

	sceneType currentScene = TITLESCREEN;
private:
	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;

	float degtorad = 0.0174532925199432957f;
	float radtodeg = 57.295779513082320876f;

	float limitFrames = 60;
	float init;
	float end;
	float currentFPS;
	//////////////
	int start;
	///////////////

	// L01: DONE 2: Create new variables from pugui namespace
	// NOTE: Redesigned LoadConfig() to avoid storing this variables
	//pugi::xml_document configFile;
	//pugi::xml_node config;
	//pugi::xml_node configApp;

	uint frames;
	float dt;

	// L02: DONE 1: Create variables to control when to execute the request load / save
	mutable bool saveGameRequested;
	bool loadGameRequested;

	float avg_fps;
	float seconds_since_startup;
	uint last_frame_ms;
	uint frames_on_last_update;

	PerfTimer ptimer;
	PerfTimer DelayTimer;
	Timer startup_time;
	Timer frame_time;
	Timer last_sec_frame_time;
	uint frame_count = 0;
	uint last_sec_frame_count = 0;
	uint prev_last_sec_frame_count = 0;
	uint deltaTime;
};

extern App* app;

#endif	// __APP_H__