#pragma once

#include "../primitive.h"


namespace TestFrame
{
	inline void testPrimitive()
	{
		uint8_t u8 = 1111;
		uint16_t u16 = 5000;
		uint32_t u32 = 7656290;
		uint64_t u64 = 1010939010;

		bool boolean = true;
		float floating = 0.1234f;
		double doubleFloating = 0.829192f;

		std::unique_ptr<ObjectModel::Primitive> u8p = ObjectModel::Primitive::createPrimitive("U8", ObjectModel::Type::U8, u8);
		std::unique_ptr<ObjectModel::Primitive> u16p = ObjectModel::Primitive::createPrimitive("U16", ObjectModel::Type::U16, u16);
		std::unique_ptr<ObjectModel::Primitive> u32p = ObjectModel::Primitive::createPrimitive("U32", ObjectModel::Type::U32, u32);
		std::unique_ptr<ObjectModel::Primitive> u64p = ObjectModel::Primitive::createPrimitive("U64", ObjectModel::Type::U64, u64);

		std::unique_ptr<ObjectModel::Primitive> booleanP = ObjectModel::Primitive::createPrimitive("BOOL", ObjectModel::Type::BOOL, boolean);
		std::unique_ptr<ObjectModel::Primitive> floatingP = ObjectModel::Primitive::createPrimitive("FLOAT", ObjectModel::Type::FLOAT, floating);
		std::unique_ptr<ObjectModel::Primitive> doubleP = ObjectModel::Primitive::createPrimitive("DOUBLE", ObjectModel::Type::DOUBLE, doubleFloating);

		Core::Utility::saveAll(u8p.get());
		Core::Utility::saveAll(u16p.get());
		Core::Utility::saveAll(u32p.get());
		Core::Utility::saveAll(u64p.get());

		Core::Utility::saveAll(booleanP.get());
		Core::Utility::saveAll(floatingP.get());
		Core::Utility::saveAll(doubleP.get());
	}
}