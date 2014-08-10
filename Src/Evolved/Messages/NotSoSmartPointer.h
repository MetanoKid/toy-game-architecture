#ifndef Evolved_Messages_NotSoSmartPointer_H
#define Evolved_Messages_NotSoSmartPointer_H

namespace Evolved {

	namespace Messages {

		/**
		We could take advantage of C++'s smart pointers, but that would
		bind us to a minimum version of the language. Trying to prevent that we'll
		be using this really simple not-so-smart pointer, which is basically a
		reference counter. For all purposes, it's a class which will act as a
		smart pointer... but it needs some external help.
		*/
		class NotSoSmartPointer {
		private:
			/**
			Current count of references for this instance.
			*/
			unsigned int _referenceCount;

		protected:
			/**
			When every references to this instance are released, let children classes
			decide what they should do.
			*/
			virtual void allReferencesReleased() = 0;

		public:
			/**
			Base constructor, will initialize the reference counter.
			*/
			NotSoSmartPointer();

			/**
			Base destructor, virtual as it's expected to be inherited.
			*/
			virtual ~NotSoSmartPointer();

			/**
			Adds a reference to the internal counter.
			*/
			void addReference();

			/**
			Removes a reference from the internal counter. If it happens to be
			reference-less, then it will auto-destroy itself.
			*/
			void releaseReference();
		};

	}

}

#endif