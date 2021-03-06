#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "Entity.h"

class EntityManager : public Module
{
public:
	EntityManager();

	// Destructor
	virtual ~EntityManager()
	{}

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	void AddEntity(fPoint position, Entity::Type type);

	void OnCollision(Collider* a, Collider* b);


	struct PlayerData 
	{
		fPoint position;
	};

	PlayerData playerData;

	List<Entity*> entityList;

private:
	SDL_Texture* texPlayer;
	SDL_Texture* texGoblin;

	Entity* entityPlayer;
	Entity* entityGoblin;
};

#endif // _ENTITYMANAGER_H_