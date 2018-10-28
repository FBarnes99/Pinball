#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"

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
	
public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	
	struct Bouncerst Volt1;
	struct Bouncerst Volt2;
	struct Bouncerst Volt3;


	char player_score[10];

	Animation anim_voltorb;
	Animation anim_bellsprout;
	Animation anim_L_Dugtrio;
	Animation anim_R_Dugtrio;

	Animation* anim_voltorb2;
	Animation* anim_voltorb3;
	Animation* anim_voltorb4;
	Animation* anim_bellsprout2;
	Animation* anim_L_Dugtrio2;
	Animation* anim_R_Dugtrio2;
	
	SDL_Texture* map_tex;
	SDL_Texture* voltorb;
	SDL_Texture* L_Dugtrio;
	SDL_Texture* R_Dugtrio;
	SDL_Texture* bellsprout;
	
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	uint hit_fx;
	int score = -1;
};
