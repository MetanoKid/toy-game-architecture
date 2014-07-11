#include <string>

namespace Classic {

	class CEntity {

	public:
		CEntity();

		~CEntity();

		void sayHi(const std::string &name) const;
	};

}