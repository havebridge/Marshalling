#pragma once

#include "../array.h"

namespace TestFrame
{
	inline void testString()
	{
		std::string name = "omg";
		std::unique_ptr<ObjectModel::Array> str = ObjectModel::Array::createString("string", ObjectModel::Type::U8, name);
		Core::Utility::saveAll(str.get());
	}
}