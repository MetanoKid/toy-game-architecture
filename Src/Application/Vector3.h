#ifndef Application_Vector3_H
#define Application_Vector3_H

#include <sstream>

namespace Application {

	/**
	Very basic representation of a Vector3: a group of three float values which
	represent a point or a vector in the 3D space.
	*/
	struct Vector3 {

		/**
		Horizontal value.
		*/
		float x;

		/**
		Vertical value.
		*/
		float y;

		/**
		Depth value.
		*/
		float z;

		/**
		Default constructor.
		*/
		Vector3() : x(0.0f), y(0.0f), z(0.0f) {

		}

		/**
		Basic constructor.
		*/
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {

		}

		/**
		Default destructor.
		*/
		~Vector3() {

		}

		/**
		Extracts a Vector3 from a stream.
		*/
		friend std::istream &operator>>(std::istream &is, Vector3 &entry) {
			is >> entry.x >> entry.y >> entry.z;

			return is;
		}

	};

}

typedef Application::Vector3 Vector3;

#endif