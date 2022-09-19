#ifndef PRIMITIVE_TEST_H
#define PRIMITIVE_TEST_H

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

		ObjectModel::Primitive* u8p = ObjectModel::Primitive::createPrimitive("U8", ObjectModel::Type::U8, u8);
		ObjectModel::Primitive* u16p = ObjectModel::Primitive::createPrimitive("U16", ObjectModel::Type::U16, u16);
		ObjectModel::Primitive* u32p = ObjectModel::Primitive::createPrimitive("U32", ObjectModel::Type::U32, u32);
		ObjectModel::Primitive* u64p = ObjectModel::Primitive::createPrimitive("U64", ObjectModel::Type::U64, u64);

		ObjectModel::Primitive* booleanP = ObjectModel::Primitive::createPrimitive("BOOL", ObjectModel::Type::BOOL, boolean);
		ObjectModel::Primitive* floatingP = ObjectModel::Primitive::createPrimitive("FLOAT", ObjectModel::Type::FLOAT, floating);
		ObjectModel::Primitive* doubleP = ObjectModel::Primitive::createPrimitive("DOUBLE", ObjectModel::Type::DOUBLE, doubleFloating);

		Core::Utility::saveAll(u8p);
		Core::Utility::saveAll(u16p);
		Core::Utility::saveAll(u32p);
		Core::Utility::saveAll(u64p);

		Core::Utility::saveAll(booleanP);
		Core::Utility::saveAll(floatingP);
		Core::Utility::saveAll(doubleP);
	}
}

#endif 