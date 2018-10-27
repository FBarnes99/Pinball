#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

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

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

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
	295, 393,
	307, 416,
	304, 520,
	277, 520,
	273, 512,
	211, 556,
	299, 555
	};
	App->physics->CreateChain(0, 0, map2, 70, 0);
	
	int map3[12] = {
	109, 523,
	42, 482,
	41, 415,
	49, 417,
	48, 464,
	114, 512
	};
	App->physics->CreateChain(0, 0, map3, 12, 0);
	int map4[12] = {
	218, 518,
	278, 480,
	282, 412,
	273, 415,
	269, 463,
	213, 505
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
	97, 471,
	77, 430
	};
	App->physics->CreateChain(0, 0, map8, 8, 0);
	
	int map9[8] = {
	222, 467,
	247, 418,
	248, 458,
	232, 463
	};
	App->physics->CreateChain(0, 0, map9, 8, 0);
	
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
	App->physics->CreateBouncer(50, 355, 15);
	App->physics->CreateBouncer(270, 355, 15);
	//voltorb
	App->physics->CreateBouncer(135, 159, 15);
	App->physics->CreateBouncer(183, 139, 15);
	App->physics->CreateBouncer(170, 199, 15);
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10, b2_dynamicBody));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50, b2_dynamicBody));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64,0));
	}

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
	App->audio->PlayFx(bonus_fx);
}
