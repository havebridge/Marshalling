#include "primitive.h"

namespace ObjectModel
{
	Primitive::Primitive()
	{
		size += sizeof type;
	}

	void Primitive::pack(std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		Core::encode<uint8_t>(buffer, iterator, nameLength);
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<uint8_t>(buffer, iterator, wrapper);
		Core::encode<uint8_t>(buffer, iterator, type);
		Core::encode<uint8_t>(buffer, iterator, *data);
		Core::encode<uint32_t>(buffer, iterator, size);
	}

	Primitive Primitive::unpack(const std::vector<uint8_t>& buffer)
	{
		Primitive p;
		uint16_t iterator = 0;

		p.nameLength = Core::decode<uint8_t>(buffer, iterator);
		p.name = Core::decode<std::string>(buffer, iterator);
		p.wrapper = Core::decode<uint8_t>(buffer, iterator);
		p.type = Core::decode<uint8_t>(buffer, iterator);

		p.data = new std::vector<uint8_t>(getTypeSize(static_cast<Type>(p.type)));
		
		Core::decode<uint8_t>(buffer, iterator, *p.data);
		p.size = Core::decode<uint32_t>(buffer, iterator);

		return p;
	}
}