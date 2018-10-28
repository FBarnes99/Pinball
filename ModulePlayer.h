#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2List.h"
#include "p2Point.h"
#include "Box2D/Box2D/Box2D.h"

#define PLAYER_POS_X 386 - 40
#define PLAYER_POS_Y 556 -20

class PhysBody;
struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool background_created = false;

	iPoint position;
	uint score = 0;
	uint maxscore = 0;
	uint lives;


private:
	void OnCollision(PhysBody * bodyA, PhysBody * bodyB);
	void setRightFlipper();
	void setLeftFlipper();
	void setPusher();
	void setBall(uint x, uint y);
	void Createsensors();

public:

	SDL_Texture* ball_tex;
	SDL_Texture* left_flipper;
	SDL_Texture* right_flipper;
	SDL_Texture* pusher_ball;
	PhysBody* player_ball;

private:

	PhysBody* pusher;
	PhysBody* pusher_pivot;
	PhysBody* L_Flipper;
	PhysBody* L_Flipper_pivot;
	PhysBody* R_Flipper;
	PhysBody* R_Flipper_pivot;
	PhysBody* Volt1;
	PhysBody* Volt2;
	PhysBody* Volt3;
	PhysBody* Dig1;
	PhysBody* Dig2;


	b2PrismaticJoint* pusherjoint;
	b2RevoluteJoint* R_Flipper_joint;
	b2RevoluteJoint* L_Flipper_joint;
};