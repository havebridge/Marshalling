#pragma once

#include <cstdint>

namespace ObjectModel
{
	enum class Wrapper : uint8_t
	{
		PRIMITIVE = 1,
		ARRAY,
		STRING,
		OBJECT
	};


	enum class Type : uint8_t
	{
		U8 = 1,
		U16,
		U32,
		U64,

		BOOL,

		FLOAT,
		DOUBLE
	};
}