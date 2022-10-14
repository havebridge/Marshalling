#pragma once

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

		std::unique_ptr<ObjectModel::Primitive> u8p = ObjectModel::Primitive::createPrimitive("U8", ObjectModel::Type::U8, u8);
		std::unique_ptr<ObjectModel::Primitive> u16p = ObjectModel::Primitive::createPrimitive("U16", ObjectModel::Type::U16, u16);
		std::unique_ptr<ObjectModel::Primitive> u32p = ObjectModel::Primitive::createPrimitive("U32", ObjectModel::Type::U32, u32);
		std::unique_ptr<ObjectModel::Primitive> u64p = ObjectModel::Primitive::createPrimitive("U64", ObjectModel::Type::U64, u64);


		ObjectModel::Object Test("test");
		Test.addEntitie(u8p.get());
		Test.addEntitie(u16p.get());
		Test.addEntitie(u32p.get());
		Test.addEntitie(u64p.get());

		Core::Utility::saveAll(&Test);
	}
}