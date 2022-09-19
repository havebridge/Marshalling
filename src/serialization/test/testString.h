#ifndef STRING_TEST_H
#define STRING_TEST_H

#include "../array.h"

namespace TestFrame
{
	inline void testString()
	{
		std::string name = "name";
		ObjectModel::Array* str = ObjectModel::Array::createString("string", ObjectModel::Type::U8, name);
		Core::Utility::saveAll(str);
	}
}

#endif 