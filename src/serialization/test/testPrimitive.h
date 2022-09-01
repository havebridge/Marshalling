#ifndef TEST_H
#define TEST_H

#include "../primitive.h"


namespace TestFrame
{
	inline void testPrimitive()
	{
		uint8_t u8 = 111;
		uint16_t u16 = 500;
		uint32_t u32 = 765629;
		uint64_t u64 = 101093901;

		bool boolean = true;
		float floating = 0.123f;
		double doubleFloating = 0.829193f;

		ObjectModel::Primitive* u8p = ObjectModel::Primitive::Create("U8", ObjectModel::Type::U8, u8);
		ObjectModel::Primitive* u16p = ObjectModel::Primitive::Create("U16", ObjectModel::Type::U16, u16);
		ObjectModel::Primitive* u32p = ObjectModel::Primitive::Create("U32", ObjectModel::Type::U32, u32);
		ObjectModel::Primitive* u64p = ObjectModel::Primitive::Create("U64", ObjectModel::Type::U64, u64);

		ObjectModel::Primitive* booleanP = ObjectModel::Primitive::Create("BOOL", ObjectModel::Type::BOOL, boolean);
		ObjectModel::Primitive* floatingP = ObjectModel::Primitive::Create("FLOAT", ObjectModel::Type::FLOAT, floating);
		ObjectModel::Primitive* doubleP = ObjectModel::Primitive::Create("DOUBLE", ObjectModel::Type::DOUBLE, doubleFloating);

		Core::Util::saveAll(u8p);
		Core::Util::saveAll(u16p);
		Core::Util::saveAll(u32p);
		Core::Util::saveAll(u64p);

		Core::Util::saveAll(booleanP);
		Core::Util::saveAll(floatingP);
		Core::Util::saveAll(doubleP);
	}
}

#endif 