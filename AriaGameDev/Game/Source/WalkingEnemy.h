#pragma once
#include "Module.h"
#include "Point.h"
#include "App.h"
#include "Physics.h"
#include "Input.h"
#include "Module.h"
#include "Textures.h"
#include "Animation.h"


struct SDL_Texture;

enum WALKING_ENEMY_STATE
{
	WALK ,
	ATTACK ,
	DIE 
};

class WalkingEnemy : public Module
{
private:
	float x, y;
	b2Vec2 speed = { 1.3,0 };
	float maxXspeed;

	b2Vec2 DetectionRange;

	SDL_Texture* texture;

public:
	iPoint directionPoint; // pixels	

	iPoint positionOfTheObject; // pixels	

	int lifes;
	bool isAlive;
	bool canJump;

	int statesInt;

	float startPosX;
	float startPosY;

	WALKING_ENEMY_STATE actualStates;

	PhysBody* ColHitbox;

	WalkingEnemy();
	virtual ~WalkingEnemy();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node& data) const;
	bool CleanUp();
	int GetEnemyLifes();
	void SetEnemyLifes(int l);
	void SetEnemyState(WALKING_ENEMY_STATE state);
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	Animation* currentAnimation = nullptr;
	int direction;

	void WalkingEnemy::SetAnimation(Animation& toChange)
	{
		if (currentAnimation != &toChange) {

			toChange.Reset();
			currentAnimation = &toChange;
		}
	}

	//// Set of animations
	//// IDLE animations
	Animation rightIdleAnim;
	Animation leftIdleAnim;
	//
	//// Walking Animations
	Animation runRigthAnim;
	Animation runLeftAnim;
	//
	//
	//// Death Animation
	Animation deathFromRightAnim;
	Animation deathFromLeftAnim;

	bool deathAnimAllowed;
};