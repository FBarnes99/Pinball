#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

struct Bouncerst {

	PhysBody* body = nullptr;
	bool hitted = false;
};


class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool background_created = false;

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	bool OnCollisionBouncer(PhysBody* bodyA, Bouncerst bodyB);
public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	
	struct Bouncerst Volt1;
	struct Bouncerst Volt2;
	struct Bouncerst Volt3;


	char player_score[10];

	SDL_Texture* map_tex;
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	uint bonus_fx;
	int score = -1;
};
