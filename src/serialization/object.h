#pragma once


#include "core.h"
#include "primitive.h"
#include "array.h"

namespace ObjectModel
{
	class LIB Object : public Root
	{
	private:
		uint8_t primitiveCount = 0, arrayCount = 0, stringCount = 0, objectCount = 0;
		std::vector<Primitive> primitives;
		std::vector<Array> arrays;
		std::vector<Array> strings;
		std::vector<Object> objects;
	public:
		Object(std::string);
		Object() = default;
	public:
		void addEntitie(Root*);

		virtual void pack(std::vector<uint8_t>&, uint16_t&) override;
		static Object unpack(const std::vector<uint8_t>&, uint16_t&);
	};
}
