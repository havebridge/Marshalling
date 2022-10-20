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

	template<typename ...>
	uint8_t getTypeSize(Type type)
	{
		switch (type)
		{
		case Type::U8: return sizeof(uint8_t); break;
		case Type::U16: return sizeof(uint16_t); break;
		case Type::U32: return sizeof(uint32_t); break;
		case Type::U64: return sizeof(uint64_t); break;
		case Type::BOOL: return sizeof(bool); break;
		case Type::FLOAT: return sizeof(float); break;
		case Type::DOUBLE: return sizeof(double); break;
		}
	}
}