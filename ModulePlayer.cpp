
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"

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
	Createsensors();

		

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
	



	return true;
}



// Update: draw background
update_status ModulePlayer::Update()
{


	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		R_Flipper_joint->EnableMotor(true);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		R_Flipper_joint->EnableMotor(false);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		L_Flipper_joint->EnableMotor(true);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		L_Flipper_joint->EnableMotor(false);
	}

	
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		
		pusherjoint->EnableMotor(true);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		
		pusherjoint->EnableMotor(false);
	}

	
	

	R_Flipper->GetPosition(position.x, position.y);
	App->renderer->Blit(right_flipper, position.x, position.y, NULL, 1.0f, R_Flipper->GetRotation());
	
	L_Flipper->GetPosition(position.x, position.y);
	App->renderer->Blit(left_flipper, position.x, position.y, NULL, 1.0f, L_Flipper->GetRotation());

	//Ball Draw--------------------
	player_ball->GetPosition(position.x, position.y);
	App->renderer->Blit(ball_tex, position.x, position.y, NULL, 1.0f, player_ball->GetRotation());
	
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		
		if (score > maxscore) {
			maxscore = score;
		}

		App->physics->world->DestroyBody(player_ball->body);
		setBall(PLAYER_POS_X, PLAYER_POS_Y);
		score = 0;

		

	}

	if (position.y > SCREEN_HEIGHT + 30 ) {
		
		App->physics->world->DestroyBody(player_ball->body);
		
		setBall(PLAYER_POS_X, PLAYER_POS_Y);
		if (score > maxscore) {
			maxscore = score;
		}
		
		score = 0;
	}
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(PhysBody * body_A, PhysBody * body_B)
{
	//maxscore = score;

	if (body_B == Volt1 || body_B == Volt2 || body_B == Volt3 || body_B == Dig1 || body_B == Dig2) {
		App->audio->PlayFx(App->scene_intro->hit_fx);
	}
	
	if (body_B == Volt1) {
		App->scene_intro->Volt1.hitted = true;
		score += 100;
	}
	
	if (body_B == Volt2) {
		App->scene_intro->Volt2.hitted = true;
		score += 100;
	}
	
	if (body_B == Volt3) {
		App->scene_intro->Volt3.hitted = true;
		score += 100;
	}

	if (App->scene_intro->Volt1.hitted == true && App->scene_intro->Volt2.hitted == true && App->scene_intro->Volt3.hitted == true) {

		score += 5000;
		App->scene_intro->Volt1.hitted = false;
		App->scene_intro->Volt2.hitted = false;
		App->scene_intro->Volt3.hitted = false;
	}
	
	if (body_B == Dig1) {
		App->scene_intro->Digg1.hitted = true;
		score += 100;
	}

	if (body_B == Dig2) {
		App->scene_intro->Digg2.hitted = true;
		score += 100;
	}

	if (App->scene_intro->Digg1.hitted == true && App->scene_intro->Digg2.hitted == true) {

		score = score * 2;
		App->scene_intro->Digg1.hitted = false;
		App->scene_intro->Digg2.hitted = false;
		
	}


	//score += 100;
}

void ModulePlayer::Createsensors() {
	
	Volt1 = App->physics->CreateRectangleSensor(132, 172, 33 ,35);
	//Volt1->listener = this;

	Volt2 = App->physics->CreateRectangleSensor(182, 151, 33, 35);
	//Volt2->listener = this;

	Volt3 = App->physics->CreateRectangleSensor(170, 209, 33, 35);
	//Volt3->listener = this;

	Dig1 = App->physics->CreateRectangleSensor(57, 365, 33, 35);
	//Dig1->listener = this;

	Dig2 = App->physics->CreateRectangleSensor(266, 365, 33, 35);
	//Dig2->listener = this;
	
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
