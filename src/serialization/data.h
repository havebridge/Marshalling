#ifndef DATA_H
#define DATA_H

#include <cstdint>

namespace ObjectModel
{
	enum class Type : uint8_t
	{
		U8 = 1,
		U16,
		U32,
		U64,

		BOOL,

		FLOAT,
		DOUBLE,
	};

	enum class Wrapper : uint8_t
	{
		PRIMITIVE = 1,
		STRING,
		ARRAY,
		OBJECT
	};
}

#endif