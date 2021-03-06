#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene1.h"
#include "Map.h"
#include "EntityManager.h"
#include "Collisions.h"
#include "FadeToBlack.h"
#include "Fonts.h"
#include "FoW.h"

#include "Defs.h"
#include "Log.h"

Scene1::Scene1() : Module()
{
	name.Create("scene1");
}

// Destructor
Scene1::~Scene1()
{}

// Called before render is available
bool Scene1::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene1::Start()
{
	app->scene1->active = true;

	app->render->camera.y = 0;
	app->render->camera.x = 0;

	app->map->active = true;

	if (app->loadingGame == true)
	{
		app->LoadGameRequest();
		app->loadingGame = false;
	}

	app->map->Load("demo.tmx");
	
	app->entityManager->AddEntity({ app->playerPosition.x, app->playerPosition.y }, Entity::Type::PLAYER);
	app->entityManager->AddEntity({ app->playerPosition.x+320, app->playerPosition.y-320 }, Entity::Type::GOBLIN);
	app->entityManager->AddEntity({ app->playerPosition.x+300, app->playerPosition.y-480 }, Entity::Type::GOBLIN);
	app->entityManager->AddEntity({ app->playerPosition.x+220, app->playerPosition.y-140 }, Entity::Type::GOBLIN);
	
	//TODO 4.0: Call the function to Load the Fog of War. 
	app->fog->FogLoad();

	return true;
}

// Called each loop iteration
bool Scene1::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene1::Update(float dt)
{
	app->map->Draw();
	app->map->LoadColliders();

	return true;
}

// Called each loop iteration
bool Scene1::PostUpdate()
{
	bool ret = true;
	//TODO 4.1: Call the function to draw the Fog of War. 
	app->fog->FogDraw();
	return ret;
}

// Called before quitting
bool Scene1::CleanUp()
{
	if (!active)return true;

	app->entityManager->CleanUp();
	app->collisions->CleanUp();
	app->map->CleanUp();

	app->scene1->active = false;

	LOG("Freeing scene");
	return true;
}
