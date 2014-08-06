#ifndef Evolved_Entity_H
#define Evolved_Entity_H

#include <string>
#include <vector>

#include "EntityID.h"
#include "Evolved/Level/LevelData.h"

namespace Evolved {

	/**
	Forward declarations.
	*/
	class IComponent;
	class CLevel;
	class CLevelData;

	namespace Messages {
		class CMessage;
	}

	/**
	Game entities in this architecture are just component containers. Some common
	component attributes are also part of this class (name, type, level, ...).

	Entities are built in two steps:
	    - The entity is instantiated and its components are instantiated as well.
		- The entity receives its data from the level, and then spawns itself and
		  its components.

	Entities can be activated or deactivated, and will receive a call to the tick
	method to perform per-frame operations.
	*/
	class CEntity {
	private:
		/**
		The ID for this entity, guaranteed to be unique.
		*/
		TEntityID _id;

		/**
		The name for this entity.
		*/
		std::string _name;

		/**
		The type of the entity as informed in the level.
		*/
		std::string _type;

		/**
		Whether the entity is active or not.
		*/
		bool _active;

		/**
		The level in which this entity exists.
		*/
		CLevel *_level;

		/**
		Alias for the list of components of an entity.
		*/
		typedef std::vector<IComponent *> TComponents;

		/**
		The list of components for this entity.
		*/
		TComponents _components;

		/**
		Destroys every component, as the entity is the one responsible for them.
		*/
		void destroyComponents();

	public:
		/**
		Base constructor, with an ID.
		It's the first part of entity's instantiation.
		*/
		CEntity(TEntityID id);

		/**
		Destructor.
		*/
		~CEntity();

		/**
		Second part of the instantiation of an entity.
		When this method is called, it's guaranteed that every component is added
		to the list and will be spawned as well.

		@return bool whether or not the spawn of its components was correct.
		*/
		bool spawn(const CLevelData &data, CLevel *level);

		/**
		Activates the entity.

		@return bool whether or not it could be activated.
		*/
		bool activate();

		/**
		Deactivates the entity.
		*/
		void deactivate();

		/**
		Called every frame, this method is a bridge to component's tick.
		*/
		void tick(float secs);

		/**
		Adds a component to the list.
		*/
		void addComponent(IComponent *component);

		/**
		Removes a component from the list.
		*/
		void removeComponent(IComponent *component);

		/**
		Arguably the most important method in the entity.
		An entity receives a message and tries to send it to its components.
		If a component is informed, the message won't try to be sent to it.
		This is the only way to communicate entities between them.
		*/
		bool sendMessage(Messages::CMessage *message, IComponent *emitter = 0);

		/**
		Gets the level in which this entity exists.
		*/
		CLevel *getLevel() const;

		/**
		Gets the name of this entity.
		*/
		const std::string &getName() const;

		/**
		Gets the unique ID of this entity.
		*/
		TEntityID getID() const;

		/**
		Sets the name of this entity.
		*/
		void setName(const std::string &name);

		/**
		Gets the type of this entity.
		*/
		const std::string &getType() const;

		/**
		Sets the type of this entity.
		*/
		void setType(const std::string &type);

		/**
		Gets whether or not the entity is active.
		*/
		bool isActive() const;
	};

}

#endif