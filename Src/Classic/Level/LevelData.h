#ifndef Classic_LevelData_H
#define Classic_LevelData_H

#include <string>
#include <map>
#include <sstream>
#include <cassert>
#include <ios>

namespace Classic {

	class CLevelData {
	private:
		typedef std::map<std::string, std::string> TProperties;
		TProperties _properties;

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
		CLevelData();

		~CLevelData();

		void put(const std::string &propertyName, const std::string &propertyValue);

		template <typename T>
		bool get(const std::string &propertyName, T &outValue) const {
			return get(propertyName, outValue, std::skipws);
		}

		template <> bool get(const std::string &propertyName, bool &outValue) const {
			return get(propertyName, outValue, std::boolalpha);
		}

		template <> bool get(const std::string &propertyName, char &outValue) const {
			return get(propertyName, outValue, std::skipws, 1);
		}

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