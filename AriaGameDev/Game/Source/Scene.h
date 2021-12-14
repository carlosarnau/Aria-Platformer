#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "Defs.h"
#include "FlyingEnemy.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene(bool startEnabled);

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Used to pass to the second level
	bool PassLevelCondition();

	// Win and Loss screens and consequences
	bool WinLoseCondition();

	// Called before quitting
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	void ResetLevel();
	
	
	uint water_fx;
	uint fall_fx;
	uint win_fx;

	uint hit_fx;

	uint ehit_fx;
	uint edeath_fx;
	uint pdeath_fx;

	uint shield_fx;
	


	int currentLevel;
	SDL_Texture* pathTex;

private:
	SDL_Texture* map;

	SDL_Texture* img;

	
	SDL_Texture* originTex;

	SDL_Rect end_rect;

	List<PhysBody*> static_chains;
	//p2List<PhysBody*> mapStaticBodies;
	List<FlyingEnemy*> FlyingEnemiesList;

	PhysBody* sensor_fall01 =nullptr;
	PhysBody* sensor_fall02 = nullptr;
	PhysBody* sensor_fall03 = nullptr;
	PhysBody* sensor_water01 = nullptr;
	PhysBody* sensor_water02 = nullptr;
	PhysBody* sensor_water03 = nullptr;
	PhysBody* sensor_win = nullptr;
};

#endif // __SCENE1_H__