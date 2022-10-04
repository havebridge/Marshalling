#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

#include "../object.h"
#include "../primitive.h"

namespace TestFrame
{
	inline void testObject()
	{
		uint8_t u8 = 1111;
		uint16_t u16 = 5000;
		uint32_t u32 = 7656290;
		uint64_t u64 = 1010939010;

		ObjectModel::Primitive* u8p = ObjectModel::Primitive::createPrimitive("U8", ObjectModel::Type::U8, u8);
		ObjectModel::Primitive* u16p = ObjectModel::Primitive::createPrimitive("U16", ObjectModel::Type::U16, u16);
		ObjectModel::Primitive* u32p = ObjectModel::Primitive::createPrimitive("U32", ObjectModel::Type::U32, u32);
		ObjectModel::Primitive* u64p = ObjectModel::Primitive::createPrimitive("U64", ObjectModel::Type::U64, u64);


		ObjectModel::Object Test("test");
		Test.addEntitie(u8p);
		Test.addEntitie(u16p);
		Test.addEntitie(u32p);
		Test.addEntitie(u64p);

		Core::Utility::saveAll(&Test);
	}
}

#endif