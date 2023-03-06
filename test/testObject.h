#pragma once

#include "../object.h"
#include "../primitive.h"

namespace TestFrame
{
	inline void testObject()
	{
#if 0
		uint8_t u8 = 5;
		uint16_t u16 = 10;
		uint32_t u32 = 20;
		uint64_t u64 = 30;

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

#endif
		ObjectModel::Object Test("test");

		std::string str1 = "xyesos";
		std::string str2 = "yeban";
		std::string str3 = "grisha";
		std::string str4 = "nikita";

		std::unique_ptr<ObjectModel::Array> st1 = ObjectModel::Array::createString("str1", ObjectModel::Type::U8, str1);
		std::unique_ptr<ObjectModel::Array> st2 = ObjectModel::Array::createString("str1", ObjectModel::Type::U8, str2);
		std::unique_ptr<ObjectModel::Array> st3 = ObjectModel::Array::createString("str1", ObjectModel::Type::U8, str3);
		std::unique_ptr<ObjectModel::Array> st4 = ObjectModel::Array::createString("str1", ObjectModel::Type::U8, str4);

		Test.addEntitie(st1.get());
		Test.addEntitie(st2.get());
		Test.addEntitie(st3.get());
		Test.addEntitie(st4.get());

		Core::Utility::saveAll(&Test);

		std::vector<uint8_t> objectFromFile = Core::Utility::load("Data/test.hsbrdg");
		uint16_t it = 0;
		ObjectModel::Object object = ObjectModel::Object::unpack(objectFromFile, it);
	}
}