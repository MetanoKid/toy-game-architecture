#ifndef EvolvedPlus_Level_H
#define EvolvedPlus_Level_H

#include <vector>
#include <map>

#include "EvolvedPlus/Entity/EntityID.h"
#include "EvolvedPlus/Entity/EntityData.h"
#include "Application/Macros.h"

namespace EvolvedPlus {

	/**
	Forward declarations.
	*/
	class IComponent;

	namespace Messages {
		class CMessage;
		class CMessageTopic;
	}

	/**
	A level is basically a group of entities. It will be loaded from a file
	and then will be used to manage those entities. It defines an entry point
	to activate, deactivate and tick every entity at once.

	Entities are just an identifier and Levels will be responsible of managing
	them. Components know which entity they belong to, so we can pack them
	into a data structure and deal with them that way.
	*/
	class CLevel {
	private:
		/**
		Alias for the list of components which belong to each entity.
		*/
		typedef std::vector<IComponent *> TComponents;

		/**
		Alias for our map of entities.
		*/
		typedef std::map<TEntityID, CEntityData> TEntities;

		/**
		Map of entities in this level.
		*/
		TEntities _entities;

		/**
		Alias for a vector of entities which will be deleted.
		*/
		typedef std::vector<TEntityID> TDeferredEntities;

		/**
		Vector of entities which are requested to be deleted.
		*/
		TDeferredEntities _entitiesToBeDeleted;

		/**
		Message topic responsible of managing messaging and suscriptions.
		*/
		Messages::CMessageTopic *_messageTopic;

		/**
		Flag which stores whether or not the level has been initialized already.
		*/
		bool _initialized;

		/**
		Destroys every entity in the level, to be used when the level is destroyed.
		*/
		void destroyAllEntities();

		/**
		Deletes every entity which was requested to be deleted.
		*/
		void deletePendingEntities();

		/**
		Creates suscriptions for every entity in the level.
		*/
		void suscribeEntities();

		/**
		Destroys suscriptions for every entity in the level.
		*/
		void unsuscribeEntities();

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
		bool addEntity(const TEntityID &entity, const CEntityData &entityData);

		/**
		Removes an entity from the level.
		*/
		bool removeEntity(const TEntityID &entity);

		/**
		Retrieves an entity by name.
		*/
		TEntityID getEntityByName(const std::string &name) const;

		/**
		Gets the name of an entity.
		*/
		const std::string &getEntityName(const TEntityID &entity) const;

		/**
		Sets the name of an entity.
		*/
		void setEntityName(const TEntityID &entity, const std::string &name);

		/**
		Gets the type of an entity.
		*/
		const std::string &getEntityType(const TEntityID &entity) const;

		/**
		Sets the type of an entity.
		*/
		void setEntityType(const TEntityID &entity, const std::string &type);

		/**
		Gets whether an entity is active or not.
		*/
		bool isEntityActive(const TEntityID &entity) const;

		/**
		Arguably the most important method related to entities.
		Since entities are just identifiers, we need to manage communications between
		components ourselves. To do it, we will delegate to a specialized messaging
		system which knows which components need messaging.
		*/
		bool sendMessage(const TEntityID &destination, Messages::CMessage *message,
		                 IComponent *emitter = 0);

		/**
		Entities can't be deleted at any time, and even less during level's tick because we're
		iterating over every entity, and our iterator would get corrupted.
		To prevent that, we enqueue the entity to be deleted. Later on, we'll really delete
		every entity which is part of that queue.
		*/
		void deferDeleteEntity(const TEntityID &entity);

		/**
		Gets a pointer to a component from an entity given the components type.
		It looks for a component of the given type, which might be O(n) in the worst case,
		where n is the number of components in the entity.
		A nicer way of doing that would be to store components indexed by type.
		*/
		template <typename T>
		T *getComponent(const TEntityID &entity) {
			TEntities::const_iterator it = _entities.find(entity);

			if(it == _entities.end()) {
				return NULL;
			}

			const std::type_info &type = typeid(T);

			FOR_IT_CONST(TComponents, itComponent, it->second.components) {
				IComponent *component = *itComponent;

				// remember: dynamic type lookup during run-time dereferencing the pointer
				if(typeid(*component) == type) {
					return static_cast<T *>(component);
				}
			}

			return NULL;
		}

		/**
		Activates or deactivates a component from an entity in this level.
		When it's deactivated it's also unregistered from any message it was interested in.
		When it's activated it will be registered again.
		*/
		void setComponentActive(IComponent *component, bool active);

	};

}

#endif