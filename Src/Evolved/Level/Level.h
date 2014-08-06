#ifndef Evolved_Level_H
#define Evolved_Level_H

#include <vector>
#include <map>

#include "Evolved/Entity/EntityID.h"
#include "Evolved/Level/LevelData.h"

namespace Evolved {

	/**
	Forward declarations.
	*/
	class CEntity;

	/**
	A level is basically a group of entities. It will be loaded from a file
	and then will be used to manage those entities. It defines an entry point
	to activate, deactivate and tick every entity at once.
	*/
	class CLevel {
	private:
		/**
		Alias for the list of entities.
		*/
		typedef std::vector<CEntity *> TEntities;

		/**
		List of entities in this level.
		*/
		TEntities _entities;

		/**
		Data for all entities in the level, when the level is built.
		*/
		typedef std::map<TEntityID, CLevelData> TEntitiesData;

		/**
		Map in which we store entity data for each entity in the level.
		*/
		TEntitiesData _entitiesData;

		/**
		Flag which stores whether or not the level has been initialized already.
		*/
		bool _initialized;

		/**
		Destroys every entity in the level, to be used when the level is destroyed.
		*/
		void destroyAllEntities();

	public:
		/**
		Basic constructor.
		*/
		CLevel();

		/**
		This destructor will destroy every entity in the level.
		*/
		~CLevel();

		/**
		Initializes the level, which means handing data to the entities within it.
		Must be done prior to level activation.
		Second part of the two-step initialization.
		*/
		bool initialize();

		/**
		Activates the level, which will activate every entity in it.
		*/
		bool activate();

		/**
		Deactivates the level, which will deactivate every entity in it.
		*/
		void deactivate();

		/**
		Called once per frame, it will pass the tick to every entity in the level.
		*/
		void tick(float secs);

		/**
		Adds an entity to the level.
		*/
		bool addEntity(CEntity *entity, CLevelData data);

		/**
		Removes an entity from the level.
		*/
		bool removeEntity(CEntity *entity);

		/**
		Retrieves an entity by name.
		*/
		CEntity *getEntityByName(const std::string &name) const;

		/**
		Retrieves an entity by its unique identifier.
		*/
		CEntity *getEntityByID(TEntityID id) const;
	};

}

#endif