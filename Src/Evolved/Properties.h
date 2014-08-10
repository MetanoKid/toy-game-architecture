#ifndef Evolved_Properties_H
#define Evolved_Properties_H

#include <string>
#include <map>
#include <sstream>
#include <cassert>
#include <ios>

namespace Evolved {

	/**
	Trims a string from both start and end
	*/
	inline std::string trim(const std::string &str) {
		int first = str.find_first_not_of(' ');
		int last = str.find_last_not_of(' ');
		return str.substr(first, last - first + 1);
	}

	/**
	This class stores a map of properties for multiple uses.
	Level files define a number of entities and the data associated to them. That data
	is stored in a properties map.
	Config file defines a number of configuration properties (i.e. file names), which
	are stored in a properties map as well.
	This class provides a way to extract those properties for different types.
	Instead of storing values themselves in a void* map and then performing casts when
	extracting, we store them as strings and let the user extract them as the type they
	want (and thus having different ways of using properties).
	*/
	class CProperties {
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
		When parsing, since we might need it in several places, we provide a way of requiring
		having tabulation for the properties.
		That way, we can require one tab for entity data in a level, or require none for
		config properties (or other amount, in fact).
		*/
		unsigned int _requiredTabs;

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
		CProperties(unsigned int requiredTabs = 0);

		/**
		Default destructor.
		*/
		~CProperties();

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

		/**
		Parses properties from a stream into the properties map.
		*/
		friend std::istream &operator>>(std::istream &is, CProperties &entry) {
			// we'll use these variables to extract properties data
			std::string name;
			std::string value;
			std::string aux;
			std::istringstream iss;

			// start processing properties
			std::getline(is, aux, '\n');

			while(!aux.empty()) {
				assert(aux.find('\t') == (entry._requiredTabs - 1) && "Incorrect number of tabs for a property.");

				// reuse the string stream using the line we've read
				iss.str(aux);
				iss.clear();

				iss >> name;
				std::getline(iss, value, '\n');

				// add the property
				entry.put(name, trim(value));

				// was that the last line?
				if(is.eof()) {
					break;
				}

				// now, get next line to continue processing
				std::getline(is, aux, '\n');
			}

			return is;
		}

		void setRequiredTabs(unsigned int requiredTabs);
	};

}

#endif