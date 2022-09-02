#ifndef ARRAY_TEST_H
#define ARRAY_TEST_H

#include "../array.h"


namespace TestFrame
{
	inline void testArray()
	{
		std::vector<uint8_t> data{ 1,2,3,4 };
		ObjectModel::Array* arr = ObjectModel::Array::createArray("array", ObjectModel::Type::U8, data);
		Core::Util::saveAll(arr);
	}
}

#endif 