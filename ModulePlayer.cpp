
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ball_tex = left_flipper = right_flipper = NULL;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading ball");
	
	ball_tex = App->textures->Load("pinball/ball.png");
	left_flipper = App->textures->Load("pinball/Left_flipper.png");
	right_flipper = App->textures->Load("pinball/Right_flipper.png");
	
	
	
	setBall(PLAYER_POS_X, PLAYER_POS_Y);
	setPusher();
	setLeftFlipper();
	setRightFlipper();
	background_created = true;
	

		

	score = 0;
	return true;
}
// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading ball");
	App->textures->Unload(ball_tex);
	App->textures->Unload(left_flipper);
	App->textures->Unload(right_flipper);
	App->textures->Unload(pusher_ball);



	return true;
}



// Update: draw background
update_status ModulePlayer::Update()
{


	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		R_Flipper_joint->EnableMotor(true);
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		R_Flipper_joint->EnableMotor(false);
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		L_Flipper_joint->EnableMotor(true);
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		L_Flipper_joint->EnableMotor(false);
	}

	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		
		pusherjoint->EnableMotor(true);
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		
		pusherjoint->EnableMotor(false);
	}

	
	//Flippers Draw------

	R_Flipper->GetPosition(position.x, position.y);
<<<<<<< HEAD
=======

>>>>>>> 679cfe0b0e33d9bd8b517f4cee2d4b7381bc9e20
	App->renderer->Blit(right_flipper, position.x, position.y, NULL, 1.0f, R_Flipper->GetRotation());
	
	L_Flipper->GetPosition(position.x, position.y);
	App->renderer->Blit(left_flipper, position.x, position.y, NULL, 1.0f, L_Flipper->GetRotation());
<<<<<<< HEAD


=======
>>>>>>> 679cfe0b0e33d9bd8b517f4cee2d4b7381bc9e20

	//Ball Draw--------------------
	player_ball->GetPosition(position.x, position.y);
	App->renderer->Blit(ball_tex, position.x, position.y, NULL, 1.0f, player_ball->GetRotation());
	
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		//delete(player_ball);
		
		App->physics->world->DestroyBody(player_ball->body);
		setBall(PLAYER_POS_X, PLAYER_POS_Y);
		score = 0;

	}

	if (position.y > SCREEN_HEIGHT  ) {
		
		App->physics->world->DestroyBody(player_ball->body);
		setBall(PLAYER_POS_X, PLAYER_POS_Y);
		score = 0;
	}
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(PhysBody * body_A, PhysBody * body_B)
{
	//App->audio->PlayFx(App->scene_intro->hit_fx);
	score += 100;
}


void ModulePlayer::setPusher() {

	pusher = App->physics->CreateRectangle(PLAYER_POS_X, PLAYER_POS_Y + 20, 30, 40, b2_dynamicBody,0);
	pusher_pivot = App->physics->CreateRectangle(PLAYER_POS_X, PLAYER_POS_Y + 50, 18, 20, b2_staticBody,0);


	b2PrismaticJointDef prismaticJointDef;

	prismaticJointDef.bodyA = pusher->body;
	prismaticJointDef.bodyB = pusher_pivot->body;

	prismaticJointDef.localAnchorA.Set(0, 0);
	prismaticJointDef.localAnchorB.Set(0, 0);
	prismaticJointDef.collideConnected = false;

	prismaticJointDef.localAxisA.Set(0, 1);

	prismaticJointDef.enableLimit = true;
	prismaticJointDef.lowerTranslation = 0;
	prismaticJointDef.upperTranslation = PIXEL_TO_METERS(50);
	prismaticJointDef.enableMotor = false;
	prismaticJointDef.maxMotorForce = 700;
	prismaticJointDef.motorSpeed = 5000;

	pusherjoint = (b2PrismaticJoint*)App->physics->world->CreateJoint(&prismaticJointDef);
}

void ModulePlayer::setRightFlipper() {

	R_Flipper = App->physics->CreateRectangle(211, 519, 50, 10,b2_dynamicBody,1.1f);
	R_Flipper_pivot = App->physics->CreateCircle(210, 515, 6, b2_staticBody);

	b2RevoluteJointDef revoluteJointDef;

	revoluteJointDef.bodyA = R_Flipper->body;
	revoluteJointDef.bodyB = R_Flipper_pivot->body;

	R_Flipper->body->SetGravityScale(10.0f);

	
	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(15), 0);
	revoluteJointDef.localAnchorB.Set(0, 0);
	revoluteJointDef.collideConnected = false;

	revoluteJointDef.enableLimit = true;
	revoluteJointDef.upperAngle = 35 * DEGTORAD;
	revoluteJointDef.lowerAngle = -30 * DEGTORAD;

	revoluteJointDef.motorSpeed = -2000.0f * DEGTORAD;
	revoluteJointDef.maxMotorTorque = 1500.0f;
	revoluteJointDef.enableMotor = false;

	R_Flipper_joint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef);
}

void ModulePlayer::setLeftFlipper() {

	L_Flipper = App->physics->CreateRectangle(142, 483, 50, 10, b2_dynamicBody,1.1f);//210 741
	L_Flipper_pivot = App->physics->CreateCircle(108, 513, 7, b2_staticBody);

	b2RevoluteJointDef revoluteJointDef;

	revoluteJointDef.bodyA = L_Flipper->body;
	revoluteJointDef.bodyB = L_Flipper_pivot->body;
	L_Flipper->body->SetGravityScale(10.0f);


	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(-18), 0);
	revoluteJointDef.localAnchorB.Set(0, 0);
	revoluteJointDef.collideConnected = false;

	revoluteJointDef.enableLimit = true;
	revoluteJointDef.upperAngle = 35 * DEGTORAD;
	revoluteJointDef.lowerAngle = -30 * DEGTORAD;

	revoluteJointDef.motorSpeed = 2000.0f * DEGTORAD;
	revoluteJointDef.maxMotorTorque = 1500.0f;
	revoluteJointDef.enableMotor = false;

	L_Flipper_joint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef);

}

void ModulePlayer::setBall(uint x, uint y)
{
	player_ball = App->physics->CreateCircle(x, y, 10, b2_dynamicBody);
	player_ball->listener = this; 
}
