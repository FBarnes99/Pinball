#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	map_tex = App->textures->Load("pinball/background.png");
	score = App->fonts->Load("pinball/score_f.png", "0123456789", 1);
	hit_fx = App->audio->LoadFx("pinball/roblox.wav");

	App->audio->PlayMusic("pinball/145 Victory is Right Before Your Eyes!.ogg", 2);

	if (!background_created) 
		background_created = true;

	int map1[84] = {
	112, 558,
	42, 511,
	41, 523,
	14, 523,
	13, 408,
	21, 396,
	35, 390,
	45, 387,
	46, 349,
	48, 341,
	54, 335,
	29, 270,
	17, 213,
	18, 157,
	18, 137,
	27, 104,
	44, 72,
	63, 55,
	99, 31,
	124, 19,
	155, 14,
	200, 15,
	233, 26,
	267, 40,
	289, 57,
	313, 81,
	337, 124,
	345, 158,
	347, 196,
	347, 248,
	349, 303,
	348, 355,
	347, 402,
	347, 431,
	347, 477,
	346, 517,
	348, 561,
	388, 559,
	392, -4,
	-6, -6,
	-12, 559,
	111, 566
	};
	App->physics->CreateChain(0, 0,map1, 84, 0);

	int map2[70] = {
	318, 555,
	319, 166,
	307, 120,
	290, 94,
	260, 71,
	225, 54,
	172, 46,
	134, 47,
	100, 62,
	76, 82,
	118, 61,
	154, 57,
	191, 58,
	216, 66,
	241, 81,
	270, 106,
	289, 131,
	295, 145,
	297, 164,
	297, 189,
	299, 218,
	295, 244,
	290, 271,
	280, 295,
	272, 312,
	261, 333,
	272, 348,
	273, 387,
	300, 393,
	307, 416,
	304, 520,
	277, 520,
	273, 512,
	211, 556,
	299, 555
	};
	App->physics->CreateChain(0, 0, map2, 70, 0);
	
	int map3[12] = {
	95, 520,
	42, 482,
	41, 415,
	49, 417,
	48, 464,
	99, 503
	};
	App->physics->CreateChain(0, 0, map3, 12, 0);
	
	int map4[12] = {
	224, 518,
	278, 480,
	282, 412,
	273, 415,
	269, 470,
	220, 505
	};
	
	App->physics->CreateChain(0, 0, map4, 12, 0);
	
	int map5[24] = {
		114, 256,
		93, 240,
		87, 197,
		87, 158,
		97, 134,
		99, 145,
		95, 161,
		94, 183,
		107, 204,
		128, 227,
		131, 241,
		125, 251
	};

	App->physics->CreateChain(0, 0, map5, 24, 0);
	int map6[40] = {
	210, 238,
	218, 178,
	219, 125,
	221, 100,
	242, 115,
	257, 138,
	269, 169,
	269, 197,
	269, 227,
	261, 253,
	248, 281,
	240, 291,
	231, 286,
	248, 262,
	254, 239,
	260, 211,
	258, 197,
	229, 196,
	231, 217,
	219, 235
	};
	App->physics->CreateChain(0, 0, map6, 40, 0);

	int map7[22] = {
	78, 300,
	91, 291,
	70, 263,
	60, 224,
	55, 188,
	58, 172,
	49, 186,
	47, 215,
	52, 248,
	61, 273,
	68, 285
	};
	App->physics->CreateChain(0, 0, map7, 22, 0);
	
	
	//over joint
	int map8[8] = {
	73, 420,
	72, 454,
	97, 469,
	77, 430
	};
	App->physics->CreateChain(0, 0, map8, 8, 1.5f);
	
	int map9[8] = {
	222, 467,
	247, 418,
	248, 458,
	232, 463
	};
	App->physics->CreateChain(0, 0, map9, 8, 1.5f);
	
	//over volt
	int map10[8] = {
	132, 99,
	141, 93,
	140, 120,
	135, 128
	};
	App->physics->CreateChain(0, 0, map10, 8, 0);
	
	int map11[8] = {
	177, 88,
	184, 88,
	185, 112,
	177, 112
	};
	App->physics->CreateChain(0, 0, map11, 8, 0);
	//diglet
	App->physics->CreateBouncer(60, 365, 15,1.4f);
	App->physics->CreateBouncer(268, 365, 15, 1.4f);
	//voltorb
	
	
	Volt1.body= App->physics->CreateBouncer(132, 172, 15, 1.4f);
	Volt1.hitted = false;

	Volt2.body = App->physics->CreateBouncer(182, 151, 15, 1.4f);
	Volt2.hitted = false;

	Volt3.body = App->physics->CreateBouncer(170, 209, 15, 1.4f);
	Volt3.hitted = false;

	App->physics->CreateBouncer(27,520, 15, 3.8f);
	App->physics->CreateBouncer(290, 518, 15, 3.8f);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(map_tex);
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	
	
	if (map_tex != NULL)
	{
		App->renderer->Blit(map_tex, 0, 0, NULL, 1.0f);
		
	}
	
	sprintf_s(player_score, 10, "%d", App->player->score);
	App->fonts->BlitText(120, 353, score, player_score, 0.7f);

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//App->audio->PlayFx(hit_fx);

}

