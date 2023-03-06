#pragma once 

#include "../array.h"


namespace TestFrame
{
	inline void testArray()
	{
		std::vector<uint8_t> data{ 1,2,3 };
		std::unique_ptr<ObjectModel::Array> arr = ObjectModel::Array::createArray("array", ObjectModel::Type::U8, data);
		Core::Utility::saveAll(arr.get());

		std::vector<uint8_t> buffer = Core::Utility::load("Data/array.hsbrdg");
		ObjectModel::Array result = ObjectModel::Array::unpackArr(buffer);
	}
}