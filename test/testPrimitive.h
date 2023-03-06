#pragma once

#include "../primitive.h"


namespace TestFrame
{
	inline void testPrimitive()
	{
		uint8_t u8 = 5;
		uint16_t u16 = 10;
		uint32_t u32 = 20;
		uint64_t u64 = 30;

		bool boolean = true;
		float floating = 0.12f;
		double doubleFloating = 0.1245f;

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

		std::vector<uint8_t> result1 = Core::Utility::load("Data/U8.hsbrdg");
		uint16_t it1 = 0;
		ObjectModel::Primitive u8p_ = ObjectModel::Primitive::unpack(result1, it1);

		std::vector<uint8_t> result2 = Core::Utility::load("Data/U16.hsbrdg");
		uint16_t it2 = 0;
		ObjectModel::Primitive u16p_ = ObjectModel::Primitive::unpack(result2, it2);

		std::vector<uint8_t> result3 = Core::Utility::load("Data/U32.hsbrdg");
		uint16_t it3 = 0;
		ObjectModel::Primitive u32p_ = ObjectModel::Primitive::unpack(result3, it3);

		std::vector<uint8_t> result4 = Core::Utility::load("Data/U64.hsbrdg");
		uint16_t it4 = 0;
		ObjectModel::Primitive u64p_ = ObjectModel::Primitive::unpack(result4, it4);

		std::vector<uint8_t> result5 = Core::Utility::load("Data/BOOL.hsbrdg");
		uint16_t it5 = 0;
		ObjectModel::Primitive Bool_ = ObjectModel::Primitive::unpack(result5, it5);

		std::vector<uint8_t> result6 = Core::Utility::load("Data/FLOAT.hsbrdg");
		uint16_t it6 = 0;
		ObjectModel::Primitive Floating_ = ObjectModel::Primitive::unpack(result6, it6);

		std::vector<uint8_t> result7 = Core::Utility::load("Data/DOUBLE.hsbrdg");
		uint16_t it7 = 0;
		ObjectModel::Primitive double_ = ObjectModel::Primitive::unpack(result7, it7);
	}
}