#ifndef EvolvedPlus_Config_H
#define EvolvedPlus_Config_H

#include <string>

#include "EvolvedPlus/Properties.h"

namespace EvolvedPlus {

	class CConfig {
	private:
		/**
		The current and unique instance of the singleton.
		*/
		static CConfig *_instance;

		/**
		Basic constructor, private as a part of the singleton pattern.
		*/
		CConfig();

		/**
		Basic destructor.
		We can only destruct it from inside, so it's private.
		*/
		~CConfig();

		/**
		In order to prevent accidental (or intentional) copying of the singleton instance,
		we declare the copy constructor as private so a compile-time error is shown.
		*/
		CConfig(const CConfig &factory);

		/**
		In order to prevent accidental (or intentional) copying of the singleton instance,
		we declare the assignment operator as private so a compile-time error is shown.
		*/
		CConfig &operator=(const CConfig &factory);

		/**
		Parses configuration file into the internal data structure.
		*/
		void parseConfigFile(const std::string &filePath);

		/**
		Parsed configuration properties from the configuration file.
		*/
		CProperties _properties;

	public:
		/**
		When the singleton won't be used anymore, we can call this method to destroy the
		current instance. This is the only way of destroying it and not calling it would
		leak it.
		*/
		static void release();

		/**
		Gets the instance of this factory.
		It's a singleton, and by returning instead of a pointer we are subtly declaring
		three characteristics:
		    - It won't be NULL: if it was a pointer, and even if we did our work
			  initializing it, it could be NULL conceptually.
			- It can't be changed: a pointer could be pointed somewhere else.
			- It can't be deleted from outside code: pointers could.
		*/
		static CConfig &getInstance();

		/**
		Gets a configuration property.
		*/
		template <typename T>
		bool get(const std::string &propertyName, T &outValue) const {
			return _properties.get<T>(propertyName, outValue);
		}
	};

}

#endif