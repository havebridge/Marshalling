#pragma once

#include "../array.h"

namespace TestFrame
{
	inline void testString()
	{
		std::string name = "omg";
		std::unique_ptr<ObjectModel::Array> str = ObjectModel::Array::createString("string", ObjectModel::Type::U8, name);
		Core::Utility::saveAll(str.get());

		uint16_t it = 0;
		std::vector<uint8_t> buffer = Core::Utility::load("Data/string.hsbrdg");
		ObjectModel::Array result = ObjectModel::Array::unpackArr(buffer, it);
	}
}