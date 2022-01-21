#ifndef __INTRO_H__
#define __INTRO_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "Defs.h"


struct SDL_Texture;

class Intro : public Module
{
public:
	Intro(bool startEnabled);

	// Destructor
	virtual ~Intro();

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

	// Called before quitting
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	//Collider* playerWall[100] = { nullptr };

private:
	SDL_Texture* map;

	SDL_Texture* img;

	//uint jump_fx;
	uint water_fx;
	uint fall_fx;
	uint win_fx;
	//uint bonus_fx;

	SDL_Rect end_rect;

	List<PhysBody*> static_chains;
	//p2List<PhysBody*> mapStaticBodies;

	PhysBody* sensor_fall01 = nullptr;
	PhysBody* sensor_fall02 = nullptr;
	PhysBody* sensor_fall03 = nullptr;
	PhysBody* sensor_water01 = nullptr;
	PhysBody* sensor_water02 = nullptr;
	PhysBody* sensor_water03 = nullptr;
	PhysBody* sensor_win = nullptr;
};

#endif // __SCENE2_H__