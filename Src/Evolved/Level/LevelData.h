#ifndef Evolved_LevelData_H
#define Evolved_LevelData_H

#include <string>
#include <map>
#include <sstream>
#include <cassert>
#include <ios>

namespace Evolved {

	/**
	Every level file contains a number of entities and their data. After the entities
	are built and their components are instantiated, then they are spawned with their
	actual data. That's the second step of their initialization.
	This type stores that data and provides a get function to obtain properties.
	*/
	class CLevelData {
	private:
		/**
		Alias for our map of properties.
		*/
		typedef std::map<std::string, std::string> TProperties;

		/**
		Internal map of properties.
		*/
		TProperties _properties;

		/**
		To abstract and reuse our get function, we provide a private and more generic
		function which is used by the other ones where applyable.
		It lets us provide a stream manipulator so we can process some data easier.
		*/
		template <typename T>
		bool get(const std::string &propertyName,
		         T &outValue,
		         std::ios_base & (*manipulator)(std::ios_base &),
		         int ignoreItems = 0) const {
			// do we have the property?
			TProperties::const_iterator it = _properties.find(propertyName);

			if(it == _properties.end()) {
				return false;
			}

			// extract it
			std::string rawValue = it->second;
			std::istringstream iss(rawValue);

			// try to build the object and get if it's correct or not
			// not using outValue directly in case extraction is correct but it's not
			// the end of the stream
			T auxOut;

			// include our manipulator when extracting
			// added "(...) != 0" to solve warning C4800 (converting int to bool)
			bool correct = (iss >> manipulator >> auxOut) != 0;

			// ignore a number of items to get to end of stream
			iss.ignore(ignoreItems);

			if(correct && iss.eof()) {
				outValue = auxOut;
				return true;
			}

			return false;
		}

	public:
		/**
		Default constructor.
		*/
		CLevelData();

		/**
		Default destructor.
		*/
		~CLevelData();

		/**
		Adds a property into the data structure. It doesn't allow duplicates.
		*/
		void put(const std::string &propertyName, const std::string &propertyValue);

		/**
		Gets a property and processes it into an instance of a type provided by the user.
		Returns whether or not the processing was correct, since data is set to the out value.
		*/
		template <typename T>
		bool get(const std::string &propertyName, T &outValue) const {
			return get(propertyName, outValue, std::skipws);
		}

		/**
		Gets a boolean value.
		*/
		template <> bool get(const std::string &propertyName, bool &outValue) const {
			return get(propertyName, outValue, std::boolalpha);
		}

		/**
		Gets a char value.
		*/
		template <> bool get(const std::string &propertyName, char &outValue) const {
			return get(propertyName, outValue, std::skipws, 1);
		}

		/**
		Gets a string value, without taking spaces into account.
		*/
		template <> bool get(const std::string &propertyName, std::string &outValue) const {
			// do we have the property?
			TProperties::const_iterator it = _properties.find(propertyName);

			if(it == _properties.end()) {
				return false;
			}

			// this time, with strings, we want to extract it raw
			outValue = it->second;
			return true;
		}
	};

}

#endif