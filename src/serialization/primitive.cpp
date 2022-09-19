#include "primitive.h"

namespace ObjectModel
{
	Primitive::Primitive()
	{
		size += sizeof type;
	}

	void Primitive::pack(std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<uint8_t>(buffer, iterator, nameLenght);
		Core::encode<uint8_t>(buffer, iterator, wrapper);
		Core::encode<uint8_t>(buffer, iterator, type);
		Core::encode<uint8_t>(buffer, iterator, *data);
		Core::encode<uint32_t>(buffer, iterator, size);
	}
}