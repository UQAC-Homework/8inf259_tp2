#ifndef INC_8INF259_TP2_KEYMISSINGEXCEPTION_H
#define INC_8INF259_TP2_KEYMISSINGEXCEPTION_H
#include <any>
#include <sstream>
#include <string>

namespace exceptions
{
	class KeyNotFoundException : public std::exception
	{
		std::string _msg;

	public:
		template <typename Key>
		explicit KeyNotFoundException(const Key& key)
		{
			std::ostringstream oss;
			oss << "Key '" << key << "' was not found";

			this->_msg = oss.str();
		}

		[[nodiscard]] const char* what() const noexcept override
		{
			return _msg.c_str();
		}
	};
}

#endif //INC_8INF259_TP2_KEYMISSINGEXCEPTION_H
