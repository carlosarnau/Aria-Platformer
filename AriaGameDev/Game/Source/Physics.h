#pragma once
#include "Module.h"
#include "Defs.h"
#include "Box2D/Box2D/Box2D.h"
#include "Textures.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -15.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)


// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int& y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int id;
	int width, height;
	b2Body* body;

	Module* listener;
};

// Module --------------------------------------
class Physics : public Module, public b2ContactListener // TODO
{
public:
	Physics();
	~Physics();

	bool Start();
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius);
	PhysBody* CreateRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateCircleSensor(int x, int y, int radius);
	PhysBody* CreateChain(int x, int y, int* points, int size);
	PhysBody* CreateStaticChain(int x, int y, int* points, int size);
	void CreateSpring(int x, int y);

	b2World* GetWorld();
	b2Body* AddToWorld(b2BodyDef* body);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	b2World* world;
	bool debug;

private:
	SDL_Texture *pathTex;
	SDL_Texture* originTex;

	b2MouseJoint* mouse_joint;
	b2Body* ground;
};